
#include "core.h"

void writeEncryptedRecord(const char* username, const char* site, const char* password, const  char* key, const char* fileName){
    char* paddedusername = calloc(sizeof(char), 256);
    char* paddedpassword = calloc(sizeof(char), 256);
    sprintf( paddedusername, "%s", username );
    sprintf( paddedpassword, "%s", password );
    
    
    char * encrypted_username =  calloc(sizeof(char), 512);
    base64encode(encryptString(paddedusername, 256, key, TWOFISH),256,encrypted_username, 512);
    char * hashed_site = calloc(sizeof(char), 1024);
    sprintf(hashed_site,"%s",hashString(site, SHA512));
    base64encode(hashed_site,512, hashed_site,1024);
    char * encrypted_password = calloc(sizeof(char), 512);
    base64encode(encryptString(paddedpassword, 256, key, TWOFISH),256,encrypted_password, 512);
    
    Record* record = createRecord(encrypted_username, hashed_site, encrypted_password);
    saveRecord(fileName, record);
    
    free(encrypted_username);
    free(hashed_site);
    free(encrypted_password);
    free(record);
    free(paddedusername);
    free(paddedpassword);
   
}


Record* retrieveEncryptedRecord(const char* site, const char* fileName){
    char * hashed_site = calloc(sizeof(char), 1024);
    base64encode(hashString(site, SHA512),512, hashed_site,1024);
  
    Record* result = getRecordBySite(fileName, hashed_site);
    free(hashed_site);
    return result;
    
}

Record* decryptRecord(const Record* record, char* key){
    Record *result = calloc(sizeof(Record),1);
    unsigned char* decodedPassword = calloc(sizeof(unsigned char),256*2);
    unsigned char* decodedUsername = calloc(sizeof(unsigned char),256*2);
    unsigned char* decodedSite = calloc(sizeof(unsigned char),512*2);
    
    size_t* passwordSize =calloc(sizeof(size_t),1);
    size_t* usernameSize =calloc(sizeof(size_t),1);
    size_t* siteSize = calloc(sizeof(size_t),1);
    
    *passwordSize = 512;
    *usernameSize = 512; 
    *siteSize = 1024;
     
    
    base64decode(record->password, 512, decodedPassword, passwordSize);
    base64decode(record->username, 512, decodedUsername, usernameSize);
    base64decode(record->site, 1024, decodedSite, siteSize);
    
    result->password = decryptString(decodedPassword, 512, key, TWOFISH);
    result->username = decryptString(decodedUsername, 512, key, TWOFISH);
    result->site = decodedSite;
    
    free(decodedPassword);
    free(decodedUsername);
    
    free(passwordSize);
    free(usernameSize);
    free(siteSize);
    return result;

}