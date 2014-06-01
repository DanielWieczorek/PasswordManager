
#ifndef PASSWORDGENERATOR_H
#define	PASSWORDGENERATOR_H
#include "dwilib.h"
typedef enum {BASE64 = 0, BASE85 = 1 } characterSet;

extern char base85[85];
extern char base64[64];

char* generatePassword(size_t length, characterSet charset);

#endif	/* PASSWORDGENERATOR_H */

