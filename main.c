
#include <stdio.h>
#include <stdlib.h>
#include "src/core.h"
#include "src/passwordgenerator.h"
#include "src/persistence.h"

#define OK       0
#define NO_INPUT 1
#define TOO_LONG 2
static int getLine(char *prmpt, char *buff, size_t sz);

int main(int argc, char** argv) {
    initCryptographyModule();
    char* fileName = "./foo";
    char* username = calloc(sizeof (char), 20);
    char* site = calloc(sizeof (char), 20);
    char* key = calloc(sizeof (char), 50);
    getLine("please enter your username:\n", username, 20);
    getLine("please enter the site name:\n", site, 20);
    getLine("please enter the key name:\n", key, 50);
    char* hashedKey = hashString(key, SHA256);
    
    
    printf("the hashed key is: %s\n", hashedKey);
    
    free(key);
    char* password = generatePassword(12, BASE85);
    printf("the generated password is: %s\n", password);

    writeEncryptedRecord(username, site, password, hashedKey, fileName);


    Record* encrypted = getRecordBySite(fileName, hashString(site, SHA512));
    if (encrypted) {
        printf("encrypted username: %s\n", encrypted->username);
        printf("encrypted site: %s\n", encrypted->site);
        printf("encrypted password: %s\n", encrypted->password);
    } else
        printf("nothing found\n");
}

static int getLine(char *prmpt, char *buff, size_t sz) {
    int ch, extra;

    // Get line with buffer overrun protection.
    if (prmpt != NULL) {
        printf("%s", prmpt);
        fflush(stdout);
    }
    if (fgets(buff, sz, stdin) == NULL)
        return NO_INPUT;

    // If it was too long, there'll be no newline. In that case, we flush
    // to end of line so that excess doesn't affect the next call.
    if (buff[strlen(buff) - 1] != '\n') {
        extra = 0;
        while (((ch = getchar()) != '\n') && (ch != EOF))
            extra = 1;
        return (extra == 1) ? TOO_LONG : OK;
    }

    // Otherwise remove newline and give string back to caller.
    buff[strlen(buff) - 1] = '\0';
    return OK;
}