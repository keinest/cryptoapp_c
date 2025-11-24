#include "headers/crypto.h"

//[*********************** ENCRYPTION ***********************]
						
	// [*********************** PRIME ***********************]
						
							int pgcd(int a,int b)
							{
								int temp = 0;
								while(b != 0)
								{		
									temp = b;
									b = a%b;
									a = temp;
								}
								return a;
							}
							
//[************************* BUFFER CONTROL ******************************]

		bool veri_enter(char *test)
		{
			for(int i = 0; test[i] != '\0'; ++i)
			{
				if(test[i] < '0' || test[i] > '9')
					return false;
			} 
			return true; 
		}
		
		int convert_enter(char *test)
		{
			int len = strlen(test);
			int result = 0;
			for(int i = 0; i < len; ++i)
				result = result * 10 + (test[i] - '0');
			return result;
		}


			//[*********************** RSA **************************]

#include <ncurses.h>
#include <stdlib.h>

	//[*********************** PRINT DESCRIPTION ***********************]

void ShowDescp()
{
    clear();
    start_color();
	system("date");
    init_pair(1, COLOR_CYAN, COLOR_BLACK);    
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);  
    init_pair(3, COLOR_GREEN, COLOR_BLACK);   
    init_pair(4, COLOR_RED, COLOR_BLACK);     

    printw("\n\n");
    attron(COLOR_PAIR(1) | A_BOLD);
    printw("\t\t\t\t======================== Encryption v1.0.3-dev ========================\n");
    attroff(COLOR_PAIR(1) | A_BOLD);

    attron(COLOR_PAIR(2));
    printw("\t\t\t\t + Exploits: ");
    attron(COLOR_PAIR(3));
    printw("6   ");
    attron(COLOR_PAIR(2));
    printw("| Auxiliary: ");
    attron(COLOR_PAIR(3));
    printw("7   ");
    attron(COLOR_PAIR(2));
    printw("| Tests: ");
    attron(COLOR_PAIR(3));
    printw("1459\n");

    printw("\t\t\t\t + Payloads: Encoders  | Developer: ");
    attron(COLOR_PAIR(4) | A_BOLD);
    printw("SOULKING (THE GEEK-GTS)\n");
    attroff(COLOR_PAIR(4) | A_BOLD);

    attron(COLOR_PAIR(2));
    printw("\t\t\t\t + Nops: ");
    attron(COLOR_PAIR(3));
    printw("11    ");
    attron(COLOR_PAIR(2));
    printw("| Modules: ");
    attron(COLOR_PAIR(3));
    printw("13\n");

    printw("\t\t\t\t + Source Code: ");
    attron(COLOR_PAIR(3));
    printw("Available at GPL Licence\n");

    attron(COLOR_PAIR(1));
    printw("\t\t\t\t---------------------------------------------------------------\n");
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(4) | A_BOLD);
    printw("\t\t\t\t Encryption Documentation: linedevils271@gmail.com\n");
    attroff(COLOR_PAIR(4) | A_BOLD);

    printw("\n");
}

	//[*********************** PRINT DESCRIPTION (FOR THE GUESS) ***********************]

void ShowDescpTry()
{
    start_color();

    init_pair(1, COLOR_CYAN, COLOR_BLACK);  
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);  
	system("date");
    printw("\n\n");

    attron(COLOR_PAIR(1) | A_BOLD);
    printw("\t\t\t\t===== Welcome to the Cryptography System =====\n\n");
    attroff(COLOR_PAIR(1) | A_BOLD);

    attron(COLOR_PAIR(2));
    printw("\t\t\t\t0 --> Return\n");
	printw("\t\t\t\t1 --> RSA Encryption System\n");
    printw("\t\t\t\t2 --> Affine Encryption System\n");
    printw("\t\t\t\t3 --> Cesar Encryption System\n");
    printw("\t\t\t\t4 --> Vigenere Encryption System\n");
    printw("\t\t\t\t5 --> Vernam Encryption System\n");
    printw("\t\t\t\t6 --> HILL Encryption System\n");
    printw("\t\t\t\t7 --> Rectangular Encryption System\n");
	printw("\t\t\t\t8 --> Feistel Encryption System\n");
    printw("\t\t\t\t9 --> PlayFair Encryption System\n");
    attroff(COLOR_PAIR(2));

    printw("\n");
    attron(COLOR_PAIR(1) | A_BOLD);
    printw("\t\t\t\t==============================================\n\n");
    attroff(COLOR_PAIR(1));
}

long long int p,q,e,m;

	//[*********************** POWER ***********************]

long long int power(int a,int b)
{	
	if(b == 0)
		return 1;
	return a * power(a,b-1);
}					
	
	//[*********************** RSA ENCRYPTION ***********************]

