#pragma once
#include "elector.h"
#include <string>
#include <vector>
#include <memory>

class pollings
{
	std::string name;
	std::vector<elector*> v;
public:
	pollings(std::string a);
	~pollings();

	void adde(std::string a);
	void dele(std::string a);
	void printe(std::ostream& out);
	void ine(std::istream& out);
	pollings& operator+= (pollings& p);
	void printev(std::ostream& out);

	friend class list;
};

