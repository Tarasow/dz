#include "stdafx.h"
#include "list.h"
#include "pollings.h"
#include "candidate.h"
#include <iostream>
#include <algorithm>
#include <stdexcept>

list::list()
{
	status = preparing; //preparing, created, started, finished
}


list::~list()
{
}

void list::cs(es a) {
	status = a;
}

void list::getstatus(std::ostream& out) {
	if (status == preparing) out << "Preparation\n";
	if (status == created) out << "Created\n";
	if (status == started) out << "Started\n";
	if (status == finished) out << "Finished\n";
}

void list::addp(std::string a) {
	if (status == preparing) {
		bool k = false;
		for (int i = 0; i < p.size() && !k; i++) 
			if (p[i]->name == a) {
				throw std::runtime_error("ERROR: there is such polling station!\n");
				k = true;
			}
		if (!k) p.push_back(new pollings(a));
	}
	else throw std::runtime_error("ERROR: can't add polling station at this stage!\n");
};


void list::delp(std::string a) {
	if (status == preparing) {
		bool k = false;
		for (int i = 0; i < p.size() && !k; i++)
			if (p[i]->name == a) {
				p.erase(p.begin() + i);
				k = true;
			}
		if (!k) throw std::runtime_error("ERROR: there isn't such polling station!\n");
	}
	else throw std::runtime_error("ERROR: can't delete polling station at this stage!\n");
};


void list::adde(std::string a, std::string b) {
	if (status == preparing) {
		bool q = false;
		int e = 0;
		for (int i = 0; i < p.size() && !q; i++)
			if (p[i]->name == b) {
				q = true;
				e = i;
			}
		if (!q) throw std::runtime_error("ERROR: there is no such polling station!\n");
		else p[e]->adde(a);
	}
	else throw std::runtime_error("ERROR: can't add elector at this stage!\n");
};


void list::dele(std::string a, std::string b) {
	if (status == preparing) {
		bool q = false;
		int e = 0;
		for (int i = 0; i < p.size() && !q; i++)
			if (p[i]->name == b) {
				q = true;
				e = i;
			}
		if (!q) throw std::runtime_error("ERROR: there is no such polling station!\n");
		else p[e]->dele(a);
	}
	else throw std::runtime_error("ERROR: can't delete elector at this stage!\n");
};


void list::addc(std::string a) {
	if (status == created) {
		bool k = false;
		for (int i = 0; i < c.size() && !k; i++) if (c[i]->name == a) k = true;
		if (!k) c.push_back(new candidate(a));
		else throw std::runtime_error("ERROR: there is such candidate!\n");
	}
	else throw std::runtime_error("ERROR: can't add candidate at this stage!\n");
};


void list::delc(std::string a) {
	if (status == created) {
		bool k = false;
		for (int i = 0; i < c.size() && !k; i++)
			if (c[i]->name == a) {
				c.erase(c.begin() + i);
				k = true;
			}
		if (!k) throw std::runtime_error("ERROR: there isn't such candidate!\n");
	}
	else throw std::runtime_error("ERROR: can't delete candidate at this stage!\n");
};


void list::merge(std::string a, std::string b) {
	if (status == preparing) {
		bool k = false, q = false;
		int n, m;
		for (int i = 0; i < p.size() && !k; i++)
			if (p[i]->name == a) {
				k = true;
				n = i;
			}
		for (int i = 0; i < p.size() && !q; i++)
			if (p[i]->name == b) {
				q = true;
				m = i;
			}
		if (k && q) {
			(*p[n]) += (*p[m]);
			p.erase(p.begin() + m);
		}
		if (!k) throw std::runtime_error("ERROR: there isn't first polling station\n");
		if (!q) throw std::runtime_error("ERROR: there isn't second polling station\n");
	}
	else throw std::runtime_error("ERROR: can't merge polling stations at this stage!\n");
}

void list::listp(std::ostream& out) {
	for (int i = 0; i < p.size(); i++) out << p[i]->name << "\n";
}

void list::liste(std::string a, std::ostream& out) {
	bool k = false;
	for (int i = 0; i < p.size() && !k; i++) 
		if (p[i]->name == a) {
			for (int j = 0; j < p[i]->v.size(); j++) out << p[i]->v[j]->name << "\n";
			k = true;
		}
	if (!k) throw std::runtime_error("Error! There is no such polling station!\n");
}

void list::listc(std::ostream&out) {
	if (status == created) for (int i = 0; i < c.size(); i++) out << c[i]->name << "\n";
	else if (status == started || started == finished) {
		out << "Candidate:\tVotes:\n";
		for (int i = 0; i < c.size(); i++) c[i]->print(out);
	}
	else throw std::runtime_error("ERROR: there are no any candidates at this stage!\n");
};

void list::vote(std::string a, std::string b) {
	if (status == started) {
		bool k = false, q = false;
		int d = 0;
		for (int i = 0; i < c.size(); i++) if (c[i]->name == b) {
			q = true;
			d = i;
		}
		if (q) {
			for (int i = 0; i < p.size() && !k; i++) {
				for (int j = 0; j < p[i]->v.size() && !k; j++) {
					if (p[i]->v[j]->name == a) {
						p[i]->v[j]->vote(b);
						(c[d]->c)++;
						k = true;
					}
				}
			}
		}
		if (q && !k) throw std::runtime_error("ERROR: there is no such elector!\n");
		else if (!q) throw std::runtime_error("ERROR: there is no such candidate!\n");
	}
	else throw std::runtime_error("ERROR: can't vote at this stage!\n");
}

