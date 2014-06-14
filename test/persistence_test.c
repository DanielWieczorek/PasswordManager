/*
 * File:   persistence_test.c
 * Author: DWI1
 *
 * Created on 14.06.2014, 12:28:05
 */
#include "../src/persistence.h"
#include <stdio.h>
#include <stdlib.h>

#include <CUnit/Basic.h>

/*
 * CUnit Test Suite
 */
char *fileName = "./foo";

int init_suite(void) {
    return 0;
    
}

int clean_suite(void) {
    remove(fileName);
    return 0;
}

void test_write_read_right_format() {
    char username[]= "username";
    char site[]= "google.com";
    char password[]= "wtf123";
    Record* input = createRecord(username, site, password);
    Record* output = NULL;
    saveRecord(fileName, input);
    
    output = getRecordBySite(fileName,"google.com");
    
    CU_ASSERT_STRING_EQUAL(input->username,output->username);
    CU_ASSERT_STRING_EQUAL(input->site,output->site);
    CU_ASSERT_STRING_EQUAL(input->password,output->password);
//    deleteRecord(input);
    //deleteRecord(output);
}

void test_create_record() {
    Record* record = createRecord("username", "site", "password");
    CU_ASSERT_STRING_EQUAL(record->username,"username");
    CU_ASSERT_STRING_EQUAL(record->site,"site");
    CU_ASSERT_STRING_EQUAL(record->password,"password");
}

int main() {
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("persistence_test", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "test_write_read_right_format", test_write_read_right_format)) ||
            (NULL == CU_add_test(pSuite, "test_create_record", test_create_record))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
