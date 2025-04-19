#include "../include/utils.h"
#include <stdio.h>

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define RESET "\033[0m"

void log_message(log_level level, char *message)
{
    switch(level)
    {
        case SUCCESS:
            printf("%s", GREEN);
            break;
        case FAILURE:
            printf("%s", RED);
            break;
    }
    printf(" %s\n", message);
    printf("%s", RESET);
}