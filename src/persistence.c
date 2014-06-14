#include "persistence.h"
#include "dwistring.h"
const char* foo= "foobar";
const size_t MAX_LINE_LENGTH = 1024;
Record* convertStringToRecord(char* line);

Record* createRecord( char* username,  char* site,  char* password){
    Record* result = calloc(1,sizeof(Record));
    result->username = username;
    result->site = site;
    result->password = password;
    return result;
}

char* buildOutputString(const Record* input){
    return concatAll(5,input->username,":",input->site,":",input->password);
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
    ptr = strtok(completeFile, "\n");
    
    while(ptr){
        temp = convertStringToRecord(ptr);
        if(strcmp(temp->site, siteName)==0){
            result = temp;
            break;
        }
        ptr = strtok(NULL, "\n");
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