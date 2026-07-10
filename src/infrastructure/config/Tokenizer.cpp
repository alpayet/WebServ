#include "infrastructure/config/Tokenizer.hpp"
#include <iostream>
#include <iterator>
#include <algorithm>

Tokenizer::Tokenizer()
{

}

Tokenizer::~Tokenizer()
{

}

const std::string	etokenToStr(e_token t)
{
	switch (t)
	{
		case char_lbracket : return "char_lbracket";
		case char_rbracket : return "char_rbracket";
		case char_end : return "char_end";
		case res_word : return "res_word";
		case str_type : return "str_type";
		case int_type : return "int_type";
		default: return "NOTOKEN";
	}
}

Token	Tokenizer::tokenize(const std::string& str)
{
	Token t;
	
	for (size_t i = 0 ; i < str.size() ; )
	{
		size_t j = str.find_first_of(" \t\n\v\f\r;{}", i);
		
		if (j != std::string::npos && i == j)
		{
			if (str[j] == ';')
				tokenizeChar(t, ";");
			else if (str[j] == '{')
				tokenizeChar(t, "{");
			else if (str[j] == '}')
				tokenizeChar(t, "}");
			++i;
			continue ;
		}
		std::string sub;
		if (j == std::string::npos)
		{
			sub = str.substr(i);
			tokenizeChar(t, sub);
			break ;
		}
		sub = str.substr(i, j - i);
		tokenizeChar(t, sub);
		if (str[j] == ';')
				tokenizeChar(t, ";");
		else if (str[j] == '{')
			tokenizeChar(t, "{");
		else if (str[j] == '}')
			tokenizeChar(t, "}");
		i = j + 1;
	}
	return t;
}

void	Tokenizer::addToken(Token token)
{
	m_tokens.push_back(token);
}

void	Tokenizer::tokenizeChar(Token& t, const std::string& str)
{
	if (str.size() > 1)
	{
		tokenizeStr(t, str);
		addToken(t);
		return ;
	}

	switch (str[0])
	{
		case '{':
			t.type = char_lbracket;
			t.data = str;
			break ;
		case '}':
			t.type = char_rbracket;
			t.data = str;
			break ;
		case ';':
			t.type = char_end;
			t.data = str;
			break ;
		default:
			tokenizeStr(t, str);
	}
	addToken(t);
}

void	Tokenizer::tokenizeStr(Token& t, const std::string& str)
{
	char *ptr;

	size_t	kw_size = sizeof(keywords) / sizeof(keywords[0]);
	bool	isRes = false;
	for (size_t i = 0 ; i < kw_size ; ++i)
	{
		if (keywords[i].name == str)
		{
			isRes = true;
			break ;
		}
	}
	if (isRes)
	{
		t.type = res_word;
		t.data = str;
	}
	else if (strtol(str.c_str(), &ptr, 10), !(*ptr))
	{
		t.type = int_type;
		t.data = str;
	}
	else
	{
		t.type = str_type;
		t.data = str;
	}
}

/** GETTERS & SETTERS*/
std::string 		Tokenizer::getFile() const { return m_file; };

std::vector<Token>	Tokenizer::getTokens() const { return m_tokens; };

std::ostream& operator<<(std::ostream& os, const Tokenizer& t)
{
	std::vector<Token> tokens;
	
	tokens = t.getTokens();
	std::vector<Token>::iterator ite = tokens.end();
	for (std::vector<Token>::iterator it = tokens.begin() ; it != ite ; *it++)
	{
		os << "Type: " << etokenToStr(it->type);
		os << "\nData: '" << it->data << "'" << std::endl;
	}
	return os;
}
