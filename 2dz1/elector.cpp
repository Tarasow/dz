#include "stdafx.h"
#include "elector.h"
#include <iostream>

elector::elector(std::string a)
{
	name = a;
	status = false;
	choosen = "no_vote";
}

elector::~elector()
{
}

void elector::ch(std::ostream& out) {
	if (choosen == "no_vote") out << name << " did not vote\n";
	else out << name << " voted for " << choosen << "\n";
}

void elector::vote(std::string a) {
	if (!status) {
		status = true;
		choosen = a;
	}
	else throw std::runtime_error("ERROR: elector can't vote twice\n");
}

void elector::elreset() {
	status = false;
	choosen = "";
}