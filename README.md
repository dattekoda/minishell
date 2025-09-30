## 使い方
```
~/cursus/3/minishell/dattekoda
```
というパスにgit cloneすれば以下の*mac用*.zshrcを使えば簡単にコンパイルできる。   
```
alias ccw='cc -Wall -Wextra -Werror'
alias ccft='ccw -I libftのヘッダーディレクトリへのパス libft.aへのパス'
alias ccr='ccft -lreadline -I /opt/homebrew/opt/readline/include -L /opt/homebrew/opt/readline/lib'
alias ccm='ccr -I ~/cursus/3/minishell/dattekoda/khanadat_proto/ ~/cursus/3/minishell/dattekoda/khanadat_proto/minishell_*.c'
alias ccast='ccm -I ~/cursus/3/minishell/dattekoda/khanadat_proto/ast -I ~/cursus/3/minishell/dattekoda/khanadat_proto/ast/tokenizer ~/cursus/3/minishell/dattekoda/khanadat_proto/ast/*.c ~/cursus/3/minishell/dattekoda/khanadat_proto/ast/tokenizer/*.c'
```
`khanadat_proto/prompt`ディレクトリ内で`ccast *.c`でコンパイルできるはず。

## 9/8
hyamamot/input.cのレビュー   
khanadat_protoの追加。   
このディレクトリでプロトタイプの作成を試みる。   

## 9/8
funcディレクトリで使えるコマンドの整理する。   

## 9/10
khanadat_proto/srcsでcd, pwd, echoを再現した簡易的なshellを実装。   
srcsディレクトリで   
```
make -C ../libft && cc *.c */*.c ../libft/libft.a \
-I ../incs -I../libft/includes \
-I/opt/homebrew/opt/readline/include \
-L/opt/homebrew/opt/readline/lib \
-lreadline -lncurses -o minishell
```
でコンパイルできる。

矢印キーで、以前入力したコマンドが自由に使えるように変更

## 9/12
expand_param.cを追加。    
標準入力を開いて、受け取った文字列から$マークに続く環境変数を展開したあとに、   
それを動的に確保された領域に保存して標準出力に出力する。   
動作例
```
$ this is test
this is test
$ $HOME
/Users/khanadat
$ inside '$HOME'
inside '$HOME'
$ \$HOME
\$HOME
$ $HOME $PWD $SHELL
/Users/khanadat /Users/khanadat/cursus/3/minishell/dattekoda/khanadat_proto /bin/zsh
```

bashのmanを読むと、変数展開が一番最初に行われると知り、ここまでやってきたminishellを一旦trash dirに削除。   

## 2025/9/30
シングルクォーテーション、ダブルクオーテーション、変数展開を行ったあとに一つだけビルトインコマンド以外のコマンドを実行できるように実装。   
