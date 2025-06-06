/* Generated by re2c */
#line 1 "d/eof/02_bounds_checking.re"
// re2d $INPUT -o $OUTPUT
module main;

import core.stdc.stdlib;
import core.stdc.string;

#line 10 "d/eof/02_bounds_checking.d"
enum YYMAXFILL = 1;
#line 7 "d/eof/02_bounds_checking.re"


private int lex(immutable char[] s) {
    // Make a copy of the string with YYMAXFILL zeroes at the end.
    char *buf = cast(char*) malloc(s.length + YYMAXFILL);
    memcpy(buf, cast(const(void*)) s, s.length);
    memset(buf + s.length, 0, YYMAXFILL);

    const(char)* cur = buf;
    const(char)* lim = buf + s.length + YYMAXFILL;
    int count = 0;

loop:
    
#line 27 "d/eof/02_bounds_checking.d"
{
	char yych;
	if (lim <= cur) goto fail;
	yych = *cur;
	switch (yych) {
		case 0x00: goto yy1;
		case ' ': goto yy3;
		case '\'': goto yy5;
		default: goto yy2;
	}
yy1:
	cur++;
#line 29 "d/eof/02_bounds_checking.re"
	{
            // Check that it is the sentinel, not some unexpected null.
            if (cur - 1 == buf + s.length) goto exit; else goto fail;
        }
#line 45 "d/eof/02_bounds_checking.d"
yy2:
	cur++;
#line 35 "d/eof/02_bounds_checking.re"
	{ goto fail; }
#line 50 "d/eof/02_bounds_checking.d"
yy3:
	cur++;
	if (lim <= cur) goto fail;
	yych = *cur;
	switch (yych) {
		case ' ': goto yy3;
		default: goto yy4;
	}
yy4:
#line 34 "d/eof/02_bounds_checking.re"
	{ goto loop; }
#line 62 "d/eof/02_bounds_checking.d"
yy5:
	cur++;
	if (lim <= cur) goto fail;
	yych = *cur;
	switch (yych) {
		case '\'': goto yy6;
		case '\\': goto yy7;
		default: goto yy5;
	}
yy6:
	cur++;
#line 33 "d/eof/02_bounds_checking.re"
	{ ++count; goto loop; }
#line 76 "d/eof/02_bounds_checking.d"
yy7:
	cur++;
	if (lim <= cur) goto fail;
	goto yy5;
}
#line 36 "d/eof/02_bounds_checking.re"

fail:
    count = -1;
exit:
    free(buf);
    return count;
}

void main() {
    assert(lex("") == 0);
    assert(lex("'qu\0tes' 'are' 'fine: \\'' ") == 3);
    assert(lex("'unterminated\\'") == -1);
    assert(lex("'unexpected \0 null\\'") == -1);
}
