#pragma once
#include "CellGroup.h"

class SudokuPuzzle {
public:

	SudokuPuzzle();
	~SudokuPuzzle();

	void solve (const char filenameIn[]);

private:
	void InitialiseGrid();

	void output()const;

	void readPuzzle(const char filenameIn[]);

	void setCandidates(const int row, const int column);

	int findBlock(const int row, const int column)const;

	CellGroup m_gridRows[9];
	CellGroup m_gridColumns[9];
	CellGroup m_gridBlocks[9];

};