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


## 2025/9/30
シングルクォーテーション、ダブルクオーテーション、変数展開を行ったあとに一つだけビルトインコマンド以外のコマンドを実行できるように実装。   
