#include"headers/decrypt.h"


    //[********************** ANIMATION **********************************]

void anim()
{
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    char stock[100] = "\n\n\n\n\n\n\t\t\t\t[********************* SoulKing The Geek GTS *********************]";
    int i = 0;
    while (stock[i] != '\0')
    {
        attron(COLOR_PAIR(1) | A_BOLD);
        printw("%c", stock[i]); 
        refresh();
        attroff(COLOR_PAIR(1));
        usleep(50000);
        ++i;
    }
    attron(A_BOLD | COLOR_PAIR(4));
    printw("\n\n\n\t\t\t\t\t\t\t\t<Enter>");
    getch();
    attroff(COLOR_PAIR(4));
    clear();
    refresh();
    attron(COLOR_PAIR(1) | A_BOLD);
    i = 0;
    char *system = "\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t[~~~~~~~~-> Encrytion and Decryption system <-~~~~~~~~]";
    while(system[i] != '\0')
    {
        printw("%c",system[i]);
        refresh();
        usleep(50000);
        i++;
    }
    attron(A_BOLD | COLOR_PAIR(4));
    printw("\n\n\n\t\t\t\t\t\t\t<Enter>");
    getch();
    attroff(COLOR_PAIR(4) | COLOR_PAIR(1));
    clear();
}
         //[********************* EUCLIDE EXTEND ALGORITHM *********************]

long long int EulcideEtendu(long long int a, long long int b, long long int *x, long long int *y)
{
    if(a == 0)
    {
        *x = 0;
        *y = 1;
        return b;
    }

    long long int x1, y1;
    long long int pgcd = EulcideEtendu(b % a, a, &x1, &y1);

    *x = y1 - (b / a) * x1;
    *y = x1;

    return pgcd;
}

    //[************************ RSA DECRYPTION ************************]

char *decryptRSA(char  *M,long long int phi,long long int e,long long int n)
{
    int len = strlen(M);
    long long int u = 0, v = 0,d = 0;
    if(EulcideEtendu(e,phi,&u,&v) == 0)
        return NULL;
    d = u;
    if(d < 0)
        d += phi;
    for(int  i = 0; i < len; ++i)
    {
        char base = (isupper(M[i])) ? 'A' : 'a';
        M[i] = (int)M[i];
        M[i] = power((int)M[i],d) % n;
        M[i] = (M[i] % 26) + (int)base;
        M[i] = (char)M[i];
    }

    return M;
}

		//[*********************** AFFINE DECRYPTION **************************]

char *decryptAFFINE(char *M,int k1,int k2)
{
    long long int u = 0, v = 0, d = 0;

    if(EulcideEtendu(k1,26,&u,&v) == 0)
        return NULL;
    d = u;
    if(d < 0)
        d = (d + 26) % 26;
    
    int len = strlen(M);
    for(int i = 0; i < len; ++i)
    {
        if((M[i] >= 'A' && M[i] <= 'Z') || (M[i] >= 'a' && M[i] <= 'z'))
            M[i] = d * (M[i] - k2) % 26;
    }

    return M;
}
		//[*********************** CESAR DECRYPTION **************************]

char *decryptCESAR(char *mess,char key) 
{
    char *cle = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *chif = (char*)malloc(5000*sizeof(char));
    int see = 0;
    int len = strlen(cle);
    
    for(int i = 0; i < len; ++i)
    {
        if(toupper(key) == cle[i])
        {
            ++see;
            break;
        }
    }

    if(see)
    {
        int i = 0;
        while(mess[i] != '\0')
        {
            if(isalpha(mess[i]))
            {
                char start = isupper(mess[i]) ? 'A' : 'a';
                char pos = (mess[i] - key) % 26;
                if(pos < 0)
                    pos = (pos + 26) % 26;
                chif[i] = start + pos;
            }
            else
                chif[i] = mess[i];
            ++i;
        }
    }
    return chif;
}

    //[******************************* VIGENERE DECRYPTION *************************]

char *decryVigenere(char *mess,char *key)
{
    int lenM = strlen(mess),lenk = strlen(key);
    char *chif = (char*)malloc((lenM + 1)*sizeof(char));
    
    for(int i = 0,j = 0; mess[i] != '\0'; ++i,++j)
    {
        if(j == lenk)
            j = 0;
        if(isalpha(mess[i]))
        {
            if(isalpha(mess[i]))
            {
                char start = (isalpha(mess[i])) ? 'A' : 'a';
                char pos = (mess[i] - key[j]) % 26;
                if(pos < 0)
                    pos = (pos + 26) % 26; 
                chif[i] = start + pos;
            }
        }
        else
            chif[i] = mess[i];   
    }
    chif[lenM] = '\0';
    
    return chif;
}
 
    //[********************** VERNAM(ONE-TIME-PAD) DECRYPTION **************************]

