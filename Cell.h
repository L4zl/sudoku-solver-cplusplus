#pragma once
#include <vector>
class Cell
{ 
public:
	Cell(void);
	~Cell(void);
	
	// Methods

	void setValue(const int value);
	void addCandidate(const int number);
	void emptyCandidates();
	void setGiven();
	int getValue()const;
	bool getGiven()const;
	const std::vector<int>& getCandidates()const;

private:
	std::vector<int> m_candidateList;	
	int m_value;
	bool m_given;
};

inline void Cell::setValue(const int value) {
	m_value = value;
}

inline void Cell::addCandidate(const int number) {
	m_candidateList.push_back(number);
}

inline void Cell::emptyCandidates() {
	m_candidateList.clear();
}

inline void Cell::setGiven() {
	m_given = true;
}

inline int Cell::getValue() const {
	return m_value;
}

inline bool Cell::getGiven() const {
	return m_given;
}

inline const std::vector<int>& Cell::getCandidates() const {
	;
	return m_candidateList;
}