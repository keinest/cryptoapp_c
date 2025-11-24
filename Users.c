#include "headers/Users.h"

    //[************************ HOME PAGE ************************]
    
void Home()
{
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_RED, COLOR_BLACK);
    init_pair(5, COLOR_BLUE, COLOR_BLACK);

    attron(COLOR_PAIR(1) | A_BOLD);
    printw("\n\t\t\t\t\t***************************************************\n");
    printw("\t\t\t\t\t*        W E L C O M E T O O U R S Y S T E M      *\n");
    printw("\t\t\t\t\t***************************************************\n\n");
    attroff(COLOR_PAIR(1));
    
    attron(COLOR_PAIR(2));
    printw("\t\t\t\t\t\t01 ==> Try as Guest\n");
    attroff(COLOR_PAIR(2));
    
    attron(COLOR_PAIR(3));
    printw("\t\t\t\t\t\t02 ==> Sign In (Create an Account)\n");
    attroff(COLOR_PAIR(3));
    
    attron(COLOR_PAIR(5));
    printw("\t\t\t\t\t\t03 ==> Log In\n");
    attroff(COLOR_PAIR(5));

    attron(COLOR_PAIR(4));
    printw("\t\t\t\t\t\t00 ==> Exit System\n");
    attroff(COLOR_PAIR(4));
    printw("\n\t\t\t\t\t\tChoose an option: ");
    refresh();
}

    //[************************ HASH PASSWORD ************************]

void *hashPassword(unsigned char *password,char *hexHash)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(password, strlen((char *)password), hash);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
        sprintf(&hexHash[i * 2], "%02x", hash[i]);

    return hexHash;
}

    //[************************ CREATE AN ACCOUNT ************************]

ListUsers *AccountCreate(ListUsers *ls, Users User)
{
    ListUsers *c = (ListUsers *)malloc(sizeof(ListUsers));
    if (!c)
    {
        printw("Memory Allocation Error ! \n");
        return ls;
    }

    c -> val = User;
    c -> next = NULL;
    
    if (!ls) return c;
    
    ListUsers *temp = ls;
    while (temp -> next)
        temp = temp -> next;
    temp -> next = c;
    return ls;
}

//[************************ USER INFORMATIONS ************************]

void UsersInf(ListUsers **ls)
{
    Users User;
    char pass[100];
    char request[4] ,ch;
    int i = 0;
    
    printw("Enter Your Login > ");
    scanw("%99s", User.login);
    printw("Enter Your Email Address > ");
    scanw("%99s", User.email);

    while(MailVeri(User.email) != 0)
    {
        attron(A_BOLD);
        printw("This Is Not An Email Address\n\n");
        printw("Enter Your Email Address > ");
        scanw("%99s", User.email);
    }
    
    PassW:
    noecho();
    printw("Enter Your PassWord > ");       
    while ((ch = getch()) != '\n' && i < 99) 
    {
        if (ch == 127 || ch == 8) 
        {
            if (i > 0) 
            {
                --i;
                printw("\b \b");
            }
        } 

        else 
        {
            pass[i++] = ch;
            printw("*");
        }
    }

    pass[i] = '\0';
    echo();
    attron(A_BOLD);

    if(StrongPassWord((unsigned char *)pass) != 0)
    {
        printw("\n\nYour PassWord Is Not Strong :) Do You Want To Continue (Yes/No) : ");
        scanw("%4s",request);
        
        if(Request(request) != 0)
        {
            i = 0;
            goto PassW;
        }
    }

    printw("\nDo You Want To See Your PassWord (Yes/No) : ");
    scanw("%4s",request);
    
    if(Request(request) == 0)
    {
        printw("\nYour PassWord Is :==> %s\n",pass);
        printw("\nDo You Want To Modify Your PassWord (Yes/No) : ");
        scanw("%4s",request);
    
        if(Request(request) == 0)
        {
            i = 0;
            goto PassW;
        }
    }

    echo();
    char hex[65];

    strcpy(User.password,hashPassword((unsigned char *)pass,hex));
    *ls = AccountCreate(*ls, User);
    UserSavers(*ls);
}

    // [************************ AUTHENTIFICATION ************************]

