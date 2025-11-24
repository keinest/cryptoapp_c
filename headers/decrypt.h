#ifndef __DECRYPT__H__
#define __DECRYPT__H__

#include "crypto.h"

// [*************************** DECRYPTION MANAGMENT ***************************]

extern long long int EulcideEtendu(long long,long long,long long*,long long *); // EXTEND EUCLIDE ALGORITHM ----|--------------------|
extern char *decryptRSA(char * , long long,    long long,long long           ); // RSA -------------------------|--------|           |
extern char  *decryptAFFINE(char * , int  ,   int                            ); // AFFINE -------------------------------|-----------|
extern int decrytHILL(          int     **,      int                       **); // HILL ---------------------------------------------|
             
extern char *decryptCESAR(char  * ,    char                                  ); // CESAR -------------------|--------------------------------|
extern char *decryVigenere(char * ,    char                                 *); // VIGENERE ----------------|----------|                     |
extern char *decryptVernam(char * ,    char                                 *); // VERNAM -----------------------------|----------|          |   
extern void  decryptRectangular(char *,char                                 *); // RECTANGULAR TRANSPOSITION ---------------------|----------|
extern Feistel *Dfeistel(Feistel *, Feistel  *,char                         *); // FEISTEL --------------------------------------------------|

#endif /* __DECRYPT__H__ */