/**
 * @file dwistring.h
 * @brief small module to make the string operations easier.
 */
#ifndef DWI_STRING_H_
#define DWI_STRING_H_
#include "dwilib.h"

char* concatAll(const uint32_t num, ...);
char* concat(const char* first, const char* second);
size_t getStringLength(const char* string);
#endif /* DWI_STRING_H_ */
