#define BUFSIZE 64
#define DELIMITER " \t\r\n\a"

char *read_line();

char **parse(char *line);

int exec(char **args);

void sig_interrupt_handler();

_Noreturn void shell_loop();