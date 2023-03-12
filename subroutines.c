#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <linux/limits.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>
#include <errno.h>

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
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("getcwd");
        return errno;
    }

    if (setenv("OLDPWD", cwd, 1) != 0) {
        perror("setenv");
        return errno;
    }

    char *dirPath = args[1];
    if (strcmp(dirPath, "-") == 0) {
        if (chdir(getenv("OLDPWD")) != 0) {
            perror("chdir");
            return errno;
        }
    } else {
        if (chdir(dirPath) != 0) {
            perror("chdir");
            return errno;
        }
    }
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
            // perror makes more sense in this context.
        }
        return status;
    }
    return 0;
}

int path_cmd() {
    puts("path is not implemented");
    return 0;
}

int touch_cmd(char **args) {
    struct flags {
        long int modify;
        long int access;
    } flags = {0, 0};

    int argc = 0;
    for (int i = 0; args[i] != NULL; i++) {
        argc++;
    }


    int flag;
    int count = 1;
    while ((flag = getopt(argc, args, ":m:a:")) != -1) {
        switch (flag) {
            case 'm':
                flags.modify = atoi(optarg);
                break;
            case 'a':
                flags.access = atoi(optarg);
                break;
            case ':':
                return 1;
            case '?':
                return 1;

        }
        count++;
    }

    /*
     * I'm not really sure what to do with these arguments.
     * The instructions are incomplete.
     * "Use the getopt loop to capture -m t1 and -a t2, if they are present where t1 and t2 are large integers representing  ... "
     *                                                                     ^                                               ^
     *                                                           If they are present, what do I do?                       This is also cut off, but I'm assuming it was supposed to say "time" or something.
     * Also, the real touch command does not take arguments for the 'a' and 'm' flags. I'm just going to do what I think is right and follow the specifications for part ii.
     */

    for (int i = count; i <= sizeof args[i]; i++) {
        int exists = stat("", (struct stat *) stat);
        if (exists != 0) {
            int success = creat(args[i], 0644);
            if (success == -1) {
                perror("touch");
                return 1;
            }
            struct timeval now;
            gettimeofday(&now, NULL);
            struct timeval time[2];
            time[0] = now;
            time[1] = now;
            gettimeofday((struct timeval *) &time, NULL);

            int fd = open(args[i], O_RDONLY);
            futimes(fd, time);
            close(fd);
            return 0;
        }
        utimes(args[i], NULL);
    }
    return 0;
}

int ln_cmd() {
    puts("ln is not implemented");
    return 0;
}
