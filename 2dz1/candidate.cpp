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
	out << name << " - " << c << "\n";
}

void candidate::inc(std::istream& in) {
	in >> name;
	in.ignore();
	in.ignore();
	in.ignore();
	in >> c;
	in.ignore();
}