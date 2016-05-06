#pragma once
#include <string>

class candidate
{
	std::string name;
	int c;
public:
	candidate(std::string a);
	~candidate();
	
	void print(std::ostream& out);
	void inc(std::istream& in);

	friend class list;
};

