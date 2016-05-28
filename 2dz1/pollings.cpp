#include "stdafx.h"
#include "pollings.h"
#include "elector.h"
#include <iostream>

pollings::pollings(std::string a)
{
	name = a;
}

pollings::~pollings()
{
}

void pollings::adde(std::string a) {
	bool k = false;
	for (int i = 0; i < v.size() && !k; i++) if (v[i]->name == a) k = true;
	if (!k) v.push_back(new elector(a));
	else throw std::runtime_error("ERROR: there is such elector!\n");
}

void pollings::dele(std::string a) {
	bool k = false;
	for (int i = 0; i < v.size() && !k; i++)
		if (v[i]->name == a) {
			v.erase(v.begin() + i);
			k = true;
		}
	if (!k) throw std::runtime_error("ERROR: there isn't such elector!\n");
}

void pollings::printe(std::ostream& out) {
	out << name << "\t" << v.size() << "\n";
	for (int i = 0; i < v.size(); i++) out << v[i]->name << "\t" << v[i]->status << "\t" << v[i]->choosen << "\n";
}

void pollings::ine(std::istream& in) {
	int n;
	in >> name >> n;
	for (int i = 0; i < n; i++) {
		std::string a;
		in >> a;
		adde(a);
		in >> v[i]->status;
		in >> v[i]->choosen;
	}
}

pollings& pollings::operator+=(pollings& p) {
	for (int i = 0; i < p.v.size(); i++) {
		this->v.push_back(p.v[i]);
	}
	return *this;
}

void pollings::printev(std::ostream& out) {
	out << name << "\n";
	for (int i = 0; i < v.size(); i++) v[i]->ch(out);
}