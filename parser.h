// parser.h
#ifndef PARSER_H
#define PARSER_H

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGS 64

char **parseInput(char *input);
void freeArgs(char **args);

#endif /* PARSER_H */

