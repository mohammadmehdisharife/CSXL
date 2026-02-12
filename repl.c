#include "./function.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char buffer[1024];
    char args[1024];
    char *function;
    int line_number = 1;

    printf("CSXL Interpreter REPL\n");
    printf("Type 'EXIT' to quit\n");
    printf("----------------------\n");

    while (1) {
        printf("> ");
        fflush(stdout);

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("\n");
            break;
        }

        buffer[strcspn(buffer, "\n")] = '\0';

        if (buffer[0] == '\0') {
            continue;
        }

        strcpy(args, buffer);
        function = strtok(buffer, " ");

        if (function == NULL) {
            line_number++;
            continue;
        }

        if (strcmp(function, "#") == 0 || function[0] == '#') {
            line_number++;
            continue;
        }

        execute_command(function, args, line_number);
        line_number++;
    }

    return 0;
}