//
// Created by Michael Chen on 10/12/2019.
//

#include "Enter.h"
#include "Security.h"
#include "stdio.h"
#include "stdlib.h"

#include "string.h"
#include "time.h"

void enter()
{
    char string[BUFSIZ];
    time_t currTime = time(NULL);
    char timeString[80];
    strftime(timeString, sizeof(timeString), "%d-%m-%y.txt", localtime(&currTime));
    char* homeDir = getenv("HOME");
    char fileString[BUFSIZ];
    memset(fileString, 0, BUFSIZ);

    strcat(fileString, homeDir);
    strcat(fileString, "/.diary/");
    strcat(fileString, timeString);

    printf("%s\n", fileString);

    FILE* diaryFile = fopen(fileString, "r");
    if (diaryFile == NULL)
    {
        fclose(diaryFile);
        diaryFile = fopen(fileString, "a+");
        fprintf(diaryFile, "%s\n", timeString);
    }
    else
    {
        fclose(diaryFile);
        diaryFile = fopen(fileString, "a+");
    }

    int response = scanf("%s", string);
    while(response != 0 && response != EOF)
    {
        fprintf(diaryFile, "%s\n", string);
        response = scanf("%s", string);
    }
    fclose(diaryFile);
}