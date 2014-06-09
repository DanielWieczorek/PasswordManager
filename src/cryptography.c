#include "cryptography.h"

char* encryptionAlgorithmMap[] = {"Twofish"};
char* hashAlgorithmMap[] = {"SHA256", "SHA512"};
char initVector[16] = {"0x34"};

gcry_cipher_hd_t initCipherDescriptor(const enum EncryptionAlgorithm algorithm, const char* key);
void initCryptographyModule(void);

void initCryptographyModule(void) {
    gcry_control(GCRYCTL_SUSPEND_SECMEM_WARN);
    gcry_control(GCRYCTL_INIT_SECMEM, 16384, 0);
    gcry_control(GCRYCTL_RESUME_SECMEM_WARN);
    gcry_control(GCRYCTL_INITIALIZATION_FINISHED, 0);

}

gcry_cipher_hd_t initCipherDescriptor(const enum EncryptionAlgorithm algorithm, const char* key) {
    gcry_cipher_hd_t hd;
    if (key) {
        int algorithmID = gcry_cipher_map_name(encryptionAlgorithmMap[algorithm]);
        
        size_t blkLength = gcry_cipher_get_algo_blklen(algorithmID);
        size_t keyLength = gcry_cipher_get_algo_keylen(algorithmID);
        gcry_cipher_open(&hd, algorithmID, GCRY_CIPHER_MODE_CBC, GCRY_MD_FLAG_SECURE);
        gcry_cipher_setkey(hd, key, keyLength);
        gcry_cipher_setiv(hd, initVector, blkLength);
    }
    return hd;
}

char* encryptString(const char* plainText, size_t plainTextLength, const char* key, const enum EncryptionAlgorithm algorithm) {
    char* result = NULL;
    if (key && plainText) {
        result = calloc(plainTextLength, sizeof (char));
        gcry_cipher_hd_t hd = initCipherDescriptor(algorithm, key);
        if (hd) {
            gcry_cipher_encrypt(hd, result, plainTextLength, plainText, plainTextLength);
            gcry_cipher_close(hd);
        }
    }
    return result;
}

char* decryptString(const char* cipherText, size_t cipherTextLength, const char* key, const enum EncryptionAlgorithm algorithm) {
    char* result = NULL;
    if (key && cipherText) {
        result = calloc(cipherTextLength, sizeof (char));
        gcry_cipher_hd_t hd = initCipherDescriptor(algorithm, key);
        if (hd) {
            gcry_cipher_decrypt(hd, result, cipherTextLength, cipherText, cipherTextLength);
            gcry_cipher_close(hd);
        }
    }
    return result;
}

char* hashString(const char* text, const enum HashAlgorithm algorithm){
    int algorithmID = gcry_md_map_name(hashAlgorithmMap[algorithm]);
    size_t digestLength = gcry_md_get_algo_dlen(algorithmID); 
    char* buffer = calloc(digestLength+1,sizeof(char));
    gcry_md_hash_buffer(algorithmID,buffer,text, getStringLength(text));
    return buffer;
    
}



void freeCryptographyModuleMemory(void) {
    gcry_control(GCRYCTL_TERM_SECMEM);
}