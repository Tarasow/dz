#pragma once
#include <string>

class elector
{
private:
	std::string name;
	bool status;
	std::string choosen;
public:
	elector(std::string a);
	~elector();

	void vote(std::string a);
	void ch(std::ostream& out);
	void elreset();

	friend class pollings;
	friend class list;
};

