#ifndef TOKENIZER_HPP
# define TOKENIZER_HPP

# include <string>
# include <vector>

/** UTILS */
enum e_token
{
	char_lbracket,
	char_rbracket,
	char_end,
	res_word,
	str_type,
	int_type
};

typedef struct s_token
{
	e_token		type;
	std::string	data;
}	Token;

static const std::string reserved[] = { "server", "location", "listen", "server_name",
										"root", "index", "proxy_pass", "error_page",
										"cgi", "allow_methods", "client_max_body_size",
										"autoindex" };

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
		//? maybe namespace utils
		void	tokenizeChar(Token& t, std::string str);
		void	tokenizeStr(Token& t, std::string str);
		void	tokenizeInt(Token& t, int nb);

		/** GETTERS & SETTERS*/
		std::string 		getFile() const;
		std::vector<Token>	getTokens() const;

	private:
		std::string			m_file;
		std::vector<Token>	m_tokens;
};

std::ostream& operator<<(std::ostream& os, const Tokenizer& t);

#endif
