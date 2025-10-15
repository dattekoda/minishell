## 使い方
`khanadat_proto/prompt`ディレクトリ内で`make`でコンパイル
作成された実行ファイル、`minishell`を`./minishell`で実行できます。

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
norminette修正: exec.c   
fix: segmentation fault: コマンドを指定せずに、`> file`のようにリダイレクトだけ指定したときにセグフォを起こすバグを修正。   
norminette fix: すべてのnorminette errorの修正。   
Makefileの追加。   

## 10/9
heredocの子プロセス上で他のheredocファイルを削除しないように変更。   
main.cファイルの分離でファイルの整理。   
Linux環境でコンパイルできるように諸々調整。   
`echo a "" a`に対応。   

## 10/10
構造体`t_mini`から`mini_pwd`を削除。   
ビルトインコマンド`cd`で親ディレクトリに移動するときの挙動を調整。   
`$OLDPWD`が`getcwd()`で得た情報をもとに更新するように変更。   
`getcwd()`エラーが発生した時、`pwd`コマンドで環境変数から出力するように変更。   
scan-build fix: `scan-build: No bugs found.`   
`tokenizer_validate.c`: ()のvalidate_parenthesisの追加。   

## 10/11
astディレクトリでのisシリーズを追加。   
プロンプトにis_spaceだけ入力されたときに$?=2となるバグを修正。   
tokenizerのvalidateで()が正しく閉じていないと`syntax error`となる`validate_parenthesis()`を追加。   
astに`()`のvalidateを追加。それに伴い`ast_utils_validate.c`ファイルを追加。   
構造体`t_word, t_red`内stringsの領域を動的確保せずに、mini->lineのポインタを持つように変更。   
それぞれのstrings終わりのlineへ`\0`を挿入。   
priorityを調節できる`()`を追加。   
`()`内で実行されたコマンドは親プロセスに影響を及ぼすことがない。   
exitで最後のコマンドの終了ステータスで終了するように修正。   
exit: refactoring   
()内で行われるexitの際にexitと標準エラー出力されないように修正。   

## 10/13
`expand_utils_add.c`内の`add_new_red()`関数内で`ft_calloc()`する際のsizeofを`t_word`から`t_red`に修正。   
libraryをutilsにリネーム。   
使われていないファイルを削除。   
バグ発見:ダブルクオーテーション連続で出現したときセグフォ。   
```
$ echo "this""is"
Segmentation fault         (core dumped) ./minishell
```
→修正済み。   
原因は、`validate_b4_tokenize()`の`validate_and()`関数の結果に直接`+1`していたこと。   

## 10/14
`pipe|`を挟んで()を受け入れないように方針固め。   

## 10/15
`pipe`をwhileループで実行するように修正。   
```
sleep 10 | echo hello
```
等のコマンドに対応。   
シグナルハンドリングの調整。   
```
sleep 10 | sleep 1
```
上記のコマンドで1秒待ったあとにCtrl+cすると$?=0となるが、   
```
sleep 10 | sleep 1 && echo hello
```
このコマンドで1秒待ったとにCtrl+cすると$?=130となるように調整。   
Ctrl+cすると新しいプロンプトが改行後に正しく表示されるように修正。   