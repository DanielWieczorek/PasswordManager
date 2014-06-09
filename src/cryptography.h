
#ifndef CRYPTOGRAPHY_H
#define	CRYPTOGRAPHY_H
#include "dwilib.h"
#include <gcrypt.h> 


enum EncryptionAlgorithm {TWOFISH};
enum HashAlgorithm {SHA256, SHA512};
char* encryptString(const char* plainText, size_t plainTextLength, const char* key, const enum EncryptionAlgorithm algorithm);
char* decryptString(const char* cipherText, size_t cipherTextLength, const char* key, const enum EncryptionAlgorithm algorithm);

char* hashString(const char* text, const enum HashAlgorithm algorithm);

void initCryptographyModule(void);
void freeCryptographyModuleMemory(void);
#endif	/* CRYPTOGRAPHY_H */

