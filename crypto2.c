#include "headers/crypto.h"


//[################################ FEISTEL ################################]

    //[********************** PUSH BYTE IN LIST HEAD **********************]

Feistel *pushInList(Feistel *node, int el)
{
    Feistel *c = (Feistel *)malloc(sizeof(Feistel));
    if (!c) return node;

    c -> val = el;
    c -> next = node;
    return c;
}

    //[********************** CONVERT ANY CHARACTER OF MESSAGE TO BINARY (8 BYTES) **********************]

Feistel *ConvertTobin(Feistel *node, int el)
{
    int tab[8] = {0},len = 0;

    while(el > 0)
    {
        int r = el % 2;
        tab[len++] = r;
        el /= 2;
    }

    for(int i = 0; i < 7; ++i)
        node = pushInList(node,tab[i]);

    return node;
}

    //[********************** COMPUTE THE BLOCK AND THE KEY LENGTH **********************]

int ComputeLength(Feistel *node)
{
    int len = 0;
    while (node)
    {
        ++len;
        node = node -> next;
    }
    return len;
}

    //[********************** LOGIQUES OPERATIONS BETWEEN KEY AND BLOCKS **********************]

Feistel *FeistelChif(Feistel *block, Feistel *block1, char *op)
{
    Feistel *ptr1 = block;
    Feistel *ptr2 = block1;
    switch (op[0])
    {
        case 'o':
        case 'O':
        {    while (ptr1 && ptr2)
            {
                ptr1 -> val |= ptr2 -> val;
                ptr1 = ptr1 -> next;
                ptr2 = ptr2 -> next;
            }
        }
        break;
        case 'a':
        case 'A':
        {
            while(ptr1 && ptr2)
            {
                ptr1 -> val &= ptr2 -> val;
                ptr1 = ptr1 -> next;
                ptr2 = ptr2 -> next;
            }
        }
        break;
        case 'x':
        case 'X':
        {
            while(ptr1 && ptr2)
            {
                ptr1 -> val ^= ptr2 -> val;
                ptr1 = ptr1 -> next;
                ptr2 = ptr2 -> next;
            }
        }
        break;
        case 'c':
        case 'C':
        {
            while(ptr1 && ptr2)
            {
                ptr1 -> val |= (~ptr2 -> val);
                ptr1 = ptr1 -> next;
                ptr2 = ptr2 -> next;
            }
        }
        break;
        default:
            printw("Can't found this operator :) !\n\n");
        break;
    }

    return block;
}

    //[********************** CLONE THE LIST **********************]

Feistel *CloneList(Feistel *node)
{
    if(!node) return NULL;
    Feistel *newList = NULL, *tail = NULL;
    while(node)
    {
        Feistel *newNode = (Feistel *)malloc(sizeof(Feistel));
        newNode -> val = node -> val;
        newNode -> next = NULL;
        if(!newList) newList = tail = newNode;
        else 
        { 
            tail -> next = newNode;
            tail = newNode; 
        }
        node = node -> next;
    }
    return newList;
}

    //[********************** VERICATION OF KEY AND BLOCK AND ENCRYPTION **********************]

Feistel *feistel(Feistel *mess, Feistel *key, char *op)
{
    int totalLen = ComputeLength(mess);
    int mid = totalLen / 2;

    Feistel *Lblock = NULL, *Rblock = NULL, *cur = mess, *tail = NULL;

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

        cur = cur -> next;
    }

    tail = NULL;
    for (int i = mid; i < totalLen; ++i)
    {
        Feistel *tmp = (Feistel *)malloc(sizeof(Feistel));
        tmp -> val = cur -> val;
        tmp -> next = NULL;

        if (!Rblock) Rblock = tail = tmp;
        else 
        { 
            tail -> next = tmp; 
            tail = tmp;
        }
        cur = cur -> next;
    }

    int lenL = ComputeLength(Lblock);
    int lenR = ComputeLength(Rblock);
    int lenK = ComputeLength(key);

    while(lenL < lenK)
    {
        Lblock = pushInList(Lblock, 0);
        lenL++; 
    }

    while(lenK < lenL)
    { 
        key = pushInList(key, 0); 
        lenK++; 
    }

    while(lenR < lenK)
    {
        Rblock = pushInList(Rblock, 0); 
        lenR++; 
    }

    Feistel *tempR = CloneList(Rblock);
    FeistelChif(tempR, Lblock, op);

    char inter[100];
    printw("Enter The Intermediate Operator > ");
    scanw(" %99[^\n]", inter);
    FeistelChif(tempR, Lblock, inter);

    Feistel *feistelChiff = tempR;
    Feistel *tailChiff = feistelChiff;
    
    while(tailChiff -> next) 
        tailChiff = tailChiff -> next;
    tailChiff -> next = Lblock;

    return feistelChiff;
}

    //[********************** PRINT MESSAGE AND KEY **********************]

void Show(Feistel *node)
{
    if (!node)
    {
        printw("The list is empty !\n\n");
        return;
    }
    while(node)
    {
        printw("%d ", node -> val);
        node = node -> next;
        usleep(10000);
        fflush(stdout);
        refresh();
    }
    printw(" -> NULL\n\n");
    refresh();
}

//[********************** PRINT ENCRYPTED MESSAGE **********************]

void ShowF(Feistel *node)
{
    if (!node)
    {
        printw("The list is empty !\n\n");
        return;
    }
    attron(COLOR_PAIR(3) | A_BOLD);
    while (node)
    {
        printw("%d ", node -> val);
        node = node -> next;
        usleep(10009);
        fflush(stdout);
        refresh();
    }
    printw(" -> NULL\n\n");
    attroff(COLOR_PAIR(3));
    refresh();
}

//[********************** CONVERT THE BINARY MESSAGE TO STRING **********************]

char *ConvertToString(Feistel *node, char *mess)
{
    if(!node) return NULL;
    int len = 0,val = 0,k = 0,i = 0;
    while(node)
    {
        if(len == 8)
        {
            mess[k++] = (char)val;
            val = 0;
            len = 0;
            i = 0;
        }
        if(len < 8 && !node -> next)
        {
            mess[k++] = (char)val;
            break;
        }
        val += node -> val * power(2,i);
        len++;
        node = node -> next;
    }
    mess[k] = '\0';
    return mess;
}

//[********************** FREE MEMORY **********************]

Feistel *FreeKey(Feistel *key)
{
    if(!key) return NULL;
    Feistel *temp = key;
    while(key)
    {
        temp = key;
        key = key -> next;
        free(temp);
    }
    return NULL;
}

//[************************ END ************************]