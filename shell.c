#include "shell.h"
#include "subroutines.h"
#include <limits.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *read_line() {
    char *line = NULL;
    size_t bufsize = 0;
    if (getline(&line, &bufsize, stdin) == -1) {
        if (feof(stdin)) {
            exit(EXIT_SUCCESS);
        } else {
            exit(EXIT_FAILURE);
        }
    }
    return line;
}

char **parse(char *line) {
    int bufsize = BUFSIZE, pos = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token, **tokens_backup;

    if (!tokens) {
        exit(EXIT_FAILURE);
    }

    token = strtok(line, DELIMITER);
    while (token != NULL) {
        tokens[pos] = strdup(token);
        pos++;
        if (pos >= bufsize) {
            bufsize += BUFSIZE;
            tokens_backup = tokens;
            tokens = reallocarray(tokens, bufsize, sizeof(char *));
            if (!tokens) {
                free(tokens_backup);
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, DELIMITER);
    }
    tokens[pos] = NULL;
    return tokens;
}

int exec(char **args) {
    if (args[0] == NULL) {
        return EXIT_SUCCESS;
    }

    for (int i = 0; subroutines[i].name; i++) {
        if (strcasecmp(args[0], subroutines[i].name) == 0) {
            return (subroutines[i].func)(args);
        }
    }

    char *cmd = malloc(strlen(args[0]) + 1);
    strcpy(cmd, args[0]);
    for (int i = 1; args[i]; ++i) {
        cmd = realloc(cmd, strlen(cmd) + strlen(args[i]) + 2);
        strcat(cmd, " ");
        strcat(cmd, args[i]);
    }

    int result = system(cmd);
    free(cmd);

    return result;
}

void sig_interrupt_handler() {
    puts("\nexit");
    exit(EXIT_SUCCESS);
}

_Noreturn void shell_loop() {
    char *line;
    char **args;
    int status;
    signal(SIGINT, sig_interrupt_handler);

    do {
        char cwd[PATH_MAX];
        printf("%s> ", getcwd(cwd, sizeof cwd));
        line = read_line();
        args = parse(line);
        status = exec(args);
        printf("exit status: %d - %s\n", WEXITSTATUS(status),
               strerror(WEXITSTATUS(status)));

    } while (true);
}