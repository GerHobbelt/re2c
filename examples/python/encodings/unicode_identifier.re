# re2py $INPUT -o $OUTPUT --utf8

/*!include:re2c "unicode_categories.re" */

def lex(str):
    cur = 0
    /*!re2c
        re2c:define:YYPEEK    = "str[cur]";
        re2c:define:YYSKIP    = "cur += 1";
        re2c:define:YYBACKUP  = "mar = cur";
        re2c:define:YYRESTORE = "cur = mar";
        re2c:yyfill:enable = 0;
        re2c:indent:top = 1;

        // Simplified "Unicode Identifier and Pattern Syntax"
        // (see https://unicode.org/reports/tr31)
        id_start    = L | Nl | [$_];
        id_continue = id_start | Mn | Mc | Nd | Pc | [\u200D\u05F3];
        identifier  = id_start id_continue*;

        identifier { return True }
        *          { return False }
    */

assert lex(bytes("_Ыдентификатор\0", "utf-8"))
