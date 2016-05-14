#include "stdafx.h"
#include "candidate.h"

candidate::candidate(std::string a)
{
	name = a;
	c = 0;
}

candidate::~candidate()
{
}

void candidate::print(std::ostream& out) {
	out << name << "\t\t" << c << "\n";
}

void candidate::inc(std::istream& in) {
	in >> name >> c;
}