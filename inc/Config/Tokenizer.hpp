#ifndef TOKENIZER_HPP
# define TOKENIZER_HPP

# include <string>
# include <vector>

# include "Config/keywords.h"

static const std::string stops[] = { " ", "\t", "\n", "\v",
										"\f", "\r" };

class Tokenizer
{
	public:
		/** CONSTRUCTORS */
		Tokenizer();
		Tokenizer(Tokenizer& other);
		Tokenizer&	operator=(Tokenizer& other);
		~Tokenizer();

		
		/** FUNCTIONS */
		Token	tokenize(std::string str);
		void	addToken(Token token);

		/** GETTERS & SETTERS*/
		std::string 		getFile() const;
		std::vector<Token>	getTokens() const;

	private:
		std::string			m_file;
		std::vector<Token>	m_tokens;

		void	tokenizeChar(Token& t, std::string str);
		void	tokenizeStr(Token& t, std::string str);
		void	tokenizeInt(Token& t, int nb);
};

std::ostream& operator<<(std::ostream& os, const Tokenizer& t);

#endif
