#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static volatile sig_atomic_t got_sigint  = 0;

static void on_signal(int signum) {
    if (signum == SIGINT)  got_sigint  = 1;
}

int main(void) {
    struct sigaction sa;
    memset(&sa, 0, sizeof sa);
    sa.sa_handler = on_signal;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;  // SA_RESTARTなし → readline内read()がEINTRで戻りやすい

    if (sigaction(SIGINT,  &sa, NULL) == -1) { perror("sigaction SIGINT");  return 1; }

    // もし使えるなら、二重処理防止のためにこれを有効化するのが最も簡単
    // rl_catch_signals = 0;

    for (;;) {
        char *line = readline("> ");

        // --- SIGINT/SIGQUIT 対応 ---
        if (got_sigint) {
            // Readlineがすでに改行・再描画して戻る（line == NULL で復帰）ことがある。
            // その場合は自分では改行/再描画を重ねない。
            if (line) {
                // 自前で整える（bash風に ^C/^\\ は出さず改行だけ）
                write(STDOUT_FILENO, "\n", 1);
                rl_replace_line("", 0);
                rl_on_new_line();
                rl_redisplay();
                free(line);
            }
            // line == NULL のケースは Readline 側が整えてくれている想定
            continue;
        }

        // --- EOF (Ctrl-D) ---
        if (line == NULL) {
            // ここに来るのは主に Ctrl-D（※SIGINT後に来ることもあるが上で continue 済み）
            puts("exit");
            break;
        }

        // 空行（Enterだけ）
        if (*line == '\0') { free(line); continue; }

        // 終了コマンド
        if (strcmp(line, "exit") == 0) {
            free(line);
            puts("exit");
            break;
        }

        printf("line is %s\n", line);
        add_history(line);
        free(line);
    }
    return 0;
}
