
#include "core.h"

void writeEncryptedRecord(char* username, char* site, char* password, char* key, char* fileName){
    char* paddedusername = calloc(sizeof(char), 256);
        char* paddedpassword = calloc(sizeof(char), 256);
    sprintf( paddedusername, "%0256d", username );
    sprintf( paddedpassword, "%0256d", password );
   
   
    
    char * encrypted_username =  calloc(sizeof(char), 512);
     base64encode(encryptString(paddedusername, 256, key, TWOFISH),256,encrypted_username, 512);
    char * hashed_site = calloc(sizeof(char), 1024);
    base64encode(hashString(site, SHA512),512, hashed_site,1024);
    char * encrypted_password = calloc(sizeof(char), 512);
    base64encode(encryptString(paddedpassword, 256, key, TWOFISH),256,encrypted_password, 512);
    
    Record* record = createRecord(encrypted_username, hashed_site, encrypted_password);
    saveRecord(fileName, record);
    
    
}


Record* retrieveEncryptedRecord(char* site, char* fileName){
    char * hashed_site = calloc(sizeof(char), 1024);
    base64encode(hashString(site, SHA512),512, hashed_site,1024);
  
    return getRecordBySite(fileName, hashed_site);
    
}