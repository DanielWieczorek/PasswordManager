
#include "core.h"

void writeEncryptedRecord(char* username, char* site, char* password, char* key, char* fileName){
    char* paddedusername = calloc(sizeof(char), 256);
    sprintf( paddedusername, "%0256d", username );
    char* paddedpassword = calloc(sizeof(char), 256);
    sprintf( paddedpassword, "%0256d", username );
    char * encrypted_username = encryptString(username, 256, key, TWOFISH);
    char * hashed_site = hashString(site, SHA512);
    char * encrypted_password = encryptString(paddedpassword, 256, key, TWOFISH);
    
    Record* record = createRecord(encrypted_username, hashed_site, encrypted_password);
    saveRecord(fileName, record);
    
    
}