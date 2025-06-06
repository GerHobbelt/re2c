/* Generated by re2c */
#line 1 "ctx_b.re"
// re2c $INPUT -o $OUTPUT -b
#include <cstring>
#include <iostream>

struct Scanner
{
	Scanner(char *txt)
		: cur(txt), lim(txt + strlen(txt))
	{
	}
	
	char    *cur;
	char    *lim;
	char	*ptr;
	char	*ctx;
	char    *tok;
};

#define	YYCTYPE		char
#define	YYCURSOR	s.cur
#define	YYLIMIT		s.lim
#define	YYMARKER	s.ptr
#define	YYCTXMARKER	s.ctx
#define	YYFILL(n)	

enum What
{
	UNEXPECTED,
	KEYWORD,
	NUMBER,
	EOI
};

char * tokens[] = { "UNEXPECTED", "KEYWORD", "NUMBER", "EOI" };


int scan(Scanner &s)
{
	YYCTYPE *cursor = s.cur;

	if(cursor == s.lim)
		return EOI;
	
std:
	s.tok = cursor;


#line 51 "ctx_b.c"
{
	YYCTYPE yych;
	static const unsigned char yybm[256] = {
		  0,   0,   0,   0,   0,   0,   0,   0,
		  0,   0,   0,   0,   0,   0,   0,   0,
		  0,   0,   0,   0,   0,   0,   0,   0,
		  0,   0,   0,   0,   0,   0,   0,   0,
		  0,   0,   0,   0,   0,   0,   0,   0,
		  0,   0,   0,   0,   0,   0,   0,   0,
		128, 128, 128, 128, 128, 128, 128, 128,
		128, 128,   0,   0,   0,   0,   0,   0,
		  0,   0,   0,   0,   0,   0,   0,   0,
		  0,   0,   0,   0,   0,   0,   0,   0,
		  0,   0,   0,   0,   0,   0,   0,   0,
		  0,   0,   0,   0,   0,   0,   0,   0,
		  0,   0,   0,   0,   0,   0,   0,   0,
		  0,   0,   0,   0,   0,   0,   0,   0,
		  0,   0,   0,   0,   0,   0,   0,   0,
		  0,   0,   0,   0,   0,   0,   0,   0,
		  0,   0,   0,   0,   0,   0,   0,   0,
		  0,   0,   0,   0,   0,   0,   0,   0,
		  0,   0,   0,   0,   0,   0,   0,   0,
		  0,   0,   0,   0,   0,   0,   0,   0,
		  0,   0,   0,   0,   0,   0,   0,   0,
		  0,   0,   0,   0,   0,   0,   0,   0,
		  0,   0,   0,   0,   0,   0,   0,   0,
		  0,   0,   0,   0,   0,   0,   0,   0,
		  0,   0,   0,   0,   0,   0,   0,   0,
		  0,   0,   0,   0,   0,   0,   0,   0,
		  0,   0,   0,   0,   0,   0,   0,   0,
		  0,   0,   0,   0,   0,   0,   0,   0,
		  0,   0,   0,   0,   0,   0,   0,   0,
		  0,   0,   0,   0,   0,   0,   0,   0,
		  0,   0,   0,   0,   0,   0,   0,   0,
		  0,   0,   0,   0,   0,   0,   0,   0
	};
	if ((YYLIMIT - YYCURSOR) < 3) YYFILL(3);
	yych = *YYCURSOR;
	if (yybm[0+yych] & 128) {
		goto yy4;
	}
	if (yych <= 0x1F) {
		if (yych <= 0x08) goto yy1;
		if (yych <= '\n') goto yy3;
	} else {
		if (yych <= ' ') goto yy3;
		if (yych <= '`') goto yy1;
		if (yych <= 'b') goto yy5;
	}
yy1:
	++YYCURSOR;
yy2:
#line 61 "ctx_b.re"
	{
		return UNEXPECTED;
	}
#line 108 "ctx_b.c"
yy3:
	++YYCURSOR;
#line 54 "ctx_b.re"
	{
		if(s.cur == s.lim)
			return EOI;
		cursor = s.cur;
		goto std;
	}
#line 118 "ctx_b.c"
yy4:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	if (yybm[0+yych] & 128) {
		goto yy4;
	}
#line 51 "ctx_b.re"
	{ return NUMBER;  }
#line 128 "ctx_b.c"
yy5:
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy2;
	if (yych == '1') {
		YYCTXMARKER = YYCURSOR;
		goto yy8;
	}
	if (yych >= ':') goto yy2;
	YYCTXMARKER = YYCURSOR;
yy6:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	if (yych <= '/') goto yy7;
	if (yych <= '9') goto yy6;
yy7:
	YYCURSOR = YYCTXMARKER;
#line 50 "ctx_b.re"
	{ return KEYWORD; }
#line 148 "ctx_b.c"
yy8:
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy9;
	if (yych <= '9') goto yy6;
yy9:
	YYCURSOR -= 1;
#line 49 "ctx_b.re"
	{ return KEYWORD; }
#line 157 "ctx_b.c"
}
#line 64 "ctx_b.re"

}

#line 163 "ctx_b.c"
#define YYMAXFILL 3
#line 67 "ctx_b.re"


int main(int,char**)
{
	Scanner s("a77 a1 b8 b1");
	
	int t, n = 0;
	while ((t = scan(s)) != EOI)
	{
		std::cout << (++n) << ": " << tokens[t] << " = \""; std::cout.write(s.tok, s.cur-s.tok); std::cout << "\"" << std::endl;
	}
}
