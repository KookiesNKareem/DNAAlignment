#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // For std::reverse
#include <limits.h>  // For INT_MIN

// Scoring constants
int match = 2;
int mismatch = -1;
int gap = -2;

// Function to calculate neighbors for traceback
std::vector<int> getBackwardsNeighbors(const std::vector<std::vector<int>>& matrix, int i, int j) {
    std::vector<int> neighbors = {
        (j > 0 ? matrix[i][j-1] : INT_MIN), // Left neighbor
        (i > 0 ? matrix[i-1][j] : INT_MIN), // Up neighbor
        (i > 0 && j > 0 ? matrix[i-1][j-1] : INT_MIN) // Diagonal neighbor
    };
    return neighbors;
}

std::pair<std::string, std::string> traceback(const std::vector<std::vector<int>>& matrix,
                                              const std::string& seq1, const std::string& seq2) {
    std::string alignedSeq1;
    std::string alignedSeq2;

    int i = seq1.length();
    int j = seq2.length();


    while (i > 0 || j > 0) {

        if (i == 0) { // Only seq2 remains
            alignedSeq1 += '-';
            alignedSeq2 += seq2[j - 1];
            j--;
            continue;
        }
        if (j == 0) { // Only seq1 remains
            alignedSeq1 += seq1[i - 1];
            alignedSeq2 += '-';
            i--;
            continue;
        }

        // Regular traceback logic
        int score = (seq1[i - 1] == seq2[j - 1]) ? match : mismatch;
        if (matrix[i][j] == matrix[i - 1][j - 1] + score) { // Diagonal move
            alignedSeq1 += seq1[i - 1];
            alignedSeq2 += seq2[j - 1];
            i--;
            j--;
        } else if (matrix[i][j] == matrix[i - 1][j] + gap) { // Up move
            alignedSeq1 += seq1[i - 1];
            alignedSeq2 += '-';
            i--;
        } else if (matrix[i][j] == matrix[i][j - 1] + gap) { // Left move
            alignedSeq1 += '-';
            alignedSeq2 += seq2[j - 1];
            j--;
        } else {
            std::cerr << "Error during traceback: invalid move detected." << std::endl;
            break;
        }
    }

    // Reverse the alignments since traceback builds them backwards
    std::reverse(alignedSeq1.begin(), alignedSeq1.end());
    std::reverse(alignedSeq2.begin(), alignedSeq2.end());

    return {alignedSeq1, alignedSeq2};
}

int main(int argc, char* argv[]) {
    std::string seq1, seq2;

    // Support for both command-line arguments and interactive input
    if (argc == 3) {
        // Command-line input
        seq1 = argv[1];
        seq2 = argv[2];
    } else {
        // Interactive input (e.g., in CLion)
        std::cout << "Enter the first sequence: ";
        std::cin >> seq1;
        std::cout << "Enter the second sequence: ";
        std::cin >> seq2;
    }

    // Initialize the scoring matrix
    std::vector<std::vector<int>> matrix(seq1.length() + 1, std::vector<int>(seq2.length() + 1, 0));

    // Fill the scoring matrix
    // Fill the scoring matrix
    for (int i = 0; i <= seq1.length(); i++) {
        for (int j = 0; j <= seq2.length(); j++) {
            if (i == 0) {
                // First row: gap penalties
                matrix[i][j] = j * gap;
            } else if (j == 0) {
                // First column: gap penalties
                matrix[i][j] = i * gap;
            } else {
                // Scoring for match, mismatch, or gap
                int matchMismatch = (seq1[i - 1] == seq2[j - 1]) ? match : mismatch;
                int diagonal = matrix[i - 1][j - 1] + matchMismatch;
                int up = matrix[i - 1][j] + gap;
                int left = matrix[i][j - 1] + gap;
                matrix[i][j] = std::max({diagonal, up, left});
            }
        }
    }

    // Perform traceback to get the alignment
    auto alignment = traceback(matrix, seq1, seq2);

    // Output the aligned sequences
    std::cout << "Aligned Sequence 1: " << alignment.first << std::endl;
    std::cout << "Aligned Sequence 2: " << alignment.second << std::endl;

    return 0;
}