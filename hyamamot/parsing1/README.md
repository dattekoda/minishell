字句解析
-> 構文解析
-> 評価
の流れを学んだので、四則演算で練習する。

コメント以外のnorminetteを通しておく。一応。

四則演算の文法
```bash
Expression  = Term { ("+" | "-") Term } ;
Term        = Factor { ("*" | "/") Factor } ;
Factor      = Number | "(" Expression ")" ;
Number      = Digit { Digit } ;
Digit       = "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9" ;
```

[memo]

- 語彙素はlexemeという
- 字句解析はlexical analysisという
- 先読みキャッシュの命名peekは覗き見という意味
- なぜ先読みが必要なのか？
	EBNFで<Number> | "(" <Expr> ")"みたいな処理があるとした時に、どちらを選択すれば良いのか先読みする必要がある。    
	また、<Expr> ::== <Term> { ("+" | "-") <Term>}の時もTermを読んだ後にループを続けるかどうか、+/-を見て判断したい。   
	単項-3なのか二項なのか1-3を判断
	この様なものをLL(1)と言ったりする。   
	L:入力をLeft-to-right,    
	L:Leftmost derivation(最も左の非終端から展開)で解析    
	(1)先読み１トークンだけ見れば、どの生成規則をつかうか一意に決められる。   
 
