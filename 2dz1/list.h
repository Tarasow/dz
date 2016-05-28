#pragma once
#include "elector.h"
#include "pollings.h"
#include "candidate.h"
#include "es.h"
#include <string>
#include <vector>

class list
{
	es status;
	std::vector<candidate*> c;
	std::vector<pollings*> p;
public:
	list();
	~list();

	void cs(es a);
	void getstatus(std::ostream& out);
	void addp(std::string a);
	void delp(std::string a);
	void adde(std::string a, std::string b);
	void dele(std::string a, std::string b);
	void addc(std::string a);
	void delc(std::string a);
	void merge(std::string a, std::string b);
	void listp(std::ostream& out);
	void liste(std::string a, std::ostream& out);
	void listc(std::ostream&out);
	void vote(std::string a, std::string b);
	void printres(std::ostream& out);
	void printstat(std::ostream& out);
	void printps(std::string a, std::ostream& out);
	void printpsev(std::string a, std::ostream& out);
	void printel(std::string a, std::ostream& out);
	void sif(std::ostream& out);
	void lff(std::istream& in);
	void reset(std::string a, std::ostream& out);
};