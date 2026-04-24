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

enum e_block
{
	whateva,
	must_be_alone,
	must_be_in_loc
};

struct Keyword
{
	std::string	name;
	int			type;
	int			max_args;
	int			e_block;
};

static const Keyword keywords[] = {
	{"server", str_type, 0, whateva},
	{"location", str_type, 1, must_be_alone},
	{"listen", int_type, 1, must_be_alone},
	{"server_name", str_type, 1, must_be_alone},
	{"root", str_type, 1, whateva},
	{"index", str_type, 200000000, whateva},
	// {"proxy_pass", str_type, 1},
	{"error_page", str_type, 2, must_be_alone},
	{"cgi", str_type, 1, must_be_in_loc},
	{"allow_methods", str_type, 3, must_be_in_loc},
	{"client_max_body_size", int_type, 1, must_be_alone},
	{"autoindex", str_type, 1, must_be_in_loc},
	{"return", int_type, 1, must_be_in_loc}
};

static const std::string reserved[] = { "server", "location", "listen", "server_name",
										"root", "index", "error_page",
										"cgi", "methods", "client_max_body_size",
										"autoindex", "return" };

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