int AuthCTion(ListUsers *ls)
{
    printw("\n\nPlease Connect To Your Account To Access To The System Fonctionnalities\n\n");
    char mail[100], pass[100],request[5], ch;
    int i = 0;
    printw("Enter Your Email Address > ");
    scanw("%99s", mail);

    while(MailVeri(mail) != 0)
    {
        printw("This Is Not An Email Address ! \n");
        printw("Enter Your Email Address > ");
        scanw("%99s", mail);
    }
    
    Pass:
    noecho();
    printw("Enter Your Authentification PassWord > ");

    while ((ch = getch()) != '\n' && i < 99) 
    {
        if (ch == 127 || ch == 8) 
        {
            if (i > 0) 
            {
                --i;
                printw("\b \b");
            }
        } 
        else 
        {
            pass[i++] = ch;
            printw("*");
        }
    }

    pass[i] = '\0';
    echo();
    printw("\nDo You Want To See Your Password (Yes/No) : ");
    scanw("%4s",request);

    if(Request(request) == 0)
    {
        printw("\nYour PassWord Is :==> %s\n",pass);
        printw("\nDo You Want To Modify Your PassWord (Yes/No) : ");
        scanw("%4s",request);

        if(Request(request) == 0)
        {
            i = 0;
            goto Pass;
        }
    }

    char hex[64];
    ListUsers *temp = ls;
    init_pair(1,COLOR_MAGENTA,COLOR_BLACK);
    init_pair(2,COLOR_GREEN,COLOR_BLACK);
    attron(COLOR_PAIR(2) | A_BOLD);
    printw("Reading data base.../");
    attroff(COLOR_PAIR(2));
    refresh();
    sleep(2);

    while(temp)
    {
        if(strcmp(temp -> val.email, mail) == 0 && strcmp(temp -> val.password,hashPassword((unsigned char *)pass,hex)) == 0)
        {
            attron(COLOR_PAIR(1) | A_BOLD);
            init_pair(2, COLOR_CYAN, COLOR_BLACK);
            printw("\n\nAuthentification Successfully !\n\n");
            attroff(COLOR_PAIR(1));
            ShowDescp();
            attron(COLOR_PAIR(1) | A_BOLD);
            printw("\n\t\t\t\t*******************************************************\n");
            printw("\t\t\t\t*\t\tWelcome :==> %s\t      *\n",temp -> val.login);
            printw("\t\t\t\t*******************************************************\n");
            attron(COLOR_PAIR(4));
            printw("\n\n\t\t\t\t\t\t\t<Enter>");
            getch();
            attroff(COLOR_PAIR(1) |COLOR_PAIR(4));
            refresh();

            return 0;
        }
        
        temp = temp -> next;
    }
    return 1;
}

//[************************ DATA BASE ************************]

void UserSavers(ListUsers *ls)
{
    FILE *fs = fopen("AuthOr", "w+");
    if(!fs)
    {
        printw("Enable To Update The Informations !\n");
        return;
    }

    while(ls)
    {
        fprintf(fs, "%s-%s-%s\n", ls -> val.login, ls -> val.email, ls -> val.password);
        ls = ls -> next;
    }
    fclose(fs);
}

//[************************ USERS UPDATE(FROM DATA BASE) ************************]

ListUsers *UpdateUsers()
{
    FILE *fs = fopen("AuthOr", "r");
    if (!fs)
    {
        printw("Data Base Error\n");
        return NULL;
    }

    ListUsers *ls = NULL;
    Users User;

    while(fscanf(fs, "%99[^-]-%99[^-]-%64s\n", User.login, User.email, User.password) == 3)
    {
        ls = AccountCreate(ls, User);
    }

    fclose(fs);
    
    return ls;
}

//[************************ FREE MEMORY ************************]

void freeList(ListUsers *ls)
{
    ListUsers *temp;
    while(ls)
    {
        temp = ls;
        ls = ls -> next;
        free(temp);
    }

    ls = NULL;
}

//[************************ VERIFICATION OF THE COMPATIBILITY OF THE EMAIL ADDRESS ************************]

int MailVeri(char *mail)
{
    int len = strlen(mail);
    
    if(len < 11)
        return 1;

    for(int i = 0; i < len - 10; i++)
    {
        if(mail[i] == '@' || (mail[i] >= 'A' && mail[i] <= 'Z'))
            return 1;
    }

    if(mail[len - 10] == '@' && mail[len - 9] == 'g' && mail[len - 8] == 'm' 
        && mail[len - 7] == 'a' && mail[len - 6] == 'i' && mail[len - 5] == 'l' 
        && mail[len - 4] == '.' && mail[len - 3] == 'c' && mail[len - 2] == 'o' 
        && mail[len - 1] == 'm')
        return 0;

    return 1;
}

    //[************************ REQUEST MANAGEMENT ************************]

int Request(char *request)
{
    if(request[0] == 'Y' || request[0] == 'y')
        return 0;

    return 1;
}

//[************************ PASSWORD VERIFICATION ************************]

int StrongPassWord(unsigned char *PassWord)
{
    int len = strlen((char *)PassWord);

    if(len < 8)
        return 1;
    
    int see = 0,i = 0;

    while(PassWord[i] != '\0')
    {
        if(PassWord[i] >= 'A' && PassWord[i] <= 'Z')
        {
            see = 1;
            break;
        }
        i++;
    }

    i = 0;
    int A = 0;
    
    while(PassWord[i] != '\0')
    {
        if((PassWord[i] >= ' ' && PassWord[i] <= ',') || (PassWord[i] >= ':' 
            && PassWord[i] <= '@') || (PassWord[i] >= '[' && PassWord[i] <= '`')
            || (PassWord[i] >= '{' && PassWord[i] <= '~')
          )
        {
            A = 1;
            break;
        }
        i++;
    }

    i = 0;
    int B = 0;
    
    while(PassWord[i] != '\0')
    {
        if((PassWord[i] >= '0' && PassWord[i] <= '9'))
        {
            B = 1;
            break;
        }

        i++;
    }

    if(see == 1 && A == 1 && B == 1)
        return 0;
    return 1;
}

// [################################ RESET PASSWORD SECTION ################################]

    //[************************ CODE GENERATION ************************]

int genPassWord()
{
    return rand () % 9;
}

    // [************************ CODE VERIFICATION ************************]

int cmpValue(int *p,int *c)
{
    for(int i = 0; i < 6; ++i)
    {
        if(p[i] != c[i])
            return 1;
    }

    return 0;
}

// [************************ END ************************]
