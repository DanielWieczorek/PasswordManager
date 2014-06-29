#include "persistence.h"
#include "dwilib.h"

const char* foo= "foobar";
const size_t MAX_LINE_LENGTH = 1024;
Record* convertStringToRecord(char* line);

Record* createRecord( char* username,  char* site,  char* password){
    Record* result = calloc(sizeof(Record),1);
    result->username = username;
    result->site = site;
    result->password = password;
    return result;
}

char* buildOutputString(const Record* input){
    return concatAll(6,input->username,":",input->site,":",input->password,"\n");
}

void saveRecord(const char* fileName, const Record* input){
    char* output = buildOutputString(input);
    writeStringToFile(fileName, output);
}

Record* getRecordBySite(const char* fileName, const char* siteName){
    Record* result = NULL;
    Record* temp = NULL;
    char* completeFile = readFileAsStringFully(fileName);
    char* ptr;
    char *end_str;
    ptr = strtok_r(completeFile, "\n",&end_str);
    
    while(ptr){
        temp = convertStringToRecord(ptr);
        if(temp->site && strcmp(temp->site, siteName)==0){
            result = temp;
            break;
        }
        
        ptr = strtok_r(NULL, "\n",&end_str);
        free(temp);
        
        
    }
    
    return result;
}

Record* convertStringToRecord(char* line){
    char* username = strtok(line, ":");
    char* site = strtok(NULL, ":");
    char* password = strtok(NULL, ":");
    
    return createRecord(username, site, password);
}

void deleteRecord(Record* input){
    nullString(input->password);
    nullString(input->site);
    nullString(input->username);
       
    free(input->password);
    free(input->site);
    free(input->username);
    free(input);
}