#include "headers/crypto.h"


	//[*********************** VIGENERE *************************]

char *Vigenere(char *msg,char *cle)
{
    printw("Enter The Message To Be Encrypted > ");
    scanw(" %[^\n]",msg);
    try:
    printw("Enter The Encryption Key > ");
    scanw(" %[^\n]",cle);
	int lenm = strlen(msg);
	int lenc = strlen(cle);
    
	if(lenm < lenc)
	{
        printw("This Key Isn't Valid For This Encryption!\n");
        goto try;
    }

	char *chif = (char*)malloc((lenm +1)*sizeof(char));
	if(chif == NULL)
	{
		printw("Memory Allocation Error!\n");
		exit(1);
	}

	for(int i = 0, j = 0; msg[i] != '\0'; ++i,++j)
	{
	    if(j == lenc)
            j = 0;
		if(isalpha(msg[i]))
		{
			char start = isupper(msg[i]) ? 'A' : 'a';
			chif[i] = start + (msg[i] + cle[j]) % 26;
		}
		else
			chif[i] = msg[i];
	}
	
	chif[lenm] = '\0';
    printw("In Process Of Encryption.../\n");
	napms(2000);
	fflush(stdout);
    printw("The Encrypted Message Of %s Is %s\n",msg,chif);
    free(chif);
	return chif;
}

	//[*********************** VERNAM **************************]

char *Vernam(char *msg,char *cle)
{
    printw("Enter The Message To Be Encrypted > ");
	scanw(" %[^\n]",msg);
    blade:
	printw("Enter The Encryption Key > ");
	scanw(" %[^\n]",cle);
	char *chif = (char*)malloc(5000 * sizeof(char));
    
	if(strlen(msg) != strlen(cle))
	{
        printw("This Isn't Valide!\nIl doit y avoir un ou plusieurs caracteres en plus ou en moins\n\n");
        goto blade;
    }
	int i = 0;
    while(msg[i] != '\0' && cle[i] != '\0')
	{
		if(isalpha(msg[i]))
		{
			char start = isupper(cle[i]) ? 'A' : 'a';
			chif[i] = start + (msg[i] + cle[i]) % 26;
		}
		else
			chif[i] = msg[i];
		++i;
    }
    chif[i] = '\0';
    printw("In Process Of Encryption.../\n");
    printw("The Encrypted Message Of %s  Is %s\n",msg,chif);
	free(chif);
    return chif;
}

	//[*********************** HILL **************************]

