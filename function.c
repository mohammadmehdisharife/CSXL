#include "./function.h"
#include "./memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_function(char *args, int number_line) {
  char *arg;
  strtok(args, " ");

  while ((arg = strtok(NULL, " ")) != NULL) {
    if (arg[0] == '$') {
      int type = exist_variable(arg + 1);
      if (type == -1) {
        printf("ERROR: %s is not a variable",arg + 1);
        exit(1);
      } else if (type == 0) {
        printf("%d ", load_int(arg + 1));
      }else if (type == 1) {
        printf("%s ", load_str(arg + 1));
      }
    } else {
      printf("%s ", arg);
    }
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
  add_int(value, name);
  // print_memory();
}

void str_function(char *args, int number_line) {
  char *name;
  char *value;

  strtok(args, " ");
  name = strtok(NULL, " ");
  value = strtok(NULL, "");

  if (name == NULL || value == NULL) {
    printf("Error: Invalid syntax at line %d\n", number_line);
    return;
  }

  add_str(value, name);
  // print_memory();
}

void execute_command(char *function, char *args, int number_line) {
  if (strcmp(function, "PRINT") == 0) {
    print_function(args, number_line);
  } else if (strcmp(function, "SHELL") == 0) {
    shell_function(args, number_line);
  } else if (strcmp(function, "INT") == 0) {
    int_function(args, number_line);
  } else if (strcmp(function, "STR") == 0) {
    str_function(args, number_line);
  } else {
    printf("\"%s\" is no a function | line <%d>\n", function, number_line);
    exit(1);
  }
}
