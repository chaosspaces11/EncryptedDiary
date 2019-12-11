//
// Created by Michael Chen on 10/12/2019.
//

#include "Security.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define PASSCODE "deadbeef"
#define PASSLEN  8

// Takes in a filename and encrypts each byte in accordance with
// the passcode
void encrypt(char* fileName)
{
    char* password = PASSCODE;

    extern char* environ;

    // Getting directory set by the $HOME environment variable
    char* homeDir = getenv("HOME");

    if (homeDir == NULL)
    {
        perror("$HOME: ");
    }

    // Getting space for variable containing the directory of the diary
    int diaryDirLen = (int)strlen(homeDir) + (int)strlen("/.diary/") + (int)strlen(fileName)+ 1;
    char* diaryDir = malloc((size_t)diaryDirLen);
    memset(diaryDir, 0, diaryDirLen);
    strcat(diaryDir, homeDir);
    strcat(diaryDir, "/.diary");
    strcat(diaryDir, "/");
    strcat(diaryDir, fileName);

    FILE* diaryFile = fopen(diaryDir, "r+");

    // Ensuring we got the file
    if (diaryFile == NULL)
    {
        fprintf(stderr, "Encrypt: Diary file %s could not be opened for reading and writing\n", fileName);
    }

    int currChar = fgetc(diaryFile);
    int len = 0;
    while(currChar != EOF)
    {
        // Shifts current character back one
        fseek(diaryFile, -1, SEEK_CUR);
        // Vigenere cipher encryption
        currChar = currChar + password[len % PASSLEN];
        len++;

        // Prints encrypted character
        fputc(currChar, diaryFile);

        // Getting next character
        currChar = fgetc(diaryFile);
    }
}

void decrypt(char* fileName)
{
    char* password = PASSCODE;

    extern char* environ;

    // Getting directory set by the $HOME environment variable
    char* homeDir = getenv("HOME");

    if (homeDir == NULL)
    {
        perror("$HOME: ");
    }

    // Getting space for variable containing the directory of the diary
    int diaryDirLen = (int)strlen(homeDir) + (int)strlen("/.diary/") + (int)strlen(fileName)+ 1;
    char* diaryDir = malloc((size_t)diaryDirLen);
    memset(diaryDir, 0, diaryDirLen);
    strcat(diaryDir, homeDir);
    strcat(diaryDir, "/.diary");
    strcat(diaryDir, "/");
    strcat(diaryDir, fileName);

    FILE* diaryFile = fopen(diaryDir, "r+");

    // Ensuring we got the file
    if (diaryFile == NULL)
    {
        fprintf(stderr, "Encrypt: Diary file %s could not be opened for reading and writing\n", fileName);
    }

    int currChar = fgetc(diaryFile);
    int len = 0;
    while(currChar != EOF)
    {
        // Shifts current character back one
        fseek(diaryFile, -1, SEEK_CUR);
        // Vigenere cipher encryption
        currChar = currChar - password[len % PASSLEN];
        len++;

        // Prints encrypted character
        fputc(currChar, diaryFile);

        // Getting next character
        currChar = fgetc(diaryFile);
    }
}