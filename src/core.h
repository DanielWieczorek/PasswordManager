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
static const char* CREDENTIAL_SITE = "PasswordManagerSiteForCredentials";

void writeEncryptedRecord(const char* username, const char* site, const char* password, const char* key, const char* fileName);
Record* retrieveEncryptedRecord(const char* site, const char* fileName);

Record* decryptRecord(const Record* record, char* key);

bool doesCredentialEntryExist(const char* fileName);
bool checkCredentials(const char* password, const char* fileName);


#endif	/* CORE_H */

