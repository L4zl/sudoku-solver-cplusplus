#include "SudokuPuzzle.h"
#include "CellGroup.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <algorithm>

SudokuPuzzle::SudokuPuzzle() {
	// Add code to initialise the SudokuPuzzle object
	InitialiseGrid();
}

SudokuPuzzle::~SudokuPuzzle()
{}


void SudokuPuzzle::solve(const char filenameIn[]) {
	// Read puzzle from text file
	readPuzzle(filenameIn);

	// Get start time
	const auto startTime = std::chrono::high_resolution_clock::now();

	// Add code to solve the puzzle
	bool loop = true;
	int countCandidates = 0;
	int countLoops = 0;
	int solvedCells = 0;
	while (loop)
	{
		loop = false;
		for (int row = 0; row < 9; ++row)
		{
			for (int column = 0; column < 9; ++column)
			{	
				if (m_gridRows[row].getValue(column) == 0)
				{
					setCandidates(row, column);
				}
			}
		}
		for (int row = 0; row < 9; ++row)
		{
			for (int column = 0; column < 9; ++column)
			{
				std::vector<int>  candidates = m_gridRows[row].getCandidates(column);

				if (candidates.size() == 1)
				{
					m_gridRows[row].setValue(column, candidates.at(0));
					loop = true;
				}
			}
		}

		for (int column = 0; column < 9; ++column)
		{
			for (int i = 1; i < 10; ++i)
			{
				std::vector<int>  indexList;
				for (int index = 0; index < 9; ++index)
				{
					std::vector<int>  candidates = m_gridColumns[column].getCandidates(index);

					if (std::find(candidates.begin(), candidates.end(), i) != candidates.end())
					{
						countCandidates++;
						indexList.push_back(index);
					}
				}
				if (indexList.size() == 1)
				{
					m_gridColumns[column].setValue(indexList.at(0), i);
				}
			}
		}

		for (int block = 0; block < 9; ++block)
		{
			for (int i = 1; i < 10; ++i)
			{
				std::vector<int>  indexList;
				for (int index = 0; index < 9; ++index)
				{
					std::vector<int>  candidates = m_gridBlocks[block].getCandidates(index);

					if (std::find(candidates.begin(), candidates.end(), i) != candidates.end())
					{
						countCandidates++;
						indexList.push_back(index);
					}
				}
				if (indexList.size() == 1)
				{
					m_gridBlocks[block].setValue(indexList.at(0), i);
				}
			}
		}

		for (int row = 0; row < 9; ++row)
		{
			for (int i = 1; i < 10; ++i)
			{
				std::vector<int>  indexList;
				for (int index = 0; index < 9; ++index)
				{
					std::vector<int>  candidates = m_gridRows[row].getCandidates(index);

					if (std::find(candidates.begin(), candidates.end(), i) != candidates.end())
					{
						countCandidates++;
						indexList.push_back(index);
					}
				}
				if (indexList.size() == 1)
				{
					m_gridRows[row].setValue(indexList.at(0), i);
				}
			}
		}

		for (int row = 0; row < 9; ++row)
		{
			for (int column = 0; column < 9; ++column)
			{
				m_gridRows[row].emptyCandidates(column);
			}
		}
		countLoops++;
	}
	for (int row = 0; row < 9; ++row)
	{
		for (int column = 0; column < 9; ++column)
		{
			const bool given = m_gridRows[row].getGiven(column);
			const int value = m_gridRows[row].getValue(column);
			if ((given == false) && (value != 0)) { ++solvedCells; }
		}
	}

	// Get end time
	const auto endTime = std::chrono::high_resolution_clock::now();
	const auto duration = (endTime - startTime).count();

	// Sample timing output in nanoseconds
	std::cout << duration << "ns" << std::endl;
	std::cout << "No of candidates considered: " << countCandidates << std::endl;
	std::cout << "No of loops taken: " << countLoops << std::endl;
	std::cout << "No of cells solved: " << solvedCells << std::endl;

	// Output the solved puzzle
	output();
}


