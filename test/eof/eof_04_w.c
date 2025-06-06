/* Generated by re2c */
// re2c $INPUT -o $OUTPUT -iw
#include <stdio.h>
#include <stdint.h>
#include <string.h>

static const size_t SIZE = 4096;

struct input_t {
    uint16_t buf[SIZE + 1];
    uint16_t *lim;
    uint16_t *cur;
    uint16_t *mar;
    uint16_t *tok;
    bool eof;

    input_t()
        : buf()
        , lim(buf + SIZE)
        , cur(lim)
        , mar(lim)
        , tok(lim)
        , eof(false)
    {
        fill();
    }
    int fill()
    {
        if (eof) {
            return 1;
        }
        const size_t free = tok - buf;
        if (free < 1) {
            return 2;
        }
        memmove(buf, tok, lim - tok);
        lim -= free;
        cur -= free;
        mar -= free;
        tok -= free;
        lim += fread(lim, sizeof(uint16_t), free, stdin);
        lim[0] = 65535;
        if (lim < buf + SIZE) {
            eof = true;
        }
        return 0;
    }
};

static bool lex(input_t & in, unsigned int &count)
{
    for (count = 0;;) {
        in.tok = in.cur;
        
{
	uint16_t yych;
yyFillLabel0:
	yych = *in.cur;
	if (yych == '\n') goto yy3;
	if (yych >= 0xFFFF) {
		if (in.lim <= in.cur) {
			if (in.fill() == 0) goto yyFillLabel0;
			goto yy5;
		}
		goto yy1;
	}
yy1:
	++in.cur;
yyFillLabel1:
	yych = *in.cur;
	if (yych == '\n') goto yy2;
	if (yych <= 0xFFFE) goto yy1;
	if (in.lim <= in.cur) {
		if (in.fill() == 0) goto yyFillLabel1;
		goto yy2;
	}
	goto yy1;
yy2:
	{ ++count; continue; }
yy3:
	++in.cur;
yyFillLabel2:
	yych = *in.cur;
	if (yych == '\n') goto yy3;
	if (yych >= 0xFFFF) {
		if (in.lim <= in.cur) {
			if (in.fill() == 0) goto yyFillLabel2;
		}
		goto yy4;
	}
yy4:
	{ continue; }
yy5:
	{ return true; }
}

    }
}

int main(void)
{
    input_t in;
    unsigned int count;
    if (lex(in, count)) {
        printf("glorious %u numbers!\n", count);
    } else {
        printf("error\n");
    }

    return 0;
}
