#include "headers/crypto.h"
#include "headers/decrypt.h"


//[*************************** DESCRYPTION OF THE DIFFERENT ENCRYPTION SYSTEME (FRENCH VERSION) ***************************]

void helpFr(char *path)
{
    FILE *fs = fopen(path,"r");
    if(!fs)
    {
        printw("ERROR (404) : Help page not found :) !\n\n");
        attron(COLOR_PAIR(4) | A_BOLD);
        printw("\t\t\t<Enter>");
        getch();
        attroff(COLOR_PAIR(4));
        refresh();
        return;
    }

	clear();
	attron(A_BOLD);
    char ch;
	int i = 0;
	while(fs)
	{

		for(int j = 0; j < LINES; j++)
		{
			fflush(stdout);
			if(i == LINES - 2)
			{
				printw("\n\n\tCliquez sur Entrer pour continuer");
				getch();
				i = 0;
				clear();
			}
			ch = getc(fs);
			printw("%c",ch);
			refresh();
			usleep(10000);
			fflush(stdout);
		}
		i++;
		if(feof(fs))
			break;
	}
	fclose(fs);
    printw("\n\n");
}

//[*************************** DESCRYPTION OF THE DIFFERENT ENCRYPTION SYSTEME (ENGLISH VERSION) ***************************]

void helpEn(char *path)
{
    FILE *fs = fopen(path,"r");
    if(!fs)
    {
        printw("ERROR (404) : Help page not found :) !\n\n");
        attron(COLOR_PAIR(4) | A_BOLD);
        printw("\t\t\t<Enter>");
        getch();
        attroff(COLOR_PAIR(4));
        refresh();
        return;
    }
	clear();
	attron(A_BOLD);
    char ch;
	int i = 0;
	while(fs)
	{

		for(int j = 0; j < LINES; j++)
		{
			fflush(stdout);
			if(i == LINES - 2)
			{
				printw("\n\n\tClick on enter to continue");
				getch();
				i = 0;
				clear();
			}
			ch = getc(fs);
			printw("%c",ch);
			refresh();
			usleep(10000);
			fflush(stdout);
		}
		i++;
		if(feof(fs))
			break;
	}
	fclose(fs);
    printw("\n\n");
}