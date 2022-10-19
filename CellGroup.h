#pragma once
#include "cell.h"
class CellGroup
{
public:
	CellGroup(void);
	CellGroup(const CellGroup& c);
	~CellGroup(void);
	CellGroup& operator=(const CellGroup& rhs);

	//Methods
	void setCell(const int index, Cell* cell);

	void setValue(const int index, const int value);

	Cell* GetCell(const int index)const;

	int getValue(const int index)const;

	bool getGiven(const int index)const;

	void addCandidate(const int index, const int number);

	const std::vector<int>& getCandidates(const int index)const;

	void emptyCandidates(const int index);

	void setGiven(const int index);

private:
	Cell* m_cells[9];
};

inline void CellGroup::setCell(const int index, Cell*const cell) {
	m_cells[index] = cell;
}

inline void CellGroup::setValue(const int index, const int value) {
	m_cells[index]->setValue(value);
}

inline int CellGroup::getValue(const int index) const {
	return m_cells[index]->getValue();
}

inline bool CellGroup::getGiven(const int index) const {
	return m_cells[index]->getGiven();
}

inline void CellGroup::addCandidate(const int index, const int number) {
	m_cells[index]->addCandidate(number);
}

inline const std::vector<int>& CellGroup::getCandidates(const int index) const {
	return m_cells[index]->getCandidates();
}

inline void CellGroup::emptyCandidates(const int index) {
	m_cells[index]->emptyCandidates();
}

inline void CellGroup::setGiven(const int index) {
	m_cells[index]->setGiven();
}

