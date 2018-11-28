#include "Query.h"
#include "TextQuery.h"
#include <memory>
#include <set>
#include <algorithm>
#include <iostream>
#include <cstddef>
#include <iterator>
using namespace std;

QueryResult
AndQuery::eval(const TextQuery& text) const
{
    auto left = left_query.eval(text), right = right_query.eval(text);
	// set to hold the intersection of left and right
    auto ret_lines = make_shared<set<line_no>>();  
    // writes the intersection of two ranges to a destination iterator
    set_intersection(left.begin(), left.end(), 
                   right.begin(), right.end(),
                   inserter(*ret_lines, ret_lines->begin()));
    return QueryResult(s1 + " {AND} " + s2, ret_lines, left.get_file());
}

QueryResult
OrQuery::eval(const TextQuery& text) const
{
    auto left = left_query.eval(text), right = right_query.eval(text); 
	// copy the line numbers from the left-hand operand into the result set
	auto ret_lines = 
	     make_shared<set<line_no>>(left.begin(), left.end());
	// insert lines from the right-hand operand
	ret_lines->insert(right.begin(), right.end());
	// return the new QueryResult representing the union of lhs and rhs
    return QueryResult(s1 + " {OR} " + s2, ret_lines, left.get_file());
}

ostream &print(ostream &os, const QueryResult &qr)
{
    // if the word was found, print the count and all occurrences
    os << "\"" << qr.sought << "\" occurs " << qr.lines->size() << " times" << endl;

    // print each line in which the word appeared
	for (auto num : *qr.lines) // for every element in the set 
        os << "(line " << num + 1 << ") " 
		   << *(qr.file->begin() + num) << endl;
	return os;
}


