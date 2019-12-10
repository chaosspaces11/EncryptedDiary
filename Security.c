//
// Created by Michael Chen on 10/12/2019.
//

#include "Security.h"
#include "stdlib.h"
#include "string.h"

#define PASSCODE "deadbeef"
#define PASSLEN  8

// Takes in a filename and encrypts each byte in accordance with
// the passcode
void encrypt(char* fileName)
{

    char* password = PASSCODE;
    char* homeDir = getenv("$HOME");
    char* diaryDir = malloc(sizeof(homeDir) + strlen("/.diary") + 1);
    memset(diaryDir, 0, strlen(homeDir) + strlen("/.diary/") + strlen(fileName)+ 1);
    strcat(diaryDir, homeDir);
    strcat(diaryDir, "/.diary");
    strcat(diaryDir, "/");
    strcat(diaryDir, fileName);
}