char *Rsa(char *m,long long int e,long long int n)
{
	int len = strlen(m);
	for(int i = 0; i < len; ++i)
	{
		char base = (isupper(m[i])) ? 'A' : 'a';
		m[i] = (int)m[i];
		m[i] = power(m[i],(int)e) % n;
		m[i] = (m[i] % 26) + (int)base;
        m[i] = (char)m[i];
	}

	return m;
}

	//[*********************** AFFINE **************************]

int k1,k2;	
int AFFINE()
{
	char key[50000];
	Enter:
	ShowDescp();
	printw("Enter The First Key > ");
	scanw(" %[^\n]",key);
	
	if(!veri_enter(key))
	{
		attron(COLOR_PAIR(4));
		printw("ERROR!\nTyping Error!\n");
		printw("\n\t\t\t<Enter>");
		getch();
		attroff(COLOR_PAIR(4));
		goto Enter;
	}

	k1 = convert_enter(key);
	
	if(k1 < 0 || k1 > 25)
	{	
		printw("ERROR! The Key Value Is Incorrect,She Have To Be Between 0 And 25!\n");
		napms(2000);
		goto Enter;
	}

	int prime = pgcd(k1,26);
	
	if(prime != 1)
	{
		printw("The First Key Have To Be Prime With The Alphabet Length\nCheck And Retry The New Value!\n");
		attron(COLOR_PAIR(4));
		printw("\n\t\t\t<Enter>");
		getch();
		attroff(COLOR_PAIR(4));
		goto Enter;
	}

	key2:
	
	printw("Enter The Second Key > ");
	scanw(" %[^\n]",key);
	
	if(!veri_enter(key))
	{
		attron(COLOR_PAIR(4));
		printw("ERROR!\nTyping Error!\n");
		printw("\n\t\t\t<Enter>");
		getch();
		attroff(COLOR_PAIR(4));
		goto key2;
	}

	k2 = convert_enter(key);
	
	if(k2 < 0 || k2 > 25)
	{
		printw("ERROR! The Key Value Is Incorrect,She Have To Be Between 0 And 25!\n");
		attron(COLOR_PAIR(4));
		printw("\n\t\t\t<Enter>");
		getch();
		attroff(COLOR_PAIR(4));
		goto key2;
	}

	back:
	
	printw("Enter The Message To Be Encrypted > ");
	scanw(" %[^\n]",key);
	
	if(!veri_enter(key))
	{
		attron(COLOR_PAIR(4));
		printw("ERROR!\nTyping Error!\n");
		printw("Enter The Position Of The Character To Be Encrypted[0,25]\n");
		printw("\n\t\t\t<Enter>");
		getch();
		attroff(COLOR_PAIR(4));
		goto back;
	}

	int m = convert_enter(key);
	
	if(m < 0 || m >= 26)
	{
		printw("The Message Have To Be In [0,25]\n");
		attron(COLOR_PAIR(4));
		printw("\n\t\t\t<Enter>");
		getch();
		attroff(COLOR_PAIR(4));
		goto back;
	}

	int M = (m*k1 + k2) % 26;
	printw("In Process To Encryption.../\n");
	printw("The Encrypt Message Of %d Is (%d * %d + %d) mod 26 = %d\n",m,m,k1,k2,M);
	return M;
}


	//[*********************** CESAR **************************]

char *cle = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

void CESAR()
{
	char mess[100000];
	Entrer:
	printw("Enter The Message To Be Encrypted > ");
	scanw(" %[^\n]",mess);
	int see;
	char *chif = (char*)malloc(strlen(mess)*sizeof(char)),key;
	
	if(chif == NULL)
	{
		printw("Memory Allocation Error\033[0m\n");
		goto Entrer;
	}

	retry:
	printw("Enter The Encryption Key > ");
	
	if(scanw(" %c",&key) == 1 && getch() == '\n')
	{
		for(int i = 0; cle[i] != '\0'; ++i)
		{
			if(toupper(key) == cle[i])
			{
				see = 1;
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
					char pos = (mess[i] + key) % 26;
					chif[i] = start + pos;
				}
				else
					chif[i] = mess[i];
				++i;
			}

			chif[i] = '\0';
			printw("In Process Of Encryption.../\n");
			printw("The Encrypted Message Of %s Is %s\n\n",mess,chif);
		}

		else
		{
			printw("Key Not Found!\nPlease Retry\n");
			goto retry;
		}
	}

	else
	{

		printw("Impossible to encrypt with this key. The key must be a single character.\n");
		goto retry;
	}
}
//[********************************* END *******************************]
