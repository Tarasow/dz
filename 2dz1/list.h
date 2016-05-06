#pragma once
#include "elector.h"
#include "pollings.h"
#include "candidate.h"
#include <string>
#include <vector>
#include <memory>

class list
{
	char es;
	std::vector<std::shared_ptr<candidate>> c;
	std::vector<std::shared_ptr<pollings>> p;
public:
	list();
	~list();

	void cs(char a);
	void getstatus();
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
	void reset(std::string a);
};

