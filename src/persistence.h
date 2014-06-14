/* 
 * File:   persistence.h
 * Author: DWI1
 *
 * Created on 14. Juni 2014, 12:57
 */

#ifndef PERSISTENCE_H
#define	PERSISTENCE_H


typedef struct 
{
    char* username;
    char* site;
    char* password;
    
}Record;

Record* createRecord( char* username,  char* site,  char* password);

void saveRecord(const char* fileName, const Record* input);

Record* getRecordBySite(const char* fileName, const char* siteName);

void deleteRecord(Record* input);

#endif	/* PERSISTENCE_H */

