//
// Created by Michael Chen on 10/12/2019.
//

#include "Security.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>

#define PASSCODE "deadbeef"
#define PASSLEN  strlen(PASSCODE)

// Takes in a filename and encrypts each byte in accordance with
// the passcode
void encrypt(char *filePath) {
    char *password = PASSCODE;

    FILE *diaryFile = fopen(filePath, "r+");

    // Ensuring we got the file
    if (diaryFile == NULL) {
        fprintf(stderr, "Encrypt: Diary file %s could not be opened for reading and writing\n", filePath + strlen(filePath) - 12);
    }

    int currChar = fgetc(diaryFile);
    int len = 0;
    while (currChar != EOF) {
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
    fclose(diaryFile);
}

void decrypt(char *filePath) {
    char *password = PASSCODE;

    FILE *diaryFile = fopen(filePath, "r+");

    // Ensuring we got the file
    if (diaryFile == NULL) {
        fprintf(stderr, "Decrypt: Diary file %s could not be opened for reading and writing\n", filePath + strlen(filePath) - 12);
    }

    int currChar = fgetc(diaryFile);
    int len = 0;
    while (currChar != EOF) {
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
    fclose(diaryFile);
}

int verifyPassword() {

    FILE *fp = fopen("/dev/tty", "r+");

    if (fp == NULL) {
//        perror("Verify Password: ");
//        abort();
        fp = stdin;
    }

    struct termios oldSettings;
    struct termios newSettings;

    //Load current settings into variable
    if (tcgetattr(fileno(fp), &oldSettings)) {
        perror("Verify Password: ");
        abort();
    }

    //Copy old settings to new settings
    memcpy(&newSettings, &oldSettings, sizeof(struct termios));

    //Edit certain flags (its all boolean algebra stuff): See man termios
    //tl;dr disables echo and cannoincal input, waits for atleast one byte before processing
    newSettings.c_lflag &= ~(ICANON | ECHO);
    newSettings.c_cc[VTIME] = 0;
    newSettings.c_cc[VMIN] = 1;

    //Set new settings
    if (tcsetattr(fileno(fp), TCSANOW, &newSettings)) {
        perror("Verify Password: ");
        abort();
    }

    int index = 0; //Keeps track of the number of characters entered
    int c;
    int validTill = -1; //Stores till where the password is valid

    printf("Please enter password: ");

    //127 is delete character
    const int DELETE = 127;

    //Get characters as typed in and verify
    while ((c = fgetc(fp)) != '\n' && c != EOF) {
        if (c != DELETE) {
            printf("*");

            if (index - 1 == validTill && c == PASSCODE[index]) {
                validTill++;
            }
            index++;

        } else if (index > 0) {
            fputc(0x8, fp); //Go to the second last character
            fputc(' ', fp); //Make the last character disappear
            fputc(0x8, fp); //Go back again so the cursor is at end
            index--;
            if (validTill >= index) {
                validTill--;
            }
        }
    }
    printf("\n");

    //Reset original settings
    if (tcsetattr(fileno(fp), TCSANOW, &oldSettings)) {
        perror("Verify Password: ");
        abort();
    }
    fclose(fp);

    //Check if entire password is valid
    if (validTill == PASSLEN - 1 && index == PASSLEN) {
        return 1;
    } else {
        printf("Incorrect Password - Please try again.\n");
        return 0;
    }

//    char *userInput = calloc(getPasswordLength() + 1, sizeof *userInput);
//    scanf("%s", userInput);
//    while (strcmp(userInput, PASSCODE) == 0) {
//        scanf("%s", userInput);
//    }
//    free(userInput);
}

int getPasswordLength() {
    return PASSLEN;
}