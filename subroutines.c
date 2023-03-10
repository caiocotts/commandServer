#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <linux/limits.h>
#include <sys/stat.h>

int export_cmd(char **args) {
    putenv(args[1]);
    return 0;
}

int unset_cmd(char **args) {
    putenv(args[1]);
    return 0;
}

int chdir_cmd(char **args) {
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof cwd);
    setenv("OLDPWD", cwd, 1);
    char *dirPath = args[1];
    if (strcmp(dirPath, "-") == 0) {
        chdir(getenv("OLDPWD"));
        return 0;
    }
    chdir(dirPath);
    return 0;
}

int access_cmd() {
    puts("access is not implemented");
    return 0;
}

int chmod_cmd(char **args) {
    long permission = strtol(args[1], NULL, 8);
    chmod(args[2], permission);
    for (int i = 2; NULL != args[i]; i++) {
        int status = chmod(args[i], permission);
        if (status != 0) {
            printf("%s\n", strerror(status)); // I don't understand why use strerror on chmod
                                                          // given that it can only return 0 or -1, but here it
                                                          // is anyways I guess. The printf will always display "unknown error -1" on an error.
        }
        return status;
    }
    return 0;
}

int path_cmd() {
    puts("path is not implemented");
    return 0;
}

int touch_cmd() {
    puts("touch is not implemented");
    return 0;
}

int ln_cmd() {
    puts("ln is not implemented");
    return 0;
}
