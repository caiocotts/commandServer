/*
   File: commandServer2.c
   Course: CENG320
   Author: Leon King
   Date: Monday Aug 31, 2020   2:40 PM

*/

#include <fcntl.h>
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

void ctrlCHandler(int signum) {
  fprintf(stderr, "Command server terminated using <ctrl>C\n");
  exit(1);
}

// Examples of stub routines - the purpose here is to test commmand and control
char *f1() { return "Command 'one' was received"; }

char *f2(char *cmd) { return "Command 'two' was received"; }

char *f3() { return "Command 'three' was received"; }

char *f4() { return "Command four  was received"; }

// 2 parallel arrays.  commands is a list of commands to recognize
//                    methods is an array of function pointers to call.
char *commands[10] = {"one", "two", "three", "four", "alias"};
char *(*methods[10])() = {f1, f2, f3, f4, f2};

// Alternate declaration
struct CMDSTRUCT {
  char *cmd;
  char *(*method)();
} cmdStruct[] = {
    {"fred", f1}, {"mary", f2}, {"clark", f3}, {"sonia", f4}, {NULL, NULL}};

char *interpret(char *cmdline) {
  char **tokens;
  char *cmd;
  int i;
  char *result;

  tokens = history_tokenize(cmdline); // Split cmdline into individual words.
  if (!tokens)
    return "no response needed";
  cmd = tokens[0];

  // Detecting commands: table lookup:  2 techniques
  // Using the  parallel arrays to look up function calls
  for (i = 0; commands[i]; i++) {
    if (strcasecmp(cmd, commands[i]) == 0)
      return (methods[i])(cmd, &tokens[1]);
  }

  // Using struct CMDSTRUCT as an alternative lookup method. Pick either
  // technique, not both Note that its possible to create multiple aliases for
  // the same command using either method.
  for (i = 0; cmdStruct[i].cmd; i++)
    if (strcasecmp(cmd, cmdStruct[i].cmd) == 0)
      return (cmdStruct[i].method)(cmd, &tokens[1]);

  return "command not found";
}

int main(int argc, char *argv[], char *envp[]) {
  char cmd[100];
  char *cmdLine;
  char *expansion;
  time_t now = time(NULL);
  int nBytes; // size of msg rec'd

  signal(SIGINT, ctrlCHandler);

  read_history("shell.log");
  add_history(ctime(&now));
  fprintf(stdout, "Starting the shell at: %s\n", ctime(&now));
  while (true) {

    cmdLine = readline("Enter a command: ");
    if (!cmdLine)
      break;
    history_expand(cmdLine, &expansion);
    add_history(expansion);
    if (strcasecmp(cmdLine, "bye") == 0)
      break;
    char *response = interpret(cmdLine);
    fprintf(stdout, "%s\n", response);
  }
  write_history("shell.log");
  system("echo Your session history is; cat -n shell.log");
  fprintf(stdout, "Server is now terminated \n");
  return 0;
}
