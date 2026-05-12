#ifndef TOKENIZER_HPP
# define TOKENIZER_HPP

# include <string>
# include <vector>

# include "Config/keywords.h"

/** UTILS */
// enum e_token
// {
// 	char_lbracket,
// 	char_rbracket,
// 	char_end,
// 	res_word,
// 	str_type,
// 	int_type
// };

// typedef struct s_token
// {
// 	e_token		type;
// 	std::string	data;
// }	Token;

// enum e_block
// {
// 	multi,
// 	uniq,
// 	inloc
// };

// struct Keyword
// {
// 	std::string	name;
// 	int			type;
// 	int			max_args;
// 	int			e_block;
// };

// static const Keyword keywords[] = {
// 	{"server",				 str_type, 0, multi},
// 	{"root",				 str_type, 1, inloc}, // maybe multi
// 	{"index",				 str_type, 9, inloc}, // maybe multi
// 	{"error_page",			 str_type, 2, multi},
// 	{"location",			 str_type, 1, uniq},
// 	{"listen",				 int_type, 1, uniq},
// 	{"interface",			 str_type, 1, uniq},
// 	{"client_max_body_size", int_type, 1, uniq},
// 	{"cgi",					 str_type, 1, inloc},
// 	{"allow_methods",		 str_type, 3, inloc},
// 	{"autoindex",			 str_type, 1, inloc},
// 	{"return",				 int_type, 1, inloc}
// };

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
		//? maybe namespace utils
		void	tokenizeChar(Token& t, std::string str);
		void	tokenizeStr(Token& t, std::string str);
		void	tokenizeInt(Token& t, int nb);
};

std::ostream& operator<<(std::ostream& os, const Tokenizer& t);

#endif
