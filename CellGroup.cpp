#include "CellGroup.h"
#include "Cell.h"

CellGroup::CellGroup(void) : m_cells(){}

CellGroup::CellGroup(const CellGroup& c) : m_cells() { *m_cells = *(c.m_cells); }

CellGroup::~CellGroup(void) {}

CellGroup& CellGroup::operator=(const CellGroup& rhs)
{
	if (&rhs != this) {
		(*this->m_cells) = (*rhs.m_cells);
	}
	return *this;
}

Cell* CellGroup::GetCell(const int index) const{
	return m_cells[index];
}