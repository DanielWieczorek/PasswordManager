
#ifndef CRYPTOGRAPHY_H
#define	CRYPTOGRAPHY_H
#include "dwilib.h"
#include <gcrypt.h> 


enum EncryptionAlgorithm {TWOFISH};
char* encryptString(const char* plainText, size_t plainTextLength, const char* key, const enum EncryptionAlgorithm algorithm);
char* decryptString(const char* cipherText, size_t cipherTextLength, const char* key, const enum EncryptionAlgorithm algorithm);
void initCryptographyModule(void);
void freeCryptographyModuleMemory(void);
#endif	/* CRYPTOGRAPHY_H */