void HILL()
{
    int lgnm,colm,lgnk,colk;
    char test[500];
	Retry :
	printw("\n\t\t\t\nHILL Encryption System :) \n\n");
	attron(A_BOLD);
	printw("Enter The Number Of Rows Of Your Message Matrix > ");
	scanw(" %[^\n]",test);
	while(!veri_enter(test))
	{
		attron(COLOR_PAIR(4));
		printw("Typing Error : \n\t\t\t<Enter>");
		getch();
		clear();
		ShowDescp();
		printw("\n\t\t\t\nHILL Encryption System :) \n\n");
		printw("Enter The Number Of Rows Of Your Message Matrix > ");
		scanw(" %[^\n]",test);
		refresh();	
	}
	lgnm = convert_enter(test);

	printw("Enter The Number Of Colunms Of Your Message Matrix > ");
	scanw(" %[^\n]",test);

	while(!veri_enter(test))
	{
		attron(COLOR_PAIR(4));
		printw("Typing Error : \n\t\t\t<Enter>");
		attroff(COLOR_PAIR(4));
		getch();
		clear();
		ShowDescp();
		printw("\n\t\t\t\nHILL Encryption System :) \n\n");
		printw("Enter The Number Of Colunms Of Your Message Matrix > ");
		scanw(" %[^\n]",test);
		refresh();
	}
	colm = convert_enter(test);

	int mat[lgnm][colm];

	for(int i = 0; i < lgnm; i++)
	{
		for(int  j = 0; j < colm; j++)
		{
			Bim :
			printw("Enter The Element [%d][%d] > ",i + 1,j + 1);
			scanw(" %[^\n]",test);
			while(!veri_enter(test))
			{
				attron(COLOR_PAIR(4));
				printw("Typing Error : \n\t\t\t<Enter>");
				attroff(COLOR_PAIR(4));
				getch();
				clear();
				ShowDescp();
				printw("\n\t\t\t\nHILL Encryption System :) \n\n");
				printw("Enter The Element [%d][%d] > ",i + 1,j + 1);
				scanw(" %[^\n]",test);
				refresh();
			}
			mat[i][j] = convert_enter(test);
			if(mat[i][j] < 0 || mat[i][j] > 25)
			{
				attron(A_BOLD);
				printw("The Value Can't Excess 25. Make Sure Your Value Is In [0 - 25], The Retry\n");
				getch();
				refresh();
				goto Bim;
			}
		}
	}

	ShowDescp();
	printw("\n\t\t\t\nHILL Encryption System :) \n\n");
	printw("\nYour Message Is :\n\n");
	for(int i = 0; i < lgnm; i++)
	{
		for(int j = 0; j < colm; j++)
			printw("%d  ",mat[i][j]);
		printw("\n");
	}

	printw("Enter The Number Of Rows Of Your Key Matrix > ");
	scanw(" %[^\n]",test);

	while(!veri_enter(test))
	{
		attron(COLOR_PAIR(4));
		printw("Typing Error : \n\t\t\t<Enter>");
		attroff(COLOR_PAIR(4));
		getch();
		clear();
		ShowDescp();
		printw("\n\t\t\t\nHILL Encryption System :) \n\n");
		printw("Enter The Number Of Rows Of Your Key Matrix > ");
		scanw(" %[^\n]",test);
		refresh();
	}

	lgnk = convert_enter(test);

	if(lgnk != colm)
	{
		printw("It Is Impossible To Perform A Linear Combination With These Two Matrices.\nMake Sure That The Number Of Rows Of Your Key Matrix Is Equal To The Number Of Columns Of Your Message Matrix, Then Try Again!\n");
		attron(COLOR_PAIR(4));
		printw("\n\t\t\t<Enter>");
		getch();
		attroff(COLOR_PAIR(4));
		goto Retry;
	}
	printw("Enter The Number Of Colunms Of Your Key Matrix > ");
	scanw(" %[^\n]",test);
	while(!veri_enter(test))
	{
		attron(COLOR_PAIR(4));
		printw("Typing Error : \n\t\t\t<Enter>");
		attroff(COLOR_PAIR(4));
		getch();
		clear();
		ShowDescp();
		printw("\n\t\t\t\nHILL Encryption System :) \n\n");
		printw("Enter The Number Of Colunms Of Your Key Matrix > ");
		scanw(" %[^\n]",test);
		refresh();
	}

	colk = convert_enter(test);

	int key[lgnk][colk];

	for(int i = 0; i < lgnk; i++)
	{
		for(int  j = 0; j < colk; j++)
		{
			Bom : 
			printw("Enter The Element [%d][%d] > ",i + 1,j + 1);
			scanw(" %[^\n]",test);
			while(!veri_enter(test))
			{
				attron(COLOR_PAIR(4));
				printw("Typing Error : \n\t\t\t<Enter>");
				attroff(COLOR_PAIR(4));
				getch();
				clear();
				ShowDescp();
				printw("\n\t\t\t\nHILL Encryption System :) \n\n");
				printw("Enter The Element [%d][%d] > ",i + 1,j + 1);
				scanw(" %[^\n]",test);
				refresh();
			}
			key[i][j] = convert_enter(test);
			if(key[i][j] < 0 || mat[i][j] > 25)
			{
				attron(A_BOLD);
				printw("The Value Can't Excess 25. Make Sure Your Value Is In [0 - 25], The Retry\n");
				getch();
				refresh();
				goto Bom;
			}
		}
	}

	ShowDescp();
	printw("\nYour Key Is : \n\n");
	for(int i = 0; i < lgnk; i++)
	{
		for(int j = 0; j < colk; j++)
			printw("%d  ",key[i][j]);
		printw("\n");
	}

	int chif[lgnk][colm];
	for(int i = 0; i < lgnk; i++)
	{
		for(int j = 0; j < colm; j++)
		{
			chif[i][j] = 0;
			for(int k = 0; k < colk; k++)
				chif[i][j] += key[i][k] * mat[k][i];
			chif[i][j] %= 26;
		}
	}

	printw("The Encrypted Matrix Is : \n\n");
	for(int i = 0; i < lgnk; i++)
	{
		for(int j = 0; j < colm; j++)
			printw("%d  ",chif[i][j]);
		printw("\n");
	}
}

	//[****************** Rectangular Transposition ***************]

char *RecTranspos(char *mess, char *key)
{
    int len = strlen(mess);
    int klen = strlen(key);

    int rows = ceil(((double)len) / klen);

    char MatTrans[rows + 1][klen]; 
    for (int i = 0; i < klen; i++)
		MatTrans[0][i] = key[i];

    int t = 0;
    for (int i = 1; i <= rows; ++i)
    {
        for (int j = 0; j < klen; ++j)
			MatTrans[i][j] = (t < len) ? mess[t++] : 'X';
    }

    printw("\nMatrix Before Sort:\n");
    for (int i = 0; i <= rows; ++i)
	{
        for (int j = 0; j < klen; ++j)
			printw("%c ", MatTrans[i][j]);
        printw("\n");
    }
    int ind[klen];
    for (int i = 0; i < klen; i++)
		ind[i] = i;

    for (int i = 0; i < klen - 1; ++i)
	{
        for (int j = i + 1; j < klen; ++j)
		{
            if (MatTrans[0][i] > MatTrans[0][j])
			{
                
                char temp = MatTrans[0][i];
                MatTrans[0][i] = MatTrans[0][j];
                MatTrans[0][j] = temp;

                int tempi = ind[i];
                ind[i] = ind[j];
                ind[j] = tempi;
            }
        }
    }

    printw("\nMatrix After Sort :\n");
    for (int i = 0; i <= rows; ++i)
	{
        for (int j = 0; j < klen; ++j)
		{
            printw("%c ", MatTrans[i][j]);
        }
        printw("\n");
    }
    char *Trans = (char *)malloc((len + 1) * sizeof(char));
    if (Trans == NULL)
	{
        printw("Memory Allocation Error!\n");
        return NULL;
    }

    int pos = 0;
    for (int j = 0; j < klen; ++j)
	{
        int col = ind[j]; 
        for (int i = 1; i <= rows; ++i)
		{
            Trans[pos] = MatTrans[i][col];
            ++pos;
        }
    }

    Trans[pos] = '\0';

    return Trans;
}

//[********************************* End *******************************]
