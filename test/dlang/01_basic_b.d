/* Generated by re2c */
#line 1 "dlang/01_basic_b.re"
// re2d $INPUT -o $OUTPUT -b
module main;

bool lex(const char *s) {
    size_t cursor;
    
#line 10 "dlang/01_basic_b.d"
{
	char yych;
	immutable char[256] yybm = [
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
	];
	yych = s[cursor];
	if (yych <= '0') goto yy1;
	if (yych <= '9') goto yy2;
yy1:
	++cursor;
#line 14 "dlang/01_basic_b.re"
	{ return false; }
#line 54 "dlang/01_basic_b.d"
yy2:
	++cursor;
	yych = s[cursor];
	if ((yybm[0+yych] & 128) != 0) {
		goto yy2;
	}
#line 13 "dlang/01_basic_b.re"
	{ return true; }
#line 63 "dlang/01_basic_b.d"
}
#line 15 "dlang/01_basic_b.re"

}

void main() {
    assert(lex("1234"));
}
