// function.c

#include "./function.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>

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

void int_function(char *args, int number_line) {
  char *name;
  int value;
  strtok(args, " ");
  name = strtok(NULL, " ");
  value = atoi(strtok(NULL, " "));
  printf("args: %s\nname: %s\nvalue: %d\n",args,name,value);
}

void execute_command(char *function, char *args, int number_line) {
  if (strcmp(function, "PRINT") == 0) {
    print_function(args, number_line);
  } else if (strcmp(function, "SHELL") == 0) {
    shell_function(args, number_line);
  } else if (strcmp(function, "INT") == 0) {
    int_function(args, number_line);
  }  
}
