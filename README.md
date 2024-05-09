# Maximum Words

The goal of this small project is to find the set of words in portuguese that cover the most amount of characters with no repetition.

There are two approaches:
- Brute force backtrack: will try to find every possible subset covering the maximum amount of letters.
- Perfect pangram: Will try directly to find a set of words that cover the 26 letters from the alphabet.

The implementations of these solutions are located in `src/backtrack.cpp` and `src/prangram.cpp` respectively.

The file `data/wordsList` contains a list of words in the portuguese language. The file should have this name and be located in the same path.

Please note that this file is not optimal since there are a lot of acronyms and some english words.
