/* Test of the fileIO library*/

#include <sys/stat.h>
#include <sys/types.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "fileIO.h"

int main (int argc, char **argv) {
    int result = 0;
    int dirStatus = 0;
    char *fileName = {"fileTest.txt"};
    char *dirName = {"dirTest"};
    char *border = {"\n=================== %s ===================\n\n"};



    if(argc >= 1) {
        char *exeName = argv[0];

        printf(border, exeName);

        if(fileExists(exeName)) {
            printf("%s exists\n", exeName);
        }

        if(isRegFile(exeName)) {
            printf("%s is a regular file\n", exeName);
        }

        isDir(exeName);

        if(isReadable(exeName)) {
            printf("%s is a readable file\n", exeName);
        }

        if(fileExecs(exeName)) {
            printf("%s is an executable file\n", exeName);
        }

        printf("%s size is %d\n", exeName, fileSize(exeName));

    }

    // Test file functions
    printf(border, fileName);


    FILE *testFile;
    testFile = fopen(fileName, "w+");
    if(testFile == NULL)
    {
        fprintf(stderr, "\nFailed to create test file\n\n");
        return(result = -1);
    }

    if(fileExists(fileName)) {
        printf("%s exists\n", fileName);
    }

    if(isRegFile(fileName)) {
        printf("%s is a regular file\n", fileName);
    }

    isDir(fileName);

    if(isReadable(fileName)) {
        printf("%s is a readable file\n", fileName);
    }

    fileExecs(fileName);

    char *hello = "Hello World!\n";
    saveline(&hello, fileName);

    printf("%s size is %d\n", fileName, fileSize(fileName));


    // Test directory functions
    printf(border, dirName);

    struct stat fileStat;
    if(stat(dirName, &fileStat) == -1) {
        dirStatus = mkdir(dirName, S_IRWXU);
    }
    
    if(dirStatus) {
        fprintf(stderr, "\nFailed to create %s directory\n\n", dirName);
            return(result = -1);
    }

    if(fileExists(dirName)) {
        printf("%s exists\n", dirName);
    }

    isRegFile(dirName);

    if(isDir(dirName)) {
        printf("%s is a directory\n", dirName);
    }
    
    if(isReadable(dirName)) {
        printf("%s is readable\n", dirName);
    }

    fileExecs(dirName);

    printf("%s size is %d\n", dirName, fileSize(dirName));

    fclose(testFile);
    return result;
}