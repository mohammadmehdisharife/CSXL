#include <stdio.h>
#include <string.h>

void print_function(char* args, int number_line) {
  char *arg;
  strtok(args, " ");

  while ((arg = strtok(NULL, " ")) != NULL) {
    printf("%s ",arg);
  }
  printf("\n");
}

void execute_command(char* function, char* args, int number_line) {
  if (strcmp(function, "PRINT") == 0) {
    print_function(args,number_line);
  }
}

int main(int argc, char *argv[])
{
  if (argc != 2) {
    fprintf(stderr, "Usign: %s <filename>\n", argv[0]);
    return 0;
  }

  FILE *file;
  file = fopen(argv[1],"r");
  if (file == NULL) {
    fprintf(stderr, "%s opening failed.\n", argv[1]);
  }

  char buffer[1024];
  char args[1024];
  char *function;
  int number_line = 1;
  while (fgets(buffer, sizeof(buffer), file)) {
    buffer[strcspn(buffer, "\n")] = '\0';
    strcpy(args, buffer);
    function = strtok(buffer," ");

    //print status 
    /* printf("args: %s\n",args);
    printf("function: %s\n",function);
    printf("number_line: %d\n",number_line); */

    execute_command(function, args, number_line);

    number_line++;
  }
  return 0;
}
