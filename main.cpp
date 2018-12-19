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
	
	// string reg_string = "((\\s*[^\\s]+\\s)*(two)(\\s[^\\s]+){0,4}(\\sthe)(\\s[^\\s]+)*\\s*)";
	// regex reg(reg_string);
	// if (regex_match("less than two man-years were spent on the main system software. We hope, ", reg))
	// 	cout << "matched!" << endl;
	// else
	// 	cout << "not matched!" << endl;
	
	while (true) {
		cout << "Enter one or two words to look for, or q to quit:\n";
		string line;
		getline(cin, line);
		if (line.empty() || line == "q") break;
		
		regex curly_and(R"((\w*\s)(\{AND\})(\s\w*)(\s\[\d+,\d+\])?)");
		regex curly_or(R"((\w*\s)(\{OR\})(\s\w*)(\s\[\d+,\d+\])?)");
		regex curly_n(R"((\w*\s)(\{\d+\})(\s\w*)(\s\[\d+,\d+\])?)");
		regex single_word_search(R"((?!AND)(?!OR)\w+(\s\[\d+,\d+\])?)");
		regex single_word(R"(\b(?!AND\b)(?!OR\b)\w+)");
		
		vector<string> words;
		
		smatch result;
		string::const_iterator searchStart( line.cbegin() );
	    while ( regex_search( searchStart, line.cend(), result, single_word ) )
	    {
	        words.push_back(result[0]);  
	        searchStart = result.suffix().first;
	    }
		
		if (regex_match(line, curly_and)){
			// cout << "and matched" << endl;
			AndQuery aquery(words[0], words[1]);  // implemented
			auto result = aquery.eval(tq);
			if (words.size() == 2)
				print(cout, result) << endl;
			else {
				size_t start = {stoi(words[2])};
				size_t end = {stoi(words[3])};
				print(cout, result, start, end) << endl;
			}
				
		}
		else if (regex_match(line, curly_or)){
			// cout << "or matched" << endl;
			OrQuery oquery(words[0], words[1]);   // implemented
			auto result = oquery.eval(tq);
			if (words.size() == 2)
				print(cout, result) << endl;
			else {
				size_t start = {stoi(words[2])};
				size_t end = {stoi(words[3])};
				print(cout, result, start, end) << endl;
			}
		}
		else if (regex_match(line, curly_n)){
			// cout << "n matched" << endl;
			NQuery nquery(words[0], words[2], stoi(words[1]));   // need to be implemented
			auto result = nquery.eval(tq);
			if (words.size() == 3)
				print(cout, result) << endl;
			else {
				size_t start = {stoi(words[3])};
				size_t end = {stoi(words[4])};
				print(cout, result, start, end) << endl;
			}
		}
		else if (regex_match(line, single_word_search)) {
			// cout << "single matched" << endl;
			WordQuery query(words[0]);
			auto result = query.eval(tq);
			if (words.size() == 1)
				print(cout, result) << endl;
			else {
				size_t start = {stoi(words[1])};
				size_t end = {stoi(words[2])};
				print(cout, result, start, end) << endl;
			}
		}
		else {
			cout << "Unrecognized search\n" << endl;
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
