(* re2ocaml $INPUT -o $OUTPUT -i *)

open Int64
open Option

type state = {
    str: string;
    mutable cur: int;
    mutable mar: int;
} 

let add (num: int option) (dgt: int) (base: int) : int option =
    match num with
        | None -> None
        | Some n ->
            let n' = add (mul (of_int n) (of_int base)) (of_int dgt)
            in if n' > (of_int32 Int32.max_int) then None else Some (to_int n')

/*!re2c
    re2c:define:YYCTYPE   = char;
    re2c:define:YYPEEK    = "st.str.[st.cur]";
    re2c:define:YYSKIP    = "st.cur <- st.cur + 1;";
    re2c:define:YYBACKUP  = "st.mar <- st.cur;";
    re2c:define:YYRESTORE = "st.cur <- st.mar;";
    re2c:define:YYSHIFT   = "st.cur <- st.cur + @@;";
    re2c:yyfill:enable    = 0;
*/

/*!local:re2c
    re2c:define:YYFN = ["parse_bin;int option", "st;state", "num;int option"];
    [01] { parse_bin st (add num (Char.code st.str.[st.cur - 1] - 48) 2) }
    *    { num }
*/

/*!local:re2c
    re2c:define:YYFN = ["parse_oct;int option", "st;state", "num;int option"];
    [0-7] { parse_oct st (add num (Char.code st.str.[st.cur - 1] - 48) 8) }
    *     { num }
*/

/*!local:re2c
    re2c:define:YYFN = ["parse_dec;int option", "st;state", "num;int option"];
    [0-9] { parse_dec st (add num (Char.code st.str.[st.cur - 1] - 48) 10) }
    *     { num }
*/

/*!local:re2c
    re2c:define:YYFN = ["parse_hex;int option", "st;state", "num;int option"];
    [0-9] { parse_hex st (add num (Char.code st.str.[st.cur - 1] - 48) 16) }
    [a-f] { parse_hex st (add num (Char.code st.str.[st.cur - 1] - 87) 16) }
    [A-F] { parse_hex st (add num (Char.code st.str.[st.cur - 1] - 55) 16) }
    *     { num }
*/

/*!local:re2c
    re2c:define:YYFN = ["parse;int option", "st;state"];
    '0b' / [01]        { parse_bin st (Some 0) }
    "0"                { parse_oct st (Some 0) }
    "" / [1-9]         { parse_dec st (Some 0) }
    '0x' / [0-9a-fA-F] { parse_hex st (Some 0) }
    *                  { None }
*/

let test (str: string) (result: int option) =
    let st = {str = str; cur = 0; mar = 0} in
    if not (parse st = result) then raise (Failure "error")

let main () =
    test "\x00" None;
    test "1234567890\x00" (Some 1234567890);
    test "0b1101\x00" (Some 13);
    test "0x7Fe\x00" (Some 2046);
    test "0644\x00" (Some 420);
    test "9999999999\x00" None

let _ = main ()
