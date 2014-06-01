
#include "passwordgenerator.h"

extern char base64[64]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
'0','1','2','3','4','5','6','7','8','9','+','/'};
extern char base85[85]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
'0','1','2','3','4','5','6','7','8','9','!','#','$','%','&','(',')','*','+','-',';','<','=','>','?','@','^','_','{','}','|','~'};

char* characterSetDefinitions[2]={base64,base85};


char* generatePassword(size_t length, characterSet charset){
    char* password = NULL;
        password = calloc(length, sizeof(char));
        int i=0;
        uint32_t index=0;
        uint32_t temp=0;
        for(i=0;i<length;i++){
            temp = getRandomUint32();
            char* characterPool = characterSetDefinitions[charset];
            index = temp%(getStringLength(characterPool)/sizeof(char));
            password[i] = characterPool[index];
        }
    return password;
}