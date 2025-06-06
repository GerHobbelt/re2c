// re2d $INPUT -o $OUTPUT
module main;

enum MTAG_ROOT = -1;

// An m-tag tree is a way to store histories with an O(1) copy operation.
// Histories naturally form a tree, as they have common start and fork at some
// point. The tree is stored as an array of pairs (tag value, link to parent).
// An m-tag is represented with a single link in the tree (array index).
struct Mtag {
    const(char)* elem; // tag value
    int pred; // index of the predecessor node or root
};

alias MtagTrie = Mtag[];
alias Ver = int[];

private int s2n(const(char)* s, const(char)* e) { // pre-parsed string to number
    int n = 0;
    for (; s < e; ++s) n = n * 10 + (*s - '0');
    return n;
}

// Append a single value to an m-tag history.
private void add_mtag(ref MtagTrie trie, ref int mtag, const(char)* value) {
    Mtag m = {value, mtag};
    mtag = cast(int)trie.length;
    trie ~= [m];
}

// Recursively unwind tag histories and collect version components.
private void unfold(const ref MtagTrie trie, int x, int y, ref Ver ver) {
    // Reached the root of the m-tag tree, stop recursion.
    if (x == MTAG_ROOT && y == MTAG_ROOT) return;

    // Unwind history further.
    unfold(trie, trie[x].pred, trie[y].pred, ver);

    // Get tag values. Tag histories must have equal length.
    assert(x != MTAG_ROOT && y != MTAG_ROOT);
    const(char)* ex = trie[x].elem, ey = trie[y].elem;

    if (ex != null && ey != null) {
        // Both tags are valid pointers, extract component.
        ver ~= [s2n(ex, ey)];
    } else {
        // Both tags are null (this corresponds to zero repetitions).
        assert(ex == null && ey == null);
    }
}

private bool parse(const(char)* str, ref Ver ver) {
    const(char)* cur = str, mar;
    MtagTrie mt;

    // User-defined tag variables that are available in semantic action.
    const(char)* t1, t2;
    int t3, t4;

    // Autogenerated tag variables used by the lexer to track tag values.
    /*!stags:re2c format = "const(char)* @@ = null;"; */
    /*!mtags:re2c format = "int @@ = MTAG_ROOT;"; */

    /*!re2c
        re2c:yyfill:enable = 0;
        re2c:tags = 1;
        re2c:define:YYCTYPE     = "char";
        re2c:define:YYPEEK      = "*cur";
        re2c:define:YYSKIP      = "++cur;";
        re2c:define:YYBACKUP    = "mar = cur;";
        re2c:define:YYRESTORE   = "cur = mar;";
        re2c:define:YYSTAGP     = "@@{tag} = cur;";
        re2c:define:YYSTAGN     = "@@{tag} = null;";
        re2c:define:YYSHIFTSTAG = "@@{tag} += @@{shift};";
        re2c:define:YYMTAGP     = "add_mtag(mt, @@, cur);";
        re2c:define:YYMTAGN     = "add_mtag(mt, @@, null);";

        num = [0-9]+;
        @t1 num @t2 ("." #t3 num #t4)* [\x00] {
            ver = [];
            ver ~= [s2n(t1, t2)];
            unfold(mt, t3, t4, ver);
            return true;
        }
        * { return false; }
    */
}

void main() {
    Ver v;
    assert(parse("1", v) && v == [1]);
    assert(parse("1.2.3.4.5.6.7", v) && v == [1, 2, 3, 4, 5, 6, 7]);
    assert(!parse("1.2.", v));
}
