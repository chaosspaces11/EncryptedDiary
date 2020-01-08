//
// Created by Michael Chen on 10/12/2019.
//

#ifndef ENCRYPTEDDIARY_SECURITY_H
#define ENCRYPTEDDIARY_SECURITY_H


void encrypt(char* filePath);

void decrypt(char* filePath);

int verifyPassword();

int getPasswordLength();

#endif //ENCRYPTEDDIARY_SECURITY_H
