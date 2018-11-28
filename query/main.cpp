// This file contains code from "C++ Primer, Fourth Edition", 
// by Stanley B.Lippman, Jose Lajoie, and Barbara E. Moo
#include "Query.h"
#include "TextQuery.h"
#include <string>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char **argv)
{
    if (argc != 2)
		{cerr << "No input file" << endl; return EXIT_FAILURE;}
    ifstream infile(argv[1]);
    if (!infile)
		{cerr << "No input file!" << endl; return EXIT_FAILURE;}
	TextQuery tq(infile); // store the file in a vector and build the query map
//	tq.display_map(); // debugging aid
	
	while (true) {
		cout << "enter word to look for, or q to quit: ";
		string line;
		getline(cin, line);
		if (line.empty() || line == "q") break;
		WordQuery query(line);
		auto result = query.eval(tq);
		print(cout, result) << endl;
		
		// AndQuery aquery("Unix", "system");
		// result = aquery.eval(tq);
		// print(cout, result) << endl;
		
		// OrQuery oquery("Unix", "system");
		// result = oquery.eval(tq);
		// print(cout, result) << endl;

		// AndNQuery anquery("Unix", "system", 3);
		// result = anquery.eval(tq);
		// print(cout, result) << endl;
		// will print:
		// "Unix {3} system" occurs ...

	}
	return 0;
}
