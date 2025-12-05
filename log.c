#include "./log.h"
#include <stdio.h>
#include <stdlib.h>

void print_error(char *msg, int number_line)
{
    fprintf(stderr, "\n");
    fprintf(stderr, "\033[1;31m╔══════════════════════════════════════════╗\n");
    fprintf(stderr, "\033[1;31m║              RUNTIME ERROR               ║\n");
    fprintf(stderr, "\033[1;31m╚══════════════════════════════════════════╝\n");
    fprintf(stderr, "\033[1;37m│ Line: \033[1;33m%d\n", number_line);
    fprintf(stderr, "\033[1;37m│ Message: \033[1;31m%s\n", msg);
    fprintf(stderr, "\033[1;31m╰──────────────────────────────────────────\n");
    fprintf(stderr, "\033[0m\n");
    exit(1);
}
