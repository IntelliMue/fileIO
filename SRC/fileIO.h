#ifndef FILE_FUNCS
#define FILE_FUNCS

#include <stdbool.h>
#include <stdio.h>

bool isRegFile(char *fileName);
bool isDir(char *fileName);
int fileSize(char *fileName);
bool fileExists(char *fileName);
bool fileExecs(char *fileName);
bool isReadable(char *fileName);

ssize_t saveline(char **linePtr, char *fileName);

#endif