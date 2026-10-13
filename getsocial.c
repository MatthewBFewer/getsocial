#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "getsocial.h"

static int copy_to_clipboard(const char *text)
{
    int pipefd[2];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    const char *program;
    char *args[4];

    if (getenv("WAYLAND_DISPLAY") != NULL) {
        program = "wl-copy";
        args[0] = "wl-copy";
        args[1] = NULL;
    } else {
        program = "xclip";
        args[0] = "xclip";
        args[1] = "-selection";
        args[2] = "clipboard";
        args[3] = NULL;
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        close(pipefd[0]);
        close(pipefd[1]);
        return 1;
    }

    if (pid == 0) {
        close(pipefd[1]);

        if (dup2(pipefd[0], STDIN_FILENO) == -1) {
            perror("dup2");
            _exit(1);
        }

        close(pipefd[0]);
        execvp(program, args);
        perror(program);
        _exit(127);
    }

    close(pipefd[0]);

    size_t len = strlen(text);
    size_t written = 0;

    while (written < len) {
        ssize_t n = write(
            pipefd[1],
            text + written,
            len - written
        );

        if (n <= 0) {
            perror("write");
            close(pipefd[1]);
            waitpid(pid, NULL, 0);
            return 1;
        }

        written += (size_t)n;
    }

    close(pipefd[1]);

    int status;

    if (waitpid(pid, &status, 0) == -1) {
        perror("waitpid");
        return 1;
    }

    if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
        fprintf(stderr, "Failed to copy to clipboard.\n");
        return 1;
    }

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(
            stderr,
            INSTRUCTIONS
        );
        return 1;
    }

    for (size_t i = 0; i < PROFILE_COUNT; i++) {
        if (strcmp(argv[1], profiles[i].option) == 0) {
            if (copy_to_clipboard(profiles[i].url) != 0) {
                return 1;
            }

            printf("%s link copied to clipboard!\n",
                   profiles[i].name);
            return 0;
        }
    }

    fprintf(stderr, "Undefined option: %s\n", argv[1]);
    return 1;
}
