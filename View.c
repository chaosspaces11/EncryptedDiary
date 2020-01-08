//
// Created by Mrinaank Sinha on 10/12/19.
//

#include "View.h"
#include "Security.h"
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void displayEntries() {
    DIR *dir;
    struct dirent *entry;

    char* homeDir = getenv("HOME");
    char fileString[BUFSIZ];
    memset(fileString, 0, BUFSIZ);
    strcat(fileString, homeDir);
    strcat(fileString, "/.diary");

    if ((dir = opendir(fileString)) != NULL) {
        //file has been opened
        while ((entry = readdir(dir)) != NULL) {
            printf("%s\n", entry->d_name);
        }
    } else {
        //error
        perror("");
        abort();
    }
}

void openEntry(char *entry) {
    printf("Opening entry %s...\n",entry);

    char* homeDir = getenv("HOME");
    char fileString[BUFSIZ];
    memset(fileString, 0, BUFSIZ);
    strcat(fileString, homeDir);
    strcat(fileString, "/.diary/");
    strncat(fileString,entry,BUFSIZ-strlen(fileString)-1);

    printf("Decrypting entry...%s\n",fileString);
    decrypt(fileString);

    FILE* file = fopen(fileString,"r");

    if (file == NULL) {
        perror("Opening Entry: ");
        abort();
    }
    //TODO: BROKEN FROM HER ON OUT I THINK
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line,&len,file)) != -1) {
        printf("%s",line);
    }

    free(line);
}


