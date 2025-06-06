/* Generated by re2c */
#line 1 "d/eof/03_eof_rule.re"
// re2d $INPUT -o $OUTPUT
module main;

// Expect a null-terminated string.
private int lex(immutable char[] s) {
    const(char)* cur = s.ptr, lim = s.ptr + s.length, mar;
    int count = 0;

    for (;;) {
    
#line 14 "d/eof/03_eof_rule.d"
{
	char yych;
	yych = *cur;
	switch (yych) {
		case ' ': goto yy3;
		case '\'': goto yy5;
		default:
			if (lim <= cur) goto yy10;
			goto yy1;
	}
yy1:
	++cur;
yy2:
#line 22 "d/eof/03_eof_rule.re"
	{ return -1; }
#line 30 "d/eof/03_eof_rule.d"
yy3:
	++cur;
	yych = *cur;
	switch (yych) {
		case ' ': goto yy3;
		default: goto yy4;
	}
yy4:
#line 25 "d/eof/03_eof_rule.re"
	{ continue; }
#line 41 "d/eof/03_eof_rule.d"
yy5:
	++cur;
	mar = cur;
	yych = *cur;
	if (yych >= 0x01) goto yy7;
	if (lim <= cur) goto yy2;
yy6:
	++cur;
	yych = *cur;
yy7:
	switch (yych) {
		case '\'': goto yy8;
		case '\\': goto yy9;
		default:
			if (lim <= cur) goto yy11;
			goto yy6;
	}
yy8:
	++cur;
#line 24 "d/eof/03_eof_rule.re"
	{ ++count; continue; }
#line 63 "d/eof/03_eof_rule.d"
yy9:
	++cur;
	yych = *cur;
	if (yych <= 0x00) {
		if (lim <= cur) goto yy11;
		goto yy6;
	}
	goto yy6;
yy10:
#line 23 "d/eof/03_eof_rule.re"
	{ return count; }
#line 75 "d/eof/03_eof_rule.d"
yy11:
	cur = mar;
	goto yy2;
}
#line 26 "d/eof/03_eof_rule.re"

    }
    assert(0); // unreachable
}

void main() {
    assert(lex("") == 0);
    assert(lex("'qu\0tes' 'are' 'fine: \\'' ") == 3);
    assert(lex("'unterminated\\'") == -1);
}
