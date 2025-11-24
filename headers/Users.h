#ifndef ___USERS__H__
#define ___USERS__H__
#include "crypto.h"

typedef struct Users
{
    char login[100];
    char email[100];
    char password[100];
}Users;

typedef struct ListUsers 
{
    Users val;
    struct ListUsers *next;
}ListUsers;

extern void Home();

extern void *hashPassword(unsigned char *,char   *);
extern ListUsers *AccountCreate(ListUsers *, Users);
extern void UsersInf(ListUsers                  **);
extern int AuthCTion(ListUsers                   *);
extern void UserSavers(ListUsers                 *);
extern ListUsers *UpdateUsers(                    );
extern void freeList(ListUsers                   *);
extern int MailVeri(char                         *);
extern int Request(char                          *);
extern int StrongPassWord(unsigned char          *);
extern int genPassWord(                           );
extern int cmpValue(int         *,int            *);

#endif
