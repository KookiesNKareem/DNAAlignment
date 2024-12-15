# Needleman-Wunsch Global Sequence Alignment
This is a project implementing a global sequence alignment algorithm commonly used to align sequences of DNA for analysis.

# How It's Made:

The Needleman-Wunsch algorithm was implemented from scratch in C++, leveraging efficient data structures such as 2D vectors to store the scoring matrix. The program calculates matches, mismatches, and gap penalties iteratively to fill the matrix, followed by a traceback step to construct the optimal alignment. The project includes:
	•	Dynamic programming to fill the scoring matrix.
	•	A flexible scoring system for matches, mismatches, and gaps.
	•	Interactive command-line input for testing with various DNA sequences.

The program emphasizes both accuracy and readability, ensuring users can interpret alignment outputs easily.

# Lessons Learned:

This project deepened my understanding of dynamic programming and its application in real-world problems like DNA sequence alignment. Key takeaways include:
	•	The importance of handling edge cases, such as terminal gaps, when working with biological data.
	•	The power of well-structured code and debugging tools for validating algorithmic correctness.
	•	The challenge and reward of translating theoretical concepts into practical implementations.
