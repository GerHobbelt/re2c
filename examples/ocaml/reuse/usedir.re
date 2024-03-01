(* re2ocaml $INPUT -o $OUTPUT *)

(* This example shows how to combine reusable re2c blocks: two blocks
   ('colors' and 'fish') are merged into one. The 'salmon' rule occurs
   in both blocks; the 'fish' block takes priority because it is used
   earlier. Default rule * occurs in all three blocks; the local (not
   inherited) definition takes priority. *)

type answer = Color | Fish | Dunno

type state = {
    str: string;
    mutable cur: int;
    mutable mar: int;
}

/*!rules:re2c:colors
    *                            { raise (Failure "ah"); }
    "red" | "salmon" | "magenta" { Color }
*/

/*!rules:re2c:fish
    *                            { raise (Failure "oh"); }
    "haddock" | "salmon" | "eel" { Fish }
*/

/*!re2c
    re2c:define:YYFN       = ["lex;answer", "st;state"];
    re2c:define:YYCTYPE    = int;
    re2c:define:YYPEEK     = "Char.code st.str.[st.cur]";
    re2c:define:YYSKIP     = "st.cur <- st.cur + 1;";
    re2c:define:YYBACKUP   = "st.mar <- st.cur;";
    re2c:define:YYRESTORE  = "st.cur <- st.mar;";
    re2c:yyfill:enable     = 0;

    !use:fish;
    !use:colors;
    * { Dunno } // overrides inherited '*' rules
*/

let test(str, ans) =
    let st = {str = str; cur = 0; mar = 0}
    in if not (lex st = ans) then raise (Failure "error")

let main () =
    test("salmon", Fish);
    test("what?", Dunno)

let _ = main ()
