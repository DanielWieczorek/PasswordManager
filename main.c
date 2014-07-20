
#include <stdio.h>
#include <stdlib.h>
#include "src/core.h"
#include "src/passwordgenerator.h"
#include "src/persistence.h"

#define OK       0
#define NO_INPUT 1
#define TOO_LONG 2
static int getLine(char *prmpt, char *buff, size_t sz);
void insertEntry();
void retrieveEntry();

char *keys[2]={"i","r"};
void (*function[2])()={insertEntry,retrieveEntry};

int main(int argc, char** argv) {
    char *line = calloc(sizeof(char),20);
    while(strcmp(line,"exit")){
        getLine("What would you like to do?",line, 20);
        int i=0, foundIndex=0;
        for(i=0; i<sizeof(keys);i++)
            if(!strcmp(line,keys[i])){
                foundIndex = i;
                break;
            }
        (*function[foundIndex])();
    }
    return 0;
}

void retrieveEntry(){
    initCryptographyModule();
    char* fileName = "./pw";
    char* site = calloc(sizeof (char), 20);
    char* key = calloc(sizeof (char), 50);
    getLine("please enter the site name:\n", site, 20);
    getLine("please enter the key:\n", key, 50);
    char* hashedKey = hashString(key, SHA256);

    if (!doesCredentialEntryExist(fileName)) {
        printf("there are no credentials set. Credentials with the key entered are created");
        writeEncryptedRecord("foo", CREDENTIAL_SITE, key, hashedKey, fileName);
    }
    if (checkCredentials(hashedKey, fileName)) {
        printf("the hashed key is: %s\n", hashedKey);
        free(key);
        Record* encrypted = retrieveEncryptedRecord(site, fileName);
        if (encrypted) {
            Record *decrypted = decryptRecord(encrypted, hashedKey);
            printf("encrypted username: %s\n", decrypted->username);
            printf("encrypted site: %s\n", decrypted->site);
            printf("encrypted password: %s\n", decrypted->password);
            free(decrypted);
        } else
            printf("nothing found\n");
        free(encrypted);
    } else
        printf("the credentials are wrong. sorry!");
    free(site);
    free(hashedKey);
    freeCryptographyModuleMemory();
}


void insertEntry(){
    initCryptographyModule();
    char* fileName = "./pw";
    char* username = calloc(sizeof (char), 20);
    char* site = calloc(sizeof (char), 20);
    char* key = calloc(sizeof (char), 50);
    getLine("please enter your username:\n", username, 20);
    getLine("please enter the site name:\n", site, 20);
    getLine("please enter the key:\n", key, 50);
    char* hashedKey = hashString(key, SHA256);

    if (!doesCredentialEntryExist(fileName)) {
        printf("there are no credentials set. Credentials with the key entered are created");
        writeEncryptedRecord("foo", CREDENTIAL_SITE, key, hashedKey, fileName);
    }
    if (checkCredentials(hashedKey, fileName)) {
        printf("the hashed key is: %s\n", hashedKey);
        free(key);
        char* password = generatePassword(12, BASE85);
        printf("the generated password is: %s\n", password);
        writeEncryptedRecord(username, site, password, hashedKey, fileName);
        Record* encrypted = retrieveEncryptedRecord(site, fileName);
        if (encrypted) {
            Record *decrypted = decryptRecord(encrypted, hashedKey);

            printf("encrypted username: %s\n", decrypted->username);
            printf("encrypted site: %s\n", decrypted->site);
            printf("encrypted password: %s\n", decrypted->password);
            free(decrypted);
        } else
            printf("nothing found\n");
        free(encrypted);
        free(password);
    } else
        printf("the credentials are wrong. sorry!");
    free(username);
    free(site);
    free(hashedKey);

    freeCryptographyModuleMemory();

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