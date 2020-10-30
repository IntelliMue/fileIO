/* Validation of file type functions
 *
 */

#define _POSIX_C_SOURCE 200809L

#include <sys/stat.h>
#include <sys/types.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "fileIO.h"

/* Test for regular files*/
bool isRegFile(char *fileName) {
    struct stat fileStat;

    if (stat(fileName, &fileStat) == -1){   
        fprintf(stderr, "Requested file %s is not a valid file\n", fileName);
        return false;
    }   

    if(S_ISREG(fileStat.st_mode) == 0) {   
        fprintf(stderr, "%s is not a regular file\n", fileName);
        return false;
    }   
    return true;
}


/* Test for directories*/
bool isDir(char *fileName) {
    struct stat fileStat;

    if (stat(fileName, &fileStat) == -1) {   
        fprintf(stderr, "Cmdline argument is"
                " not a valid file/directory\n");
        return false;
    }   

    if(S_ISDIR(fileStat.st_mode) == 0) {   
        fprintf(stderr, "%s is not a directory\n", fileName);
        return false;
    }   
    return true;
}


/* Get the file size of valid files*/
int fileSize(char *fileName) {
    struct stat fileStat;

    if(stat(fileName, &fileStat) == -1) {   
        fprintf(stderr, "Requested file %s is not a valid file\n", fileName);
        return -1;
    }
    return fileStat.st_size;
}


/* Check if a bland file exists*/
bool fileExists(char *fileName) {
    struct stat fileStat;

    if(stat(fileName, &fileStat) == -1) {   
        fprintf(stderr, "Requested file %s cannot be found\n", fileName);
        return false;
    }
    return true;
}


/* check if a file is executable*/
bool fileExecs(char *fileName) {
    struct stat fileStat;

    if (stat(fileName, &fileStat) == -1) { 
        fprintf(stderr, "Requested file %s is not a valid file\n", fileName);
        return false;
    }   

    if((fileStat.st_mode & S_IXOTH) == 0) {   
        fprintf(stderr, "%s is not a executable\n", fileName);
        return false;
    }   
    return true;
}


/* check if a file is readable*/
bool isReadable(char *fileName) {
    struct stat fileStat;
    if (stat(fileName, &fileStat) == -1) { 
        fprintf(stderr, "Requested file %s is not a valid file\n", fileName);
        return false;
    }   

    if((fileStat.st_mode & S_IROTH) == 0) {   
        fprintf(stderr, "%s is not readable\n", fileName);
        return false;
    }   
    return true;
}

/* save n characters from a passed string to a file*/
ssize_t saveline(char **linePtr, char *fileName) {
    ssize_t savedCount = 0;

    if(!linePtr) {
        puts("Nothing to save to file");
        return -1;
    }

    FILE *saveFile;

    saveFile = fopen(fileName, "w+");
    if(saveFile == NULL)
    {
        fprintf(stderr, "\nFailed to save to file %s\n\n", fileName);
        return(-1);
    }

    savedCount = fprintf(saveFile, "%s", linePtr[0]);

    fclose(saveFile);

    return savedCount;
}