// This file contains code from "C++ Primer", 
// by Stanley B.Lippman, Jose Lajoie, and Barbara E. Moo
#include "Query.h"
#include "TextQuery.h"
#include <string>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <fstream>
#include <regex>
using namespace std;

int main(int argc, char **argv)
{
    if (argc != 2)
		{cerr << "No input file" << endl; return EXIT_FAILURE;}
    ifstream infile(argv[1]);
    if (!infile)
		{cerr << "No input file!" << endl; return EXIT_FAILURE;}
	TextQuery tq(infile); // store the file in a vector and build the query map
	// tq.display_map();     // debugging aid
	
	while (true) {
		cout << "Enter one or two words to look for, or q to quit:\n";
		string line;
		getline(cin, line);
		if (line.empty() || line == "q") break;
		
		regex curly_and(R"((\w*\s)(\{AND\})(\s\w*))");
		regex curly_or(R"((\w*\s)(\{OR\})(\s\w*))");
		regex single_word(R"((^\w+)|(\w+$))");
		
		vector<string> words;
		
		smatch result;
		string::const_iterator searchStart( line.cbegin() );
	    while ( regex_search( searchStart, line.cend(), result, single_word ) )
	    {
	        words.push_back(result[0]);  
	        searchStart = result.suffix().first;
	    }
	    cout << endl;
		
		if (regex_match(line, curly_and)){
			AndQuery aquery(words[0], words[1]);  // implemented
			auto result = aquery.eval(tq);
			print(cout, result) << endl;
		}
		else if (regex_match(line, curly_or)){
			OrQuery oquery(words[0], words[1]);   // implemented
			auto result = oquery.eval(tq);
			print(cout, result) << endl;
		}
		else {
			WordQuery query(words[0]);
			auto result = query.eval(tq);
			print(cout, result) << endl;
		}
		
		
		
		// WordQuery query(line);
		// auto result = query.eval(tq);
		// print(cout, result) << endl;
		
		// AndQuery aquery("Unix", "system");  // implemented
		// result = aquery.eval(tq);
		// print(cout, result) << endl;
		
		// OrQuery oquery("Unix", "system");   // implemented
		// result = oquery.eval(tq);
		// print(cout, result) << endl;

		// NQuery nquery("Unix", "system", 3); // need to be implemented
		// result = nquery.eval(tq);
		// print(cout, result) << endl;
		// will print:
		// "Unix {3} system" occurs ...

	}
	return 0;
}
