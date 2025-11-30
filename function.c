// function.c

#include "./function.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_function(char *args, int number_line) {
  char *arg;
  strtok(args, " ");

  while ((arg = strtok(NULL, " ")) != NULL) {
    printf("%s ", arg);
  }
  printf("\n");
}

void shell_function(char *args, int number_line) {
  char *space = strchr(args, ' ');
  if (space != NULL) {
    system(space + 1);
  } else {
    printf("Error: No command at line %d\n", number_line);
  }
}

void execute_command(char *function, char *args, int number_line) {
  if (strcmp(function, "PRINT") == 0) {
    print_function(args, number_line);
  } else if (strcmp(function, "SHELL") == 0) {
    shell_function(args, number_line);
  }
}
