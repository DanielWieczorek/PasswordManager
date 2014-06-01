/**
 * @file dwiio.h
 * @brief small module to make the io easier. This includes mainly file io but can also be reading and printing text from or to streams.
 */

#ifndef DWIIO_H_
#define DWIIO_H_
#include "dwilib.h"

void printBanner(void);
off_t getFileSize(const char *filename);
char* getAbsolutePath(const char* relativePath);
char* readFileAsStringFully(const char *filename);
char* readBytesFromFile(const char *filename, off_t bytes);
#endif /* DWIIO_H_ */