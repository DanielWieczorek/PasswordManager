/* 
 * File:   base64.h
 * Author: DWI1
 *
 * Created on 21. Juni 2014, 15:51
 */

#ifndef BASE64_H
#define	BASE64_H



int base64decode (char *in, size_t inLen, unsigned char *out, size_t *outLen);
int base64encode(const void* data_buf, size_t dataLength, char* result, size_t resultSize);

#endif	/* BASE64_H */

