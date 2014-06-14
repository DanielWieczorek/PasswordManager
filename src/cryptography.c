#include "cryptography.h"

char* encryptionAlgorithmMap[] = {"Twofish"};
char* hashAlgorithmMap[] = {"SHA256", "SHA512"};
char initVector[16] = {"0x34"};
enum CipherDirection {ENCRYPT, DECRYPT};
gcry_error_t (*cipherDirections[2])()={gcry_cipher_encrypt,gcry_cipher_decrypt};

char* executeCryptoFunction(const char* inputText, size_t inputTextLength, const char* key, const enum EncryptionAlgorithm algorithm, const enum CipherDirection);
gcry_cipher_hd_t initCipherDescriptor(const enum EncryptionAlgorithm algorithm, const char* key, size_t inputTextLength) ;
void initCryptographyModule(void);

void initCryptographyModule(void) {
    gcry_control(GCRYCTL_SUSPEND_SECMEM_WARN);
    gcry_control(GCRYCTL_INIT_SECMEM, 16384, 0);
    gcry_control(GCRYCTL_RESUME_SECMEM_WARN);
    gcry_control(GCRYCTL_INITIALIZATION_FINISHED, 0);

}

gcry_cipher_hd_t initCipherDescriptor(const enum EncryptionAlgorithm algorithm, const char* key, size_t inputTextLength) {
    gcry_cipher_hd_t hd = NULL;
    if (key) {
        int algorithmID = gcry_cipher_map_name(encryptionAlgorithmMap[algorithm]);
        size_t blkLength = gcry_cipher_get_algo_blklen(algorithmID);
        size_t keyLength = gcry_cipher_get_algo_keylen(algorithmID);
        if(keyLength == getStringLength(key) && inputTextLength%blkLength == 0){
            gcry_cipher_open(&hd, algorithmID, GCRY_CIPHER_MODE_CBC, GCRY_MD_FLAG_SECURE);
            gcry_cipher_setkey(hd, key, keyLength);
            gcry_cipher_setiv(hd, initVector, blkLength);
        }
    }
    return hd;
}

char* encryptString(const char* plainText, size_t plainTextLength, const char* key, const enum EncryptionAlgorithm algorithm) {
    return executeCryptoFunction(plainText, plainTextLength, key, algorithm, ENCRYPT);
}

char* decryptString(const char* cipherText, size_t cipherTextLength, const char* key, const enum EncryptionAlgorithm algorithm) {
    return executeCryptoFunction(cipherText, cipherTextLength, key, algorithm, DECRYPT);
}

char* hashString(const char* text, const enum HashAlgorithm algorithm) {
    char* buffer = NULL;
    if (text) {
        int algorithmID = gcry_md_map_name(hashAlgorithmMap[algorithm]);
        size_t digestLength = gcry_md_get_algo_dlen(algorithmID);
        buffer = calloc(digestLength + 1, sizeof (char));
        gcry_md_hash_buffer(algorithmID, buffer, text, getStringLength(text));
    }
    return buffer;

}

char* executeCryptoFunction(const char* inputText, size_t inputTextLength, const char* key, const enum EncryptionAlgorithm algorithm, const enum CipherDirection direction) {
    char* result = NULL;
    if (key && inputText) {
        gcry_cipher_hd_t hd = initCipherDescriptor(algorithm, key, inputTextLength);
        if (hd) {
  
            result = calloc(inputTextLength+1, sizeof (char));
            (*cipherDirections[direction])(hd, result, inputTextLength,  inputText, inputTextLength);
            gcry_cipher_close(hd);
        }
    }
    return result;
}

void freeCryptographyModuleMemory(void) {
    gcry_control(GCRYCTL_TERM_SECMEM);
}