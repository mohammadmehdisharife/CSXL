#include "./function.h"
#include "./memory.h"
#include "./log.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

char* make_string(char *args, int number_line)
{
    char *string = NULL;
    char *token;
    while ((token = strtok(NULL, " ")) != NULL) {

        if (token[0] == '$') {
            int type = exist_variable(token + 1);

            if (type == -1) {
                print_error("variable is not exist.", number_line);
            } else if (type == 0) {
                int int_value = load_int(token + 1);
                char value[20];
                sprintf(value, "%d", int_value);
                if (string == NULL) {
                    string = realloc(string, strlen(value) + 1);
                    strcpy(string, value);
                    strcat(string, " ");
                } else {
                    string = realloc(string, strlen(value) + 1);
                    strcat(string, value);
                    strcat(string, " ");
                }
            } else if (type == 1) {
                char *value = load_str(token + 1);
                if (string == NULL) {
                    string = realloc(string, strlen(value) + 1);
                    strcpy(string, value);
                    strcat(string, " ");
                } else {
                    string = realloc(string, strlen(value) + 1);
                    strcat(string, value);
                    strcat(string, " ");
                }
            }
        }

        else {
            if (string == NULL) {
                string = realloc(string, strlen(token) + 1);
                strcpy(string, token);
                strcat(string, " ");
            } else {
                string = realloc(string, strlen(string) + strlen(token) + 1);
                strcat(string, token);
                strcat(string, " ");
            }
        }

    }
    return string;
}

void print_function(char *args, int number_line)
{
    strtok(args, " ");
    printf("%s\n",make_string(args,number_line));
}

void shell_function(char *args, int number_line)
{
    char *space = strchr(args, ' ');
    char *command = make_string(space++, number_line);
    system(command);
}

void int_function(char *args, int number_line)
{
    char *name;
    char *value_str;
    int value;
    
    char *token = strtok(args, " ");
    
    name = strtok(NULL, " ");
    if (name == NULL) {
        print_error("Syntax: INT <name> <value>", number_line);
        return;
    }
    
    if (name[0] == '$') {
        print_error("Variable name cannot start with '$'", number_line);
        return;
    }
    
    value_str = strtok(NULL, "");
    if (value_str == NULL) {
        print_error("INT: Value is required", number_line);
        return;
    }
    
    while (*value_str == ' ') value_str++;
    
    if (strlen(value_str) > 9) {
        print_error("Value must be a valid integer",number_line);
    }

    char *endptr;
    value = strtol(value_str, &endptr, 10);
    
    if (endptr == value_str || *endptr != '\0') {
        print_error("Value must be a valid integer", number_line);
        return;
    }
    
    errno = 0;
    if (errno == ERANGE) {
        print_error("Number is too large or too small", number_line);
        return;
    }
    
    add_int(value, name);
}

void str_function(char *args, int number_line)
{
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

void execute_command(char *function, char *args, int number_line)
{
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
