// 2dz1.cpp: определяет точку входа для консольного приложения.
//

#pragma once
#include "stdafx.h"
#include "elector.h"
#include "pollings.h"
#include "candidate.h"
#include "list.h"
#include <iostream>
#include <fstream>
#include <string>

using std::cin;
using std::cout;

int main()
{
	cout << "Use 'help' command to view reference\n\n";
	list e;
	std::string a, b, c;
	bool k = false;
	while (!k) {
		cin >> a;

		if (a == "create") {
			e.cs('c');
			cout << "Created!\n";
		}

		else if (a == "start") {
			e.cs('s');
			cout << "Started!\n";
		}

		else if (a == "finish") {
			e.cs('f');
			e.printres(cout);
		}

		else if (a == "getstatus") e.getstatus();

		else if (a == "add") {
			cin >> b;
			if (b == "pollings") {
				cin >> b;
				e.addp(b);
			}
			else if (b == "elector") {
				cin >> b;
				cin >> c;
				e.adde(b, c);
			}
			else if (b == "candidate") {
				cin >> b;
				e.addc(b);
			}
			else cout << "ERROR: unknown command!\n";
		}

		else if (a == "del") {
			cin >> b;
			if (b == "pollings") {
				cin >> b;
				e.delp(b);
			}
			else if (b == "elector") {
				cin >> b;
				cin >> c;
				e.dele(b, c);
			}
			else if (b == "candidate") {
				cin >> b;
				e.delc(b);
			}
			else cout << "ERROR: unknown command!\n";
		}

		else if (a == "merge") {
			cin >> b;
			cin >> c;
			e.merge(b, c);
		}
		
		else if (a == "listp") e.listp(cout);

		else if (a == "liste") {
			cin >> b;
			e.liste(b, cout);
		}

		else if (a == "listc") e.listc(cout);

		else if (a == "vote") {
			cin >> b;
			cin >> c;
			e.vote(b, c);
		}

		else if (a == "printres") e.printres(cout);

		else if (a == "printstat") e.printstat(cout);

		else if (a == "printps") {
			cin >> b;
			e.printps(b, cout);
		}

		else if (a == "printpsev") {
			cin >> b;
			e.printpsev(b, cout);
		}

		else if (a == "printel") {
			cin >> b;
			e.printel(b, cout);
		}

		else if (a == "reset") {
			cin >> b;
			e.reset(b);
		}

		else if (a == "saveinfile") {
			std::ofstream f("elections.txt");
			e.sif(f);
			f.close();
			cout << "The data was saved!\n";
		}

		else if (a == "loadfromfile") {
			std::ifstream f("elections.txt");
			if (f.is_open()) {
				e.lff(f);
				f.close();
				cout << "The data was loaded!\n";
			}
			else cout << "ERROR: can't open file!\n";
		}
		
		else if (a == "help") {
			cout << "create\t\tcreate elections\nstart\t\tstart elections\nfinish\t\tfinish elections\ngetstatus\tget current status of elections\n";
			cout << "add pollings <name>\nadd elector <name> <pollings>\nadd candidate <name>\ndel pollings <name>\ndel elector <name> <pollings>\ndel candidate <name>\n";
			cout << "merge <pollings_in> <pollings_from>\nlistp\t\tview list of polling stations\nliste <name>\tview list electors in polling station <name>";
			cout << "\nlistc\t\tview list of candidates\nvote <el> <can>\telector <el> vote for candidate <can>\nprintres\tprint the result of elections\n";
			cout << "printstat\tprint statisics of elections\nprintps <name>\tprint statistics on polling station <name>\nprintpsev <name>print statistics on polling station for electors\n";
			cout << "printel <name>\tprint elector <name> choice\nreset <...>\treset <all> or <candidates> or <votes>\n";
			cout << "saveinfile\tsave current elections in file\nloadfromfile\tload elections from file\nexit\t\tquit program\n\n";
		}

		else if (a == "exit") {
			cout << "Are you sure you want to quit? Unsaved data will be lost!\nPress 'yes' if you are sure, else any key\n";
			cin >> b;
			if (b == "yes") k = true;
		}

		else cout << "ERROR: unknown command!\n";
		cout << "\n";
	}

	system("pause");
    return 0;
}

