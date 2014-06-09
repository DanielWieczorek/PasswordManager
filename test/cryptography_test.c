/*
 * File:   cryptography_test.c
 * Author: Rhox
 *
 * Created on 04.06.2014, 21:08:36
 */

#include <stdio.h>
#include <stdlib.h>
#include "../src/cryptography.h"
#include <CUnit/Basic.h>

/*
 * CUnit Test Suite
 */

int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}

void test_twofish_decrypt_encrypt() {
    char *key = "ldlelslelslelslslflelslalelslssl";
    char *plainText = "ldlelslelslelslslflelslalelslsslldlelslelslelslslflelslalelslssl";
    enum EncryptionAlgorithm algorithm = TWOFISH;
    initCryptographyModule();
    int plainTextSize = getStringLength(plainText);
    char *cipherText = encryptString(plainText,plainTextSize, key, algorithm);
    char *plainText2 = decryptString(cipherText,plainTextSize, key, algorithm);
    CU_ASSERT_STRING_EQUAL(plainText, plainText2);
    freeCryptographyModuleMemory();
    free(cipherText);
    free(plainText2);
}


void test_twofish_decrypt_encrypt_null() {
    char *key = NULL;
    char *plainText = NULL;
    enum EncryptionAlgorithm algorithm = TWOFISH;
    initCryptographyModule();
    int plainTextSize = getStringLength(plainText);
    char *cipherText = encryptString(plainText,plainTextSize, key, algorithm);
    char *plainText2 = decryptString(cipherText,plainTextSize, key, algorithm);
    CU_ASSERT_EQUAL(plainText, NULL);
    CU_ASSERT_EQUAL(plainText2, NULL);
    freeCryptographyModuleMemory();
}

void test_sha256_normal() {
    char *text = "ldlelslelslelslslflelslalelslsslldlelslelslelslslflelslalelslssl";
    enum HashAlgorithm algorithm = SHA256;
    initCryptographyModule();
    char *hash = hashString(text, algorithm);
    CU_ASSERT_STRING_NOT_EQUAL(text, hash);
    freeCryptographyModuleMemory();
    free(hash);
}

void test_sha512_normal() {
    char *text = "ldlelslelslelslslflelslalelslsslldlelslelslelslslflelslalelslssl";
    enum HashAlgorithm algorithm = SHA512;
    initCryptographyModule();
    char *hash = hashString(text, algorithm);
    CU_ASSERT_STRING_NOT_EQUAL(text, hash);
    freeCryptographyModuleMemory();
    free(hash);
}

void test_sha512_null() {
    char *text = NULL;
    enum HashAlgorithm algorithm = SHA512;
    initCryptographyModule();
    char *hash = hashString(text, algorithm);
    CU_ASSERT_EQUAL(hash, NULL);
    freeCryptographyModuleMemory();
}




int main() {
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("cryptography_test", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "test_twofish_decrypt_encrypt", test_twofish_decrypt_encrypt)) ||
            (NULL == CU_add_test(pSuite, "test_twofish_decrypt_encrypt_null", test_twofish_decrypt_encrypt_null))||
            (NULL == CU_add_test(pSuite, "test_sha256_normal", test_sha256_normal))||
            (NULL == CU_add_test(pSuite, "test_sha512_normal", test_sha512_normal))||
            (NULL == CU_add_test(pSuite, "test_sha512_null", test_sha512_null))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
