#ifndef LEX_H
#define LEX_H

enum lex_type {
	tok_error  = -1,
	tok_panic  = -2,

	tok_eof    = '\0',
	tok_nl     = '\n',
	tok_str    = '\'',
	tok_equ    = '=',
	tok_comma  = ',',
	tok_at     = '@',
	tok_obrace = '{',
	tok_cbrace = '}'
};

struct lex_tok {
	enum lex_type type;
	const char *s;
	const char *e;
};

struct lex_state {
	unsigned b;
	char buf[8192];
	const char *p;
	FILE *f;
};

void
lex_next(struct lex_state *l, struct lex_tok *t);

#endif

