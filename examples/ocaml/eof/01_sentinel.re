(* re2ocaml $INPUT -o $OUTPUT *)

type state = {
    str: string;
    mutable cur: int;
}

(* expect a null-terminated string *)
/*!re2c
    re2c:define:YYFN    = ["lex;int", "st;state", "count;int"];
    re2c:define:YYCTYPE = int;
    re2c:define:YYPEEK  = "Char.code st.str.[st.cur]";
    re2c:define:YYSKIP  = "st.cur <- st.cur + 1;";
    re2c:yyfill:enable  = 0;

    *      { -1 }
    [\x00] { count }
    [a-z]+ { lex st (count + 1) }
    [ ]+   { lex st count }
*/

let test(str, count) =
    let st = {str = str; cur = 0}
    in if not (lex st 0 = count) then raise (Failure "error")

let main () =
    test("\x00", 0);
    test("one two three\x00", 3);
    test("f0ur\x00", -1)

let _ = main ()