char *decryptVernam(char *mess, char *key)
{
    char *chif = (char*)malloc(5000 * sizeof(char));
    int i = 0;
    while(mess[i] != '\0' && key[i] != '\0')
    {
        if(isalpha(mess[i]))
        {
            char start = (isupper(mess[i])) ? 'A' : 'a';
            char pos = (mess[i] - key[i]) % 26;
            if(pos < 0)
                pos = (pos + 26) % 26;
            chif[i] = start + pos;
        }
        else
            chif[i] = mess[i];
        ++i;
    }
    chif[i] = '\0';

    return chif;
}

    //[******************* RECTANGULAR TRANSPOSITION DECRYPTION *******************]

void decryptRectangular(char *mess, char *key)
{
    int len = strlen(mess);
    int lenk = strlen(key);
    int rows = ceil((double)len / lenk);

    char mat[rows][lenk];
    int order[lenk];
    
    for(int i = 0; i < lenk; ++i)
        order[i] = i;

    int ind = 0;

    for(int i = 0; i < lenk; ++i)
        mat[0][i] = key[i];

    for(int i = 1; i < rows; ++i) 
    {
        for(int j = 0; j < lenk; ++j)
            mat[i][j] = (ind < len) ? mess[ind++] : 'X';
    }

    printw("\nMatrix Before Sort:\n");
    for(int i = 0; i < rows; ++i)
    {
        for(int j = 0; j < lenk; ++j)
            printw("%c ", mat[i][j]);
        printw("\n");
    }

    for(int i = 0; i < lenk - 1; ++i)
    {
        for(int j = i + 1; j < lenk; ++j) 
        {
            if(mat[0][i] > mat[0][j]) 
            {
                char temp = mat[0][i];
                mat[0][i] = mat[0][j];
                mat[0][j] = temp;

                int tempIndex = order[i];
                order[i] = order[j];
                order[j] = tempIndex;
            }
        }
    }

    printw("\nMatrix After Sort:\n");
    for(int i = 0; i < rows; ++i) 
    {
        for(int j = 0; j < lenk; ++j) 
            printw("%c ", mat[i][j]);
        printw("\n");
    }

    int index = 0;
    for(int i = 0; i < lenk; ++i) 
    {
        int col = order[i];
        for(int j = 0; j < rows; ++j)
        {
            if(index < len)
                mat[j][col] = mess[index];
            else
                mat[j][col] = 'X';
            ++index;
        }
    }

    printw("\nThe Decrypted Message Is: ");
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < lenk; ++j)
            printw("%c", mat[i][j]);        
    }
    printw("\n");
}

    // [************************* FEISTEL DECRYPTION ***********************************]

Feistel *Dfeistel(Feistel *mess, Feistel *key,char *op)
{
    if(!mess) return NULL;

    Feistel *Lblock = NULL,*Rblock = NULL,*cur = mess,*tail = NULL;

    int len = ComputeLength(mess);
    int mid = len / 2;

    for(int i = 0; i < mid; ++i)
    {
        Feistel *tmp = (Feistel *)malloc(sizeof(Feistel));
        tmp -> val = cur -> val;
        tmp -> next = NULL;
        if (!Lblock) Lblock = tail = tmp;
        else
        {
            tail -> next = tmp; 
            tail = tmp;
        }
        cur  = cur -> next;
    }

    tail = NULL;

    for(int i = mid; i < len; ++i)
    {
        Feistel *tmp = (Feistel *)malloc(sizeof(Feistel));
        tmp -> val = cur -> val;
        tmp -> next = NULL;
        if(!Rblock) Rblock = tail = tmp;

        else
        {
            tail -> next = tmp;
            tail = tmp;
        } 
        cur = cur ->next;
    }

    int lenL = ComputeLength(Lblock),lenR = ComputeLength(Rblock),lenK = ComputeLength(key);

    while(lenL < lenK)
    {
        Lblock = pushInList(Lblock,0);
        ++lenL;
    }

    while(lenK < lenL)
    {
        key = pushInList(key,0);
        ++lenK;
    }

    while(lenR < lenK)
    {
        Rblock = pushInList(Rblock,0);
        ++lenK;
    }

    Feistel *tempR = CloneList(Rblock);
    FeistelChif(tempR, Lblock, op);
    char inter[100];
    printw("Enter The Intermediate Operator > ");
    scanw(" %99[^\n]", inter);
    FeistelChif(tempR, Lblock, inter);

    Feistel *feistelDechiff = tempR;
    Feistel *tailChiff = feistelDechiff;
    while(tailChiff -> next) 
        tailChiff = tailChiff -> next;
    tailChiff -> next = Lblock;

    return feistelDechiff;
    
}

//[************************ END ************************]