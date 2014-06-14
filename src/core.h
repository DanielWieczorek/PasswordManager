/* 
 * File:   core.h
 * Author: DWI1
 *
 * Created on 14. Juni 2014, 12:19
 */

#ifndef CORE_H
#define	CORE_H
#include "cryptography.h"
#include "persistence.h"
void writeEncryptedRecord(char* username, char* site, char* password, char* key, char* fileName);


#endif	/* CORE_H */