void list::printres(std::ostream& out) {
	if (status == finished && c.size() > 0) {
		bool k = false;
		int sum = 0;
		for (int i = 0; i < c.size(); i++) sum += c[i]->c;
		if (sum > 0) {
			sort(c.begin(), c.end(), [](candidate* const &f, candidate* const&s) {return f->c < s->c;});
			if (c[c.size() - 1]->c == c[c.size() - 2]->c) {
				out << "NO WINNER: same number of votes!\n";
				k = true;
			}
			if (!k) out << "Winner:\n";
			else out << "Top candidates:\n";
			int i = 1;
			do {
				out << c[c.size() - i]->name << " with " << (double)c[c.size() - i]->c * 100 / sum << "% of votes\n";
				i++;
			} while (i <= c.size() && c[c.size() - i + 1]->c == c[c.size() - i]->c);
		}
		else out << "ERROR: no any votes!\n";
	}
	else if (c.size() == 0) out << "ERROR: nobody wants to be choosen :c\n";
	else out << "ERROR: can't get result at this stage!\n";
};


void list::printstat(std::ostream& out) {
	if (status == finished && c.size() > 0) {
		int sum = 0;
		for (int i = 0; i < c.size(); i++) sum += c[i]->c;
		if (sum > 0) {
			sort(c.begin(), c.end(), [](candidate* const &f, candidate* const&s) {return f->c < s->c;});
			out << "Statistics of candidates: \n";
			for (int i = 0; i < c.size(); i++)
				out << c[c.size() - i - 1]->name << " with " << (double)c[c.size() - i - 1]->c * 100 / sum << "% of votes\n";
		}
		else out << "ERROR: no any votes!\n";
	}
	else if (c.size() == 0) out << "ERROR: nobody wants to be choosen :c\n";
	else out << "ERROR: can't get result at this stage!\n";
};

void list::printps(std::string a, std::ostream& out) {
	if (status == finished) {
		bool k = false;
		int sum = 0;
		std::vector<int> st;
		for (int i = 0; i < p.size() && !k; i++) {
			if (p[i]->name == a) {
				k = true;
				for (int j = 0; j < c.size(); j++) {
					st.push_back(0);
					for (int l = 0; l < p[i]->v.size(); l++) {
						if (p[i]->v[l]->choosen == c[j]->name) st[j]++;
					}
					sum += st[j];
				}
			}
		}
		if (!k) out << "ERROR: there is no such polling station\n";
		else for (int i = 0; i < c.size(); i++) {
			out << c[i]->name << " gets " << (double)st[i] * 100 / sum << "% of votes\n";
		}
	}
	else out << "ERROR: can't get result at this stage!\n";
};

void list::printpsev(std::string a, std::ostream& out) {
	if (status == finished) {
		bool k = false;
		for (int i = 0; i < p.size() && !k; i++) {
			if (p[i]->name == a) {
				k = true;
				p[i]->printev(out);
			}
		}
		if (!k) out << "ERROR: there is no such polling station\n";
	}
	else out << "ERROR: can't get result at this stage!\n";
}

void list::printel(std::string a, std::ostream& out) {
	if (status == finished) {
		bool k = false;
		for (int i = 0; i < p.size() && !k; i++)
			for (int j = 0; j < p[i]->v.size() && !k; j++)
				if (p[i]->v[j]->name == a) {
					p[i]->v[j]->ch(out);
					k = true;
				}
		if (!k) throw std::runtime_error("ERROR: there is no such elector!\n");
	}
	else out << "ERROR: can't get result at this stage!\n";
}

void list::sif(std::ostream& out) {
	out << p.size() << "\n";
	for (int i = 0; i < p.size(); i++)
		p[i]->printe(out);
	out << c.size() << "\n";
	for (int i=0; i<c.size(); i++)
		c[i]->print(out);
	out << status;
};


void list::lff(std::istream& in) {
	int n;
	in >> n;
	status = preparing;
	for (int i = 0; i < n; i++) {
		addp(" ");
		p[i]->ine(in);
	}
	in >> n;
	status = created;
	for (int i = 0; i < n; i++) {
		addc(" ");
		c[i]->inc(in);
	}
	int a;
	in >> a;
	status = static_cast<es>(a);
};

void list::reset(std::string a, std::ostream& out) {
	if (a == "all") {
		status = preparing;
		p.erase(p.begin(), p.end());
		c.erase(c.begin(), c.end());
		out << "All was reset!\n";
	}
	else if (a == "candidates") {
		status = preparing;
		for (int i = 0; i < p.size(); i++)
			for (int j = 0; j < p[i]->v.size(); j++)
				p[i]->v[j]->elreset();
		c.erase(c.begin(), c.end());
		out << "Candidates were reset (status of elections - preparing)\n";
	}
	else if (a == "votes") {
		status = created;
		for (int i = 0; i < p.size(); i++)
			for (int j = 0; j < p[i]->v.size(); j++)
				p[i]->v[j]->elreset();
		for (int i = 0; i < c.size(); i++) c[i]->c = 0;
		out << "Votes were reset!\n";
	}
}