void SudokuPuzzle::setCandidates(const int row, const int column) 
{
	std::vector<int> list;
	int value;
	const int block = findBlock(row, column);
	for (int i = 1; i < 10; ++i)
	{
		list.push_back(i);
	}
	for (int i = 0; i < 9; ++i) {
		value = m_gridRows[row].getValue(i);
		list.erase(std::remove(list.begin(), list.end(), value), list.end());

		value = m_gridColumns[column].getValue(i);
		list.erase(std::remove(list.begin(), list.end(), value), list.end());

		value = m_gridBlocks[block].getValue(i);
		list.erase(std::remove(list.begin(), list.end(), value), list.end());
	}
	for (int i = 0; i < list.size(); ++i)
	{
		m_gridRows[row].addCandidate(column, list.at(i));
	}
}

int SudokuPuzzle::findBlock(const int row, const int column)const
{
	if (row < 3) {
		if (column < 3) {
			return 0;
		}
		if (column > 5) {
			return 2;
		}
		else {
			return 1;
		}
	}
	if (row > 5) {
		if (column < 3) {
			return 6;
		}
		if (column > 5) {
			return 8;
		}
		else {
			return 7;
		}
	}
	else {
		if (column < 3) {
			return 3;
		}
		if (column > 5) {
			return 5;
		}
		else {
			return 4;
		}
	}
}


void SudokuPuzzle::readPuzzle(const char filenameIn[]) {
	// Add code to read in a puzzle from the text file and store within the SudokuPuzzle object
	std::ifstream fin(filenameIn);
	for (int row = 0; row < 9; ++row)
	{
		for (int column = 0; column < 9; ++column)
		{
			int value;
			fin >> value;
			m_gridRows[row].setValue(column, value);
			if (value != 0) { m_gridRows[row].setGiven(column); }
		}
	}
}


void SudokuPuzzle::output() const{
	// Add code to output your solved puzzle
	std::ofstream fout("output.txt");
	for (int row = 0; row < 9; ++row)
	{
		for (int column = 0; column < 8; ++column)
		{	
			fout << m_gridRows[row].getValue(column) << " ";
		}
		fout << m_gridRows[row].getValue(8);
		fout << std::endl;
	}
}

void SudokuPuzzle::InitialiseGrid() {
	for (int row = 0; row < 9; ++row)
	{
		for (int column = 0; column < 9; ++column)
		{
			m_gridRows[row].setCell(column, new Cell());
		}
	}
	for (int column = 0; column < 9; ++column)
	{
		for (int row = 0; row < 9; ++row)
		{
			m_gridColumns[column].setCell(row, m_gridRows[row].GetCell(column));
		}
	}

	int count1 = 0;
	int count2 = 0;
	int count3 = 0;
	for (int row = 0; row < 3; ++row)
	{
		for (int column = 0; column < 3; ++column)
		{			
			m_gridBlocks[0].setCell(count1, m_gridRows[row].GetCell(column));
			++count1;
		}
		for (int column = 3; column < 6; ++column)
		{
			m_gridBlocks[1].setCell(count2, m_gridRows[row].GetCell(column));
			++count2;

		}
		for (int column = 6; column < 9; ++column)
		{
			m_gridBlocks[2].setCell(count3, m_gridRows[row].GetCell(column));
			++count3;

		}
	}
	count1 = 0;
	count2 = 0;
	count3 = 0;
	for (int row = 3; row < 6; ++row)
	{
		for (int column = 0; column < 3; ++column)
		{
			m_gridBlocks[3].setCell(count1, m_gridRows[row].GetCell(column));
			++count1;
		}
		for (int column = 3; column < 6; ++column)
		{
			m_gridBlocks[4].setCell(count2, m_gridRows[row].GetCell(column));
			++count2;

		}
		for (int column = 6; column < 9; ++column)
		{
			m_gridBlocks[5].setCell(count3, m_gridRows[row].GetCell(column));
			++count3;

		}
	}
	count1 = 0;
	count2 = 0;
	count3 = 0;
	for (int row = 6; row < 9; ++row)
	{
		for (int column = 0; column < 3; ++column)
		{
			m_gridBlocks[6].setCell(count1, m_gridRows[row].GetCell(column));
			++count1;
		}
		for (int column = 3; column < 6; ++column)
		{
			m_gridBlocks[7].setCell(count2, m_gridRows[row].GetCell(column));
			++count2;

		}
		for (int column = 6; column < 9; ++column)
		{
			m_gridBlocks[8].setCell(count3, m_gridRows[row].GetCell(column));
			++count3;

		}
	}
}