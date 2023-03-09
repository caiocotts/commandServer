#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <linux/limits.h>

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

int chmod_cmd() {
    puts("chmod is not implemented");
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
