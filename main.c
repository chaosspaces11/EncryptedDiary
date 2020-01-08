//
// Created by Michael Chen on 10/12/2019.
//


#include <stdio.h>
#include "Security.h"
#include "Enter.h"
#include "View.h"
#include <string.h>

int main() {
    printf("Welcome to your Personal Diary.\n");
    while (!verifyPassword());

    displayHelp();

    char command;
    printf("> ");

    while (scanf("%c",&command) != EOF) {
        switch (command) {
            case '\n':
                continue;
            case 'd':
                displayEntries();
                break;
            case 'c':
                createEntry();
                break;
            case 'v': {
                char date[188];
                fgets(date, 13, stdin);
                strcpy(date+9, ".txt");
                openEntry(date+1);
                break;
            }
            case 'q':
                printf("Goodbye!\n");
                return 0;
            case '?':
                displayHelp();
                break;
            default:
                printf("Invalid command entered. Enter '?' for help\n");
                break;
        }
        printf("> ");
    }

    return 0;
}