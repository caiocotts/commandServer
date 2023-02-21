
int export_cmd() {
    puts("export is not implemented");
    return 0;
}

int unset_cmd() {
    puts("unset is not implemented");
    return 0;
}

int chdir_cmd() {
    puts("chdir is not implemented");
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