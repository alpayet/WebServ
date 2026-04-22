#include "Tokenizer.hpp"
#include <algorithm>

Tokenizer::Tokenizer()
{

}

Tokenizer::Tokenizer(Tokenizer& other)
{
	(void)(other);
}

Tokenizer&	Tokenizer::operator=(Tokenizer& other)
{

	(void)(other);
	return *this;
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

#include <iostream>
Token	Tokenizer::tokenize(std::string str)
{
	Token t;

	for (size_t i = 0 ; i < str.size() ; )
	{
		size_t j = str.find_first_of(" \t\n\v\f\r", i);
		if (j != std::string::npos)
		{
			if (i == j)
			{
				++i;
				continue ;
			}
			std::string sub = str.substr(i, j - i);
			if (sub[sub.size() - 1] == ';')
			{
				std::string sub2 = sub.substr(0, sub.size() - 1);
				tokenizeChar(t, sub2);
				tokenizeChar(t, ";");
				++j;
			}
			else
				tokenizeChar(t, sub);
		}
		else
		{
			tokenizeChar(t, &str[i]);
			break ;
		}
		i = j + 1;
	} 
	return t;
}

void	Tokenizer::addToken(Token token)
{
	m_tokens.push_back(token);
}

void	Tokenizer::tokenizeChar(Token& t, std::string str)
{
	if (str.size() > 1)
	{
		tokenizeStr(t, str);
		addToken(t);
		return ;
	}

	char c = str[0];
	switch (c)
	{
		case '{':
			t.type = char_lbracket;
			t.data = c;
			break ;
		case '}':
			t.type = char_rbracket;
			t.data = c;
			break ;
		case ';':
			t.type = char_end;
			t.data = c;
			break ;
		default:
			tokenizeStr(t, str);
	}
	addToken(t);
}

void	Tokenizer::tokenizeStr(Token& t, std::string str)
{
	char *ptr;

	size_t res_size = sizeof(reserved) / sizeof(reserved[0]);
	if (std::find(reserved, reserved + res_size, str) != reserved + res_size)
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

void	Tokenizer::tokenizeInt(Token& t, int nb)
{
	(void) (t);
	(void) (nb);
}

/** GETTERS & SETTERS*/
std::string 		Tokenizer::getFile() const { return m_file; };

std::vector<Token>	Tokenizer::getTokens() const { return m_tokens; };
#include <iterator>
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
