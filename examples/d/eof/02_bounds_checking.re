// re2d $INPUT -o $OUTPUT
module main;

import core.stdc.stdlib;
import core.stdc.string;

/*!max:re2c*/

private int lex(immutable char[] s) {
    // Make a copy of the string with YYMAXFILL zeroes at the end.
    char *buf = cast(char*) malloc(s.length + YYMAXFILL);
    memcpy(buf, cast(const(void*)) s, s.length);
    memset(buf + s.length, 0, YYMAXFILL);

    const(char)* cur = buf;
    const(char)* lim = buf + s.length + YYMAXFILL;
    int count = 0;

loop:
    /*!re2c
        re2c:define:YYCTYPE    = char;
        re2c:define:YYPEEK     = '*cur';
        re2c:define:YYSKIP     = 'cur++;';
        re2c:define:YYLESSTHAN = 'lim <= cur';
        re2c:define:YYFILL     = "goto fail;";

        str = ['] ([^'\\] | [\\][^])* ['];

        [\x00] {
            // Check that it is the sentinel, not some unexpected null.
            if (cur - 1 == buf + s.length) goto exit; else goto fail;
        }
        str  { ++count; goto loop; }
        [ ]+ { goto loop; }
        *    { goto fail; }
    */
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
