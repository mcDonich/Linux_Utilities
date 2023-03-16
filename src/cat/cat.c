#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef struct {
  int b;
  int e;
  int n;
  int t;
  int s;
  int v;
  int l;
  int u;
} command;

void error(char);
char parser(int, char **, command *);
char print_flag(int, char **, command *);

int main(int argc, char **argv) {
  command command_t = {0};
  struct flock stdout_lock;
  char pars_elem = 0;
  if (argc > 1) {
    pars_elem = parser(argc, argv, &command_t);
    if (pars_elem) {
        error(pars_elem);
    } else {
        print_flag(argc, argv, &command_t);
    }
  } else if (argc == 1) {
      char sym = 1;
      while (sym) {
          sym = getc(stdin);
          putchar(sym);
      }
  }
  return 0;
}

void error(char pars_elem) {
    fprintf(stderr, " cat: illegal option\nusage: cat [-benstuv] [file ...]\\n\");");
}

char parser(int argc, char** argv, command *command_t) {
    int erro = 0;
    char ret_value = 0;
    if (argc > 1) {
        for (int i = 1; i < argc && !erro; i++) {
            int word_flag = 0;
            for (int j = 1; j < (int)strlen(argv[i]) && !word_flag && !erro; j++) {
                if (argv[i][0] == '-') {
                    switch (argv[i][j]) {
                        case 'b':
                            command_t->b = 1;
                            break;
                        case 'e':
                            command_t->e = command_t->v = 1;
                            break;
                        case 'E': // GNU
                            command_t->e = command_t->v = 1;
                            break;
                        case 'n':
                            command_t->n = 1;
                            break;
                        case 's':
                            command_t->s = 1;
                            break;
                        case 'l':
                            command_t->l = 1;
                            break;
                        case 't':
                            command_t->t = command_t->v = 1;
                            break;
                        case 'T': // GNU
                            command_t->t = command_t->v = 1;
                            break;
                        case 'u':
                            command_t->u = 1;
                            break;
                        case 'v':
                            command_t->v = 1;
                            break;
                        case '-':
                            if (strcmp(argv[i], "--number-nonblank") == 0) command_t->b = 1;
                            if (strcmp(argv[i], "--number") == 0) command_t->n = 1;
                            if (strcmp(argv[i], "--squeeze-blank") == 0) command_t->s = 1;
                            if (!command_t->b && !command_t->n && !command_t->s) {
                                ret_value = argv[i][j];
                                erro = 1;
                            }
                            word_flag = 1;
                            break;
                        default:
                            ret_value = argv[i][j];
                            erro = 1;
                            break;
                    }
                }
            }
        }
    }
    return (erro) ? ret_value : 0;
}

char print_flag(int argc, char** argv, command *command_t) {
    FILE *file;
    int enter_one = 1;
    int enter_two = 1;
    int double_check = 1;
    int number = 1;
    char sym;
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] != '-') {
            if ((file = fopen(argv[i], )))
        }
    }
}