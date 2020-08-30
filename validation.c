/* Validation of file type functions
 *
 */
#include <sys/stat.h>
#include <sys/types.h>
#include <stdbool.h>
#include <stdio.h>
#include "validation.h"

/* Test of the validation library*/
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

    printf("%s size is %d\n", fileName, fileSize(fileName));


    // Test directory functions
    printf(border, dirName);

    dirStatus = mkdir(dirName, S_IRWXU);
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
    isReadable(dirName);

    fileExecs(dirName);

    printf("%s size is %d\n", dirName, fileSize(dirName));

    fclose(testFile);
    return result;
}

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
