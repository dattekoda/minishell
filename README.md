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

## 9/30
シングルクォーテーション、ダブルクオーテーション、変数展開を行ったあとに一つだけビルトインコマンド以外のコマンドを実行できるように実装。   
リダイレクトができるように変更
シグナルを受け取ったときの$?のバグ修正

## 10/1
環境変数に入ってくるスペースに対応できないバグを修正   
```
% export SPACE="     "
a.out$ echo $SPACE'a'
a
a.out$ echo "$SPACE"a
     a
```

## 10/3
ファイルディスクリプタの変更と変数展開を親プロセス内で更新するように変更。   
ビルトインコマンドであるpwdとcdコマンドの追加。    
set_redirect.h, set_redirect.cの追加。   
heredocを子プロセスで行うよう修正。   
heredocで変数展開が行う機能の追加。   

## 10/4
cdで絶対パスに移動できるように修正。   
ambigous redirectでmallocエラーとして処理されるバグを修正。  
未設定の環境変数をリダイレクト入力としてセットしたときにambigous redirectとエラーメッセージが表示されるよう修正。   
次にやるタスクはexec.cファイルの整理。   

exportの追加   
echoの追加   
envの追加   

## 10/5
引数がないときのechoでセグフォするバグを修正。   
exitの追加。   
unsetの追加。   
export var+=valueへ対応する機能の追加。   
cdで$PWDを更新するときの挙動を調整。   
buitinディレクトリの作成。   
exec.cファイルの整理。   
tokenizer, astの段階で出るsyntax errorがエラーステータス$?を取得できていないバグを修正。   

## 10/7
パイプ、アンド、オアの機能を実装。   
細かなバグの修正。   
次やることは、norminetteに準拠するようにファイルの整理。   
それと、メモリリークの修正。   
子プロセスをkillするように修正。   

パイプでheredocしたときの挙動を修正。   
```
bash$ cat << abc | cat << this
> ohayo
> gohan
> abc
> 123
> 456
> this
123
456
```
環境変数の更新をPWDやSHLVLが行うよう変更。   
heredocを複数回行っているときシグナルが飛んできたとき正しくすべて終了するよう修正。   
プログラム名をグローバル変数もどきの関数で取得しないように修正。   

## 10/8
カレントディレクトリのパーミッションをなくしたときでも`cd ..`で親ディレクトリに移動できるように修正。   
