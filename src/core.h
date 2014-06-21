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
#include "base64.h"
void writeEncryptedRecord(char* username, char* site, char* password, char* key, char* fileName);
Record* retrieveEncryptedRecord(char* site, char* fileName);

Record* decryptRecord(Record* record, char* key);



#endif	/* CORE_H */

