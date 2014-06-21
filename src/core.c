
#include "core.h"

void writeEncryptedRecord(char* username, char* site, char* password, char* key, char* fileName){
    char* paddedusername = calloc(sizeof(char), 256);
        char* paddedpassword = calloc(sizeof(char), 256);
    sprintf( paddedusername, "%s", username );
    sprintf( paddedpassword, "%s", password );
   
   
    
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

Record* decryptRecord(Record* record, char* key){
    char* decodedPassword = calloc(sizeof(char),256);
    char* decodedUsername = calloc(sizeof(char),256);
    char* decodedSite = calloc(sizeof(char),512);
    
    int* passwordSize =calloc(sizeof(int),1);
    int* usernameSize =calloc(sizeof(int),1);
    int* siteSize =calloc(sizeof(int),1);
    
    *passwordSize = 512;
    *usernameSize = 512; 
    *siteSize = 1024;
     
    
    base64decode(record->password, 512, decodedPassword, passwordSize);
    base64decode(record->username, 512, decodedUsername, usernameSize);
    base64decode(record->site, 1024, decodedSite, siteSize);
    
    record->password = decryptString(decodedPassword, 512, key, TWOFISH);
    record->username = decryptString(decodedUsername, 512, key, TWOFISH);
    record->site = decodedSite;
    
    return record;

}