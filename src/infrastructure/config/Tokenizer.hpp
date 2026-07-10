#ifndef TOKENIZER_HPP
# define TOKENIZER_HPP

# include <string>
# include <vector>
# include "infrastructure/config/keywords.hpp"

static const std::string stops[] = { " ", "\t", "\n", "\v",
										"\f", "\r" };

class Tokenizer
{
	public:
		/** CONSTRUCTORS */
		Tokenizer();
		~Tokenizer();

		
		/** FUNCTIONS */
		Token	tokenize(const std::string& str);
		void	addToken(Token token);

		/** GETTERS & SETTERS*/
		std::string 		getFile() const;
		std::vector<Token>	getTokens() const;

	private:
		std::string			m_file;
		std::vector<Token>	m_tokens;

		void	tokenizeChar(Token& t, const std::string& str);
		void	tokenizeStr(Token& t, const std::string& str);
		
		Tokenizer(Tokenizer& other);
		Tokenizer&	operator=(Tokenizer& other);
};

std::ostream& operator<<(std::ostream& os, const Tokenizer& t);

#endif
