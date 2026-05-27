#ifndef KEYWORDS_H
# define KEYWORDS_H

# include <string>

enum e_token
{
	char_lbracket,
	char_rbracket,
	char_end,
	res_word,
	str_type,
	int_type
};

struct Token
{
	e_token		type;
	std::string	data;
};

enum e_uniqness
{
	multi,
	uniq
};

enum e_block
{
	inserv,
	inloc,
	both
};

struct Keyword
{
	std::string	name;
	int			type;
	int			min_args;
	int			max_args;
	int			e_uniqness;
	int			e_block;
};

static const Keyword keywords[] = {
	{"server",				 str_type, 0, 0, multi, inserv},
	{"root",				 str_type, 1, 1, uniq, both},
	{"index",				 str_type, 1, 9, uniq, both},
	{"error_page",			 str_type, 2, 2, multi, inserv},
	{"location",			 str_type, 1, 1, multi, inserv},
	{"listen",				 int_type, 1, 1, uniq, inserv},
	{"interface",			 str_type, 1, 1, uniq, inserv},
	{"client_max_body_size", int_type, 1, 1, uniq, inserv},
	{"proxy_pass",			 str_type, 1, 1, uniq, inloc},
	{"allow_methods",		 str_type, 1, 3, uniq, inloc},
	{"autoindex",			 str_type, 1, 1, uniq, inloc},
	{"return",				 int_type, 1, 1, uniq, inloc}
};



#endif
