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
	uniq,
	multi
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
	int			max_args;
	int			e_uniqness;
	int			e_block;
};

static const Keyword keywords[] = {
	{"server",				 str_type, 0, multi, inserv},
	{"root",				 str_type, 1, uniq, both}, // maybe multi
	{"index",				 str_type, 9, uniq, both}, // maybe multi
	// {"root",				 str_type, 1, inloc}, // maybe multi
	// {"index",				 str_type, 9, inloc}, // maybe multi
	{"error_page",			 str_type, 2, multi, inserv},
	{"location",			 str_type, 1, multi, inserv},
	{"listen",				 int_type, 1, uniq, inserv},
	{"server_name",			 str_type, 1, uniq, inserv},
	{"client_max_body_size", int_type, 1, uniq, inserv},
	{"cgi",					 str_type, 1, inloc, inloc},
	{"allow_methods",		 str_type, 3, inloc, inloc},
	{"autoindex",			 str_type, 1, inloc, inloc},
	{"return",				 int_type, 1, inloc, inloc}
};



#endif
