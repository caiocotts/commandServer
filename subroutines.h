#include <stddef.h>

int export_cmd();

int unset_cmd();

int chdir_cmd(char **args);

int access_cmd();

int chmod_cmd();

int path_cmd();

int touch_cmd();

int ln_cmd();

struct SUBROUTINES {
    char *name;

    int (*func)();
} subroutines[] = {
        {"export", export_cmd},
        {"unset",  unset_cmd}, 
        {"chdir",  chdir_cmd},
        {"access", access_cmd},
        {"chmod",  chmod_cmd}, 
        {"path",   path_cmd},
        {"touch",  touch_cmd},
        {"ln",     ln_cmd},
        {NULL, NULL}};   