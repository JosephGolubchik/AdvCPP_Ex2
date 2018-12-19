#ifndef QUERY_H
#define QUERY_H

#include "TextQuery.h"
#include <string>
#include <set>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>

// abstract class 
class Query_base {
public:
    using line_no = TextQuery::line_no;
    Query_base() = default;
	virtual ~Query_base() = default;
    virtual QueryResult eval(const TextQuery&) const = 0; 
//private:
};

class WordQuery: public Query_base {
public:
    WordQuery(const std::string &s): query_word(s) { }
    QueryResult eval(const TextQuery &t) const
                    { return t.query(query_word); }
	std::string rep() const { return query_word; }
private:
    std::string query_word;
};
    
class AndQuery: public Query_base {
public:
    AndQuery(const std::string &left_string, const std::string &right_string): 
            left_query(WordQuery(left_string)), right_query(WordQuery(right_string)),
			s1(left_string), s2(right_string){ }
    virtual QueryResult eval(const TextQuery&) const;
protected:
    WordQuery left_query, right_query;
	const std::string s1, s2;
};

class OrQuery: public Query_base {
public:
    OrQuery(const std::string &left_string, const std::string &right_string): 
            left_query(WordQuery(left_string)), right_query(WordQuery(right_string)),
			s1(left_string), s2(right_string){ }
    QueryResult eval(const TextQuery&) const;
private:
    WordQuery left_query, right_query;
	const std::string s1, s2;
};

class NQuery: public AndQuery {
friend class QueryResult;
public:
    NQuery(const std::string &left_string, const std::string &right_string, const int words_between): 
            AndQuery(left_string, right_string), words_between(words_between){ }
    QueryResult eval(const TextQuery&) const;
private:
    const int words_between;
};

#endif
