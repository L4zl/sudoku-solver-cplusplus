#include "SudokuPuzzle.h"

int main(const int argc, char **) {
	SudokuPuzzle puzzle;
	const char*const name = "sudoku_puzzle.txt";
	puzzle.solve(name); 

	return 0;
}