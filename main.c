
#include <stdio.h>
#include <stdlib.h>

#include "src/passwordgenerator.h"


int main(int argc, char** argv) {
    int i=0;
    for(i=0;i<100;i++)
    printf("pw: %s", generatePassword(12,BASE85));
    return (EXIT_SUCCESS);
}

