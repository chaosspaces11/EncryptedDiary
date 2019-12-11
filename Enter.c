//
// Created by Michael Chen on 10/12/2019.
//

#include "Enter.h"
#include "Security.h"
#include "stdio.h"
#include "stdlib.h"

void enter()
{
    char string[BUFSIZ];
    int response = scanf("%s", string);
    while(response != 0)
    {
        fprintf(stdout, "%s\n", string);
        response = scanf("%s", string);
    }
}