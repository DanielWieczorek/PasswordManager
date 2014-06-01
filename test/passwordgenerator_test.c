
#include <stdio.h>
#include <stdlib.h>
#include "../src/passwordgenerator.h"
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

void test_generate_base64_password () {
    char* password = generatePassword(12, BASE64);
    int i=0;
    for(i=0;i<getStringLength(password);i++)
        CU_ASSERT_TRUE(containsChar(base64,password[i]));
    printf("len: %d", getStringLength(password));
    CU_ASSERT_EQUAL(getStringLength(password),12);
        
}

void test_generate_base85_password () {
    char* password = generatePassword(12, BASE85);
    int i=0;
    for(i=0;i<getStringLength(password);i++)
        CU_ASSERT_TRUE(containsChar(base85,password[i]));
    
    CU_ASSERT_EQUAL(getStringLength(password),12);
}


int main() {
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("passwordgenerator_test", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error(); 
    }

    /* Add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "test_generate_base64_password", test_generate_base64_password)) ||
            (NULL == CU_add_test(pSuite, "test_generate_base85_password", test_generate_base85_password))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
