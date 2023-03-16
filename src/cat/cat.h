#ifndef CAT_C
#define CAT_C

#include <errno.h>
#include <stdio.h>
#include <string.h>

typedef struct {
  int b;
  int e;
  int E;
  int n;
  int s;
  int t;
  int T;
  int v;
} command;

void err(char pars_elem);
char parser(int argc, char **argv, command *command_t);
char print_flag(int argc, char **argv, command *command_t);

#endif  // CAT_C
