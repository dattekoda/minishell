wildcard の実装

1. "."を明示的にしないと隠しファイルはスコープされない。
```	$ ls *	```
```	$ ls .*	```
ファイル名チェックの際、先頭が'.'かを判定、パターン側も'.'で始まっていない限りは除外する必要あり

2. パターンに該当するファイルが一つもなければ展開されずに、パターン文字列が引数となる。
```	cmd: cannot access 'パターン文字列': No such file or directory```

3. シングルクウォート(')やダブルクウォート(")で囲まれているwildcardは展開されない。
```	$ echo *	``` -> 展開される
```	$ echo "*"	``` -> パターン文字列とする
```	$ echo '*'	``` -> パターン文字列とする

4. 環境変数にexportされたwildcardは展開する必要あり。
```export PATH="*.txt"```
- ``` $ echo $PATH		```	-> 展開される
- ``` $ echo "$PATH"	```	-> パターン文字列とする

5. wildcardのスコープ対象にスラッシュ(/)が見つけた瞬間 -> exit()

//! パース段階でwildcardを展開するか決める為にフラグ管理の必要あり。
//- 区切り文字でしっかり区切られていない場合は構文エラー処理(syntax err)

※ bashのオプション
- ```shopt -s nullglob```
- ``` globstar ```

opendir() Err handle

1. dirのパーミッションが無い場合 (DIR : EACCES)
	```cmd: cannot open directoty 'dir name': Permission denied	```
2. 指定パターンに該当するファイルが一つもない (DIR : ENOTDIR)
	```	cmd: cannot access 'パターン文字列': No such file or directory```
? これはexec()の仕事かな?
(例)
	bash ls
	a.out  gohanohayo  main.c  test_dir
	bash ls *.out
	a.out
	bash cd *.out
	bash: cd: a.out: Not a directory```

3.
## 10/14
