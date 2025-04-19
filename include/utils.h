#ifndef UTILS_H
#define UTILS_H

typedef enum log_level
{
    SUCCESS,
    FAILURE
}   log_level;

void log_message(log_level level, char *message);

#endif