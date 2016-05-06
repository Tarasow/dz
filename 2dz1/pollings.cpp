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
	if (!k) v.push_back(std::shared_ptr<elector>(new elector(a)));
	else std::cout << "ERROR: there is such elector!\n";
}

void pollings::dele(std::string a) {
	bool k = false;
	for (int i = 0; i < v.size() && !k; i++)
		if (v[i]->name == a) {
			v.erase(v.begin() + i);
			k = true;
		}
	if (!k) std::cout << "ERROR: there isn't such elector!\n";
}

void pollings::printe(std::ostream& out) {
	out << name << " " << v.size() << "\n";
	for (int i = 0; i < v.size(); i++) out << v[i]->name << " " << v[i]->status << " " << v[i]->choosen << "\n";
}

void pollings::ine(std::istream& in) {
	in >> name;
	int n;
	in.ignore();
	in >> n;
	in.ignore();
	for (int i = 0; i < n; i++) {
		std::string a;
		in >> a;
		adde(a);
		in.ignore();
		in >> v[i]->status;
		in.ignore();
		in >> v[i]->choosen;
		in.ignore();
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