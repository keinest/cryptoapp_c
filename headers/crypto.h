#ifndef __CRYPTO__H__
#define __CRYPTO__H__
#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>
#include <ncurses.h>
#include <signal.h>
#include <openssl/sha.h>



// [**************** BUFFER CONTRL *******************]

extern bool          veri_enter(char                               *);
extern int           convert_enter(char                            *);
extern void          anim(                                          );
extern void          ShowDescp(                                     );
extern void          ShowDescpTry(                                  );

// [****************************************************************]

extern long long int p,q,e,m;
long long int        power(     int  ,                 int          ); // POWER -----|-----------------------------------------|
extern int           pgcd(         int ,          int               ); // GCD -------|-----|                                   |
extern char          *Rsa(char * ,long long int ,long long int      ); // RSA -------------|-----------|                       |
extern void          RSA_Helpfr(                                    ); // RSA HELPfr ------------------|-----|                 |
extern void          RSA_Helpen(                                    ); // RSA HELPen ------------------------|-----|           |     
extern int           AFFINE(                                        ); // AFFINE ----------------------------------|-----|     |
extern void          helpFr(      char                             *); // AFFINE HELPfr ---------------------------------|-----|
extern void          helpEn(      char                             *); // AFFINE HELPeN ---------------------------------------|
extern char *cle;
extern void          CESAR(                                         );	// CESAR ----------------------------------------------|
extern char          *Vigenere(char             *,char             *); // VIGENERE --------------------------------------------|
extern int len,lenc;
extern char *msg;
extern char          *Vernam(char               *,char             *); // VERNAM -----|--------------------------|
extern void          HILL(                                          ); // HILL -------|--------------------|     |
extern char          *RecTranspos(char              *, char        *); // RECTANGULAR TRANSPOSITION -------|-----|
 

// [********************************* FEISTEL *********************************]

                // [******** START ********]

typedef struct Feistel
{
    int val;
    struct Feistel *next;
} Feistel;

extern Feistel       *pushInList(Feistel              *,         int ); // STACK ---------------|-----------------------------------------------------|
extern Feistel       *ConvertTobin(Feistel           *,          int ); // BINARY CONVERTER ----|-----|                                               |
extern int           ComputeLength(Feistel                          *); // LENGHT COMPUTER -----------|-----|                                         |
extern Feistel       *FeistelChif(Feistel       *, Feistel *, char  *); // FEISTEL ENCRYPTION --------------|-----|                                   |
extern Feistel       *CloneList(Feistel                             *); // MESSAGE CLONER ------------------------|-----|                             |
extern Feistel       *feistel(Feistel *, Feistel       *, char      *); // MAIN FUNCTION (FEISTEL) ---------------------|-----|                       |
extern void          Show(Feistel                                   *); // BINARY FORMAT -------------------------------------|-----|                 |
extern void          ShowF(Feistel                                  *); // STRING FORMAT -------------------------------------------|-----|           |
extern Feistel       *FreeKey(Feistel                               *); // FREE MEMORY ---------------------------------------------------|-----|     |
extern char          *ConvertToString(Feistel   *, char             *); // STRING CONVERTER ----------------------------------------------------|-----|

//[********************************* END *********************************]

#endif /* __CRYPYO__H__*/
