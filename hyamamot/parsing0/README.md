四則演算を再帰降下構文解析で実装してみようとしたが、難しかったので別の例で練習

実装する文法
<Pairs> ::= <Pair> { ";" <Pair> } [ ";" ]
<Pair>  ::= <Ident> "=" <Ident>
<Ident> ::= <Letter> { <Letter> | <Digit> | "_" }
<Letter>::= "A" | ... | "Z" | "a" | ... | "z" | "_"
<Digit> ::= "0" | ... | "9"

e.g.)
foo=bar; x1=y2; lang=_C
