/*
 * File:   newcunittest.c
 * Author: DWI1
 *
 * Created on 22.06.2014, 11:28:58
 */

#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include "../src/core.h"

/*
 * CUnit Test Suite
 */

int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}

void test_writeEncryptedRecord_positive() {
    char *desiredResult = "eA0vGQoYPiYInMAIA79ug9cH9PK1feeqRNrXoOVGEfwbMnqWHWQfVTdRCH4Vz7jz9eFcruXKfjgSlj+8EdrzUOlVis204lTpUnel+gqLKmiaYyX1zyXYxyiH9dST74TdWlJAEgAWGRa5v4ySz1/Tor9WCaRuJf74AUsjkdnvKv/2WNclQAzIqoaeJq696uKdH3SIkclgyiAxsmmBvsQq2DY7HdZCZVWJY1e6Gd/1FEXGr3lwpyf84APPCVVmnYsmcB0kf9foSO9c4h7EMo/l9vzrJOoGXnvCDPXtUCHLNg7qRs8IsZL3MWRTLf8Ah8JdlfSbqA6agJ5mj0nn/fzSIQ==:2CxOTyYcWWOqV09xVjA5eFZqQTVlRlpxUVRWbFJscHhVVlJXYkZKc2NIaFZWbEpYWWtaS2MyTklhRlpXYkVwWVdXdGFTMk15VGtsaFJscFhZa1Z3V1ZkWGRHRlRNazE1Vkd0c2FGSnNjRmhaYTFaM1YxWmtXR1JIUmxSTmF6RTFWa2QwYzJGR1NuTmpSbWhhWVRGYU0xWXhXbXRYUjFKSVVteFNUbUY2UlRGV2EyUXdZekpHUjFOdVRtcFNiV2hoV1ZSR1lVMHhXWGhYYlhSWVVqRktTVlZ0ZUZOVWJVWTJVbFJHVjJFeVVYZFpla3BIVWpGT2RWUnRjRk5pVjJob1YxWlNSMWxWTUhoWFdHaFlZbGhTV1ZWcVJrdFRWbFowWlVaT1ZXSlZXVEpWYkZKSFZqSkZlVlZZWkZwbGEzQklWV3BHVDJSV1VuUmpSazVwVmpKb2IxWXhXbE5TTVd4V1RVaG9XRmRIYUZsWmJHaFRWMVpXY1ZKcmRGUldiRm93V2xWYVQxWlhTbFpYVkVwV1lrWktTRlpxU2tabFZsWlpXa1p3YkdFelFrbFdWM0JIVkRKU1YxVnVVbXBTYXpWd1ZtcEtiMkl4V1hoWGJFNVRUVmQ0VjFSVmFHOVhSbVJJWVVac1dtSkhhRlJXTVZwWFkxWktjbVJHVWxkaVJtOTM=:yqMq32HX/UWIhiX8JxN8L0MZ4OdPYOkX+OcnvfwkbEtFjKrc2wr9k1WnxLQkSUNh6XNVSM0RL9we7zOiMKlXwjG2AmgU+9LoV+MiXKXnxpi0+VCvY5ciXgzrgitJ64rjojEUVuAzQ4i0SATLa/6uhRT4DEaM5MUauWxvF2z0UsgJv+RBYGVjQn8i2ubUc6aTNVTX4AM0gMY4wRBPK/DxAIhgQDuJWTli91+O6VIxTQklefHDtYqFJGQQeN8fUL9AFYq1/nbEMtAkr76hToMNRg+1IYhZL26K6x3iHkJ00aJh/fRpQBACJnw89geJeMnBptryhIVnXnnr8MbqqKdEmg==";
    initCryptographyModule();
    writeEncryptedRecord("foo", "bar", "foobar", hashString("my secret key", SHA256), "./foo");
    freeCryptographyModuleMemory();
    char* fileContent=readFileAsStringFully("./foo");
    CU_ASSERT_STRING_EQUAL(desiredResult, fileContent);
    free(fileContent);
}

int main() {
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("newcunittest", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "test_writeEncryptedRecord_positive", test_writeEncryptedRecord_positive)) ) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
