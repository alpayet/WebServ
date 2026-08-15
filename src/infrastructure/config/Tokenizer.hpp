#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include "infrastructure/config/keywords.hpp"
#include <string>
#include <vector>

namespace webserv {
static std::string const stops[] = {" ", "\t", "\n", "\v", "\f", "\r"};

class Tokenizer
{
  public:
	/** CONSTRUCTORS */
	Tokenizer();
	~Tokenizer();

	/** FUNCTIONS */
	Token tokenize(std::string const &str);
	void  addToken(Token token);

	/** GETTERS & SETTERS*/
	std::string		   getFile() const;
	std::vector<Token> getTokens() const;

  private:
	std::string		   m_file;
	std::vector<Token> m_tokens;

	void tokenizeChar(Token &t, std::string const &str);
	void tokenizeStr(Token &t, std::string const &str);

	Tokenizer(Tokenizer &other);
	Tokenizer &operator=(Tokenizer &other);
};

std::ostream &operator<<(std::ostream &os, Tokenizer const &t);
} // namespace webserv

#endif
