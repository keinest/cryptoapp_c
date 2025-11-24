#include "headers/crypto.h"
#include "headers/decrypt.h"
#include "headers/Users.h"

int main()
{
	ListUsers *head = NULL;
    initscr();
    start_color();
    cbreak();
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_RED, COLOR_BLACK);

	anim();

	head = UpdateUsers();
    char test[100];
    int dec,auth = 0;
	clear();
	Deb:
    do
	{
		clear();
		do
		{
			clear();
			Home();
			scanw("%99s",test);
		}while(!veri_enter(test));

		dec = convert_enter(test);
		switch (dec)
		{
			case 1:
			{
				int choix;
				clear();
				ShowDescpTry();
				do
				{
					clear();
					ShowDescpTry();
					refresh();
					scanw("%99s",test);
					refresh();
				}while(!veri_enter(test));

				attron(A_BOLD);
				choix = convert_enter(test);
				switch(choix)
				{
					case 1:
					{
						int choice;
						do
						{
							clear();
							printw("\t\t\tRSA Encryption System\n\t\t\t1 --> Encrypt\n\t\t\t2 --> Decrypt\n\n> ");
							scanw("%99s",test);
							refresh();
						}while(!veri_enter(test));

						choice = convert_enter(test);
						refresh();
						switch(choice)
						{
							case 1:
							{
								long long int n,p,q,phi,e;
								char m[1000];
								Integer:
								do
								{
									printw("Enter The First Integer > ");
									scanw("%99s",test);
									refresh();
								}while(!veri_enter(test));

								p = convert_enter(test);
								do
								{
									printw("Enter The Second Integer > ");
									scanw("%99s",test);
									refresh();
								}while(!veri_enter(test));
								refresh();

								q = convert_enter(test);
								if(pgcd(p,q) != 1)
								{
									printw("Your Integer Are Not The Primes Numbers \n");
									getch();
									refresh();
									goto Integer;
								}
								n = p * q;
								printw("Your Public Value Is n = %lld * %lld = %lld\n\n",p,q,n);
								refresh();	
								phi = (p - 1) * (q - 1);
								printw("The Euler Function Is phi(%lld) = (%lld - 1) x (%lld - 1) = %lld\n\n",n,p,q,phi);
								KeyVal :
								do
								{
									printw("Enter The Encryption Key > ");
									scanw("%99s",test);
								}while(!veri_enter(test));
								e = convert_enter(test);
								if(pgcd(phi,e) != 1 && (e < 2 || e >= phi))
								{
									printw("The Value Of The Key Is Not Compatible!\n");
									getch();
									goto KeyVal;
								}
								printw("Enter The Message To Be Encrypted > ");
								scanw(" %999[^\n]",m);
								char Copy[1000];
								strcpy(Copy,m);
								printw("The Encrypted Message Of %s Is M = (%s)^%lld mod %lld = %s\n\n",Copy,Copy,e,n,Rsa(m,e,n));
								refresh();
								getch();
								goto Deb;
							}
							break;
							case 2:
							{
								char request[5];
								printw("Please Open An Account Before Decrypt A Message Or Connect To Your Account!\n\n");
								printw("Do You Want To Open An Account Or Login ?(y --> Create An Account/Y --> Login) : ");
								scanw("%4s",request);
								refresh();
								if(request[0] == 'Y')
								{
									refresh();
									goto AuthOr;
								}
								if(request[0] == 'y')
								{
									refresh();
									goto Login;
								}
								goto Deb;

							}
							break;
							default:
							{
								printw("Invalid Option\n\n");
								attron(COLOR_PAIR(4) | A_BOLD);
								printw("\t\t\t<Enter>");
								getch();
								attroff(COLOR_PAIR(4));
								goto Deb;
							}
						}
					}
					break;
					case 2:
					{
						int dec;
						do
						{
							clear();
							printw("\t\t\tAFFINE Encryption System\n");
							printw("\t\t1 --> Encrypt\n\t\t2 --> Decrypt\n\n> ");
							scanw("%99s",test);
							refresh();
						}while(!veri_enter(test));
						dec = convert_enter(test);
						switch(dec)
						{
							case 1:
							{
								AFFINE();
								refresh();
								getch();
								goto Deb;
							}
							break;
							case 2:
							{
								refresh();
								printw("Please Create An Account First Before Decrypt Message\n\n");
								refresh();
								char request[5];
								printw("Please Open An Account Before Decrypt A Message Or Connect To Your Account!\n\n");
								printw("Do You Want To Open An Account Or Login ?(y --> Create An Account/Y --> Login) : ");
								scanw("%4s",request);
								refresh();
								if(request[0] == 'Y')
								{
									refresh();
									goto AuthOr;
								}
								if(request[0] == 'y')
								{
									refresh();
									goto Login;
								}
								goto Deb;
							}
							break;
							default:
							{
								printw("Invalid Option!\n\n");
								attron(COLOR_PAIR(4) | A_BOLD);
								printw("\t\t\t<Enter>");
								getch();
								attroff(COLOR_PAIR(4));
								goto Deb;
							}
						}					
					}
					break;
					case 3:
					{
						int dec;
						do
						{
							printw("\t\t\t\tCesar Encryption System\n\t\t\t1 --> Encrypt\n\t\t\t2 --> Decrypt\n");
							scanw("%99s",test);
							refresh();
						}while(!veri_enter(test));;
						dec = convert_enter(test);
						switch(dec)
						{
							case 1:
							{
								CESAR();
								refresh();
								printw("\t\t\t<Enter>");;
								getch();
								goto Deb;
							}
							break;
							case 2:
							{
								char request[5];
								printw("Please Open An Account Before Decrypt A Message Or Connect To Your Account!\n\n");
								printw("Do You Want To Open An Account Or Login ?(y --> Create An Account/Y --> Login) : ");
								scanw("%4s",request);
								refresh();
								if(request[0] == 'Y')
								{
									refresh();
									goto AuthOr;
								}
								if(request[0] == 'y')
								{
									refresh();
									goto Login;
								}
								goto Deb;
							}
							break;
							default:
							{
								refresh();
								printw("Invalid Option!\n\n");
								attron(COLOR_PAIR(4) | A_BOLD);
								printw("\t\t\t<Enter>");
								attroff(COLOR_PAIR(4));
								getch();
								refresh();
								goto Deb;
							}
						}
					}
					break;
					case 4:
					{
						int dec;
						do
						{
							refresh();
							printw("\t\t\t\tVigenere Encryption Systen\n\t\t\t1 --> Encrypt\n\t\t\t2 --> Decrypt\n\n> ");
							scanw("%99s",test);
						}while(!veri_enter(test));
						dec = convert_enter(test);
						switch(dec)
						{
							case 1:
							{
								char mess[1000],key[500];
								Vigenere(mess,key);
								printw("\n\t\t\t<Enter>");
								goto Deb;
							}
							break;
							case 2:
							{
								char request[5];
								printw("Please Open An Account Before Decrypt A Message Or Connect To Your Account!\n\n");
								printw("Do You Want To Open An Account Or Login ?(y --> Create An Account/Y --> Login) : ");
								scanw("%4s",request);
								refresh();
								if(request[0] == 'Y')
								{
									refresh();
									goto AuthOr;
								}
								if(request[0] == 'y')
								{
									refresh();
									goto Login;
								}
								goto Deb;
							}
							break;
							default :
							{
								refresh();
								printw("Invalid Option!\n\n");
								attron(COLOR_PAIR(4) | A_BOLD);
								printw("\t\t\t<Enter>");
								attroff(COLOR_PAIR(4));
								getch();
								refresh();
								goto Deb;
							}
						}
					}
					break;
					case 5:
					{
						int dec;
						do
						{
							printw("\t\t\t\tVernam Encryption System\n\t\t\t1 --> Encrypt\n\t\t\t2 --> Decrypt\n\n ");
							scanw("%99s",test);
							refresh();
						}while(!veri_enter(test));
						dec = convert_enter(test);
						
						switch(dec)
						{
							case 1:
							{
								char mess[1000],key[1000];
								Vernam(mess,key);
								printw("\n\t\t\t<Enter>");
								getch();
								goto Deb;
							}
							break;
							case 2:
							{
								char request[5];
								printw("Please Open An Account Before Decrypt A Message Or Connect To Your Account!\n\n");
								printw("Do You Want To Open An Account Or Login ?(y --> Create An Account/Y --> Login) : ");
								scanw("%4s",request);
								refresh();
								if(request[0] == 'Y')
								{
									refresh();
									goto Login;
								}
								if(request[0] == 'y')
								{
									refresh();
									goto AuthOr;
								}
								goto Deb;
							}
							break;
							default:
							{
								refresh();
								printw("Invalid Option!\n\n");
								attron(COLOR_PAIR(4) | A_BOLD);
								printw("\t\t\t<Enter>");
								attroff(COLOR_PAIR(4));
								getch();
								refresh();
								goto Deb;
							}
						}
					}
					break;
					case 6 :
					{
						int dec;
						do
						{
							printw("\t\t\t\tHILL Encryption System\n\t\t\t1 --> Encrypt\n\t\t\t2 --> Decrypt\n ");
							scanw("%99s",test);
							refresh();
						}while(!veri_enter(test));
						dec = convert_enter(test);

						switch(dec)
						{
							case 1:
							{
								HILL();
								attron(COLOR_PAIR(4) | A_BOLD);
								printw("\t\t\t<Enter>");
								attroff(COLOR_PAIR(4));
								getch();
								refresh();
								goto Deb;
							}
							break;
					
							case 2:
							{
								char request[5];
								printw("Please Open An Account Before Decrypt A Message Or Connect To Your Account!\n\n");
								printw("Do You Want To Open An Account Or Login ?(y --> Create An Account/Y --> Login) : ");
								scanw("%4s",request);
								refresh();
								if(request[0] == 'Y')
								{
									refresh();
									goto Login;
								}
								if(request[0] == 'y')
								{
									refresh();
									goto AuthOr;
								}
								goto Deb;
							}
							break;
					
							default:
							{
								refresh();
								printw("Invalid Option!\n\n");
								attron(COLOR_PAIR(4) | A_BOLD);
								printw("\t\t\t<Enter>");
								attroff(COLOR_PAIR(4));
								getch();
								refresh();
								goto Deb;
							}
						}
					}
					break;
					
					case 7:
					{
						int dec;
						do
						{
							printw("\n\t\t\t\tRectangular Transposition Encryption System\n\t\t\t1 --> Encrypt\n\t\t\t2 --> Decrypt\n");
							refresh();
							scanw(" %[^\n]",test);
						}while(!veri_enter(test));
						dec = convert_enter(test);

						switch(dec)
						{
							case 1:
							{
								char mess[10000],key[5000];
								Start :
								printw("Enter The Message To Be Encrypted > ");
								scanw(" %[^\n]",mess);
								refresh();
								printw("Enter De Encryption Key > ");
								scanw(" %[^\n]",key);
								if(strlen(key) > strlen(mess))
								{
									printw("Impossible To Perform The Encryption With This Key Because His Lenght Is More Large Than The Message Lenght\n\n");
									printw("Try Again\n\n");
									getch();
									goto Start;
								}
								RecTranspos(mess,key);
								printw("\n\t\t\t<Enter>");
								getch();
								goto Deb;
							}
							break;
					
							case 2:
							{
								char request[5];
								printw("Please Open An Account Before Decrypt A Message Or Connect To Your Account!\n\n");
								printw("Do You Want To Open An Account Or Login ?(y --> Create An Account/Y --> Login) : ");
								scanw("%4s",request);
								refresh();
								if(request[0] == 'Y')
								{
									refresh();
									goto AuthOr;
								}
								if(request[0] == 'y')
								{
									refresh();
									goto Login;
								}
								goto Deb;
							}
							break;
					
							default:
							{
								refresh();
								printw("Invalid Option!\n\n");
								attron(COLOR_PAIR(4) | A_BOLD);
								printw("\t\t\t<Enter>");
								attroff(COLOR_PAIR(4));
								getch();
								refresh();
								goto Deb;
							}
						}
					}
					break;
					
					case 8 :
					{
						char word[100];
						do
						{	
							ShowDescp();
							attron(A_BOLD);
							printw("\n\n\t\t\tFeistel Encryption System\n\n");
							printw("\n\t\t\t0 --> Return\n\t\t\t1 --> Encrypt\n\t\t\t2 --> Decrypt\n\n");
							scanw(" %99[^\n]",word);
						}while(!veri_enter(word));
						int dec = convert_enter(word);

						switch(dec)
						{
							case 1:
							{
								ShowDescp();
								printw("\n\t\t\tFeistel Encryption System\n\n");
								ShowDescp();
								attron(A_BOLD);
								printw("\n\nFeistel Encryption System\n\n");
								Feistel *node = NULL, *Key = NULL, *chif = NULL;
								char mess[1000],key[1000],op[50];
								printw("Enter The message to be encrypted > ");
								scanw(" %999[^\n]",mess);

								for(int i = 0; i < (int)strlen(mess); ++i)
									node = ConvertTobin(node,(int)mess[i]);
								printw("Message :) \n\n");
								Show(node);
								printw("\n<Enter>");
								getch();
								clear();
								refresh();
								printw("Enter The encryption key > ");
								scanw(" %999[^\n]",key);

								for (int i = 0; i < (int)strlen(key); ++i)
        							Key = ConvertTobin(Key, (int)key[i]);
    							printw("Key :) \n\n");
    							Show(Key);
								printw("\n<Enter>");
								getch();
								refresh();
								clear();
								printw("Enter The Operator(XOR/OR/AND/C(~)) > ");
								scanw(" %49[^\n]",op);
								chif = feistel(node, Key, op);
    							printw("Encrypted message :)\n\n");
    							ShowF(chif);
								attron(COLOR_PAIR(4) | A_BOLD);
								printw("\t\t\t<Enter>");
								getch();
								attroff(COLOR_PAIR(4));
								refresh();
								chif = FreeKey(chif);
								
								goto Deb;
							}
							break;
							case 2:
							{
								char request[5];
								printw("Please Open An Account Before Decrypt A Message Or Connect To Your Account!\n\n");
								printw("Do You Want To Open An Account Or Login ?(y --> Create An Account/Y --> Login) : ");
								scanw("%4s",request);
								refresh();
								if(request[0] == 'Y')
								{
									refresh();
									goto AuthOr;
								}
								if(request[0] == 'y')
								{
									refresh();
									goto Login;
								}
								goto Deb;
							}
							break;
							case 0:
								goto Deb;
							default :
							{
								printw("Error :) !\n\n");
								attron(COLOR_PAIR(4) | A_BOLD);
								printw("Typing Error !\n\n\t\t\t<Enter>");
								getch();
								goto Deb;
							}
						}

					}
					break;

					case 9:
					{
						printw("This System Is Not Yet Updated!\n");
						getch();
						goto Deb;
					}
					break;
					
					default:
					{
						refresh();
						printw("Invalid Option!\n\n");
						attron(COLOR_PAIR(4) | A_BOLD);
						printw("\t\t\t<Enter>");
						attroff(COLOR_PAIR(4));
						getch();
						refresh();
						goto Deb;
					}
				}
			}
			break;
			
			case 2:
			{
				Login:
				UsersInf(&head);
				printw("Your Account Has Been Created.../\n");
				attron(COLOR_PAIR(4 | A_BOLD));
				printw("\t\t\t<Enter>");
				getch();
				attroff(COLOR_PAIR(4));
				goto Deb;
			}
			break;
			
			case 3:
			{
				AuthOr:
				auth = AuthCTion(head);
				if(auth == 0)
					goto SuperUser;
				else 
				{
					refresh();
					attron(COLOR_PAIR(4) | A_BOLD);
            		printw("\n\nCan't Found This Account!\n");
            		refresh();
            		attron(COLOR_PAIR(4) | A_BOLD);
            		printw("\n\t\t\t<Enter>");
					getch();
            		attroff(COLOR_PAIR(4));
            		echo();
					goto Deb;
				}
			}
			break;
			
			case 0:
			{
				echo();
				freeList(head);
				system("rm *.o && rm RunCrypt");
				endwin();
				exit(EXIT_SUCCESS);
			}
			break;

			default:
			{
				refresh();
				printw("Invalid Option!\n\n");
				attron(COLOR_PAIR(4) | A_BOLD);
				printw("\t\t\t<Enter>");
				getch();
				attroff(COLOR_PAIR(4));
				goto Deb;
			}
		}
		SuperUser:
		do{
			int dec;
			refresh();
			do
			{
				MENU:
				ShowDescp();
				ShowDescpTry();
				printw("\n\t\t\t\tChoose an option : ");
				scanw(" %[^\n]",test);
				refresh();
			}while(!veri_enter(test));
			
			dec = convert_enter(test);

			switch(dec)
			{
				case 1:
				{
					int dec;
					do
					{
						RSA:
						clear();
						ShowDescp();
						attron(A_BOLD);
						printw("\t\t\t[********************* RSA decryption System *********************]\n\n");
						printw("\t\t\t\t\t\t1 --> Encrypt\n");
						printw("\t\t\t\t\t\t2 --> Decrypt\n");
						printw("\t\t\t\t\t\t3 --> Help\n");
						printw("\t\t\t\t\t\t0 --> Return\n");
						printw("\n\t\t\t\t\t\tChose an option : ");
						scanw("%99[^\n]",test);
					}while(!veri_enter(test));
					attroff(A_BOLD);
					dec = convert_enter(test);
					switch(dec)
					{
						case 1:
						{
							long long int p,q,n,e,phi;
							char m[1000];
							Int :
							ShowDescp();
							printw("\t\t\t[********************* RSA decryption System *********************]\n\n");
							printw("Enter The First Integer > ");
							scanw(" %[^\n]",test);
							while(!veri_enter(test))
							{
								ShowDescp();
								printw("\t\t\t[********************* RSA decryption System *********************]\n\n");
								printw("Enter The First Integer > ");
								scanw(" %[^\n]",test);
								refresh();
							}
							p = convert_enter(test);

							printw("Enter The Second Interger > ");
							scanw(" %[^\n]",test);
							while(!veri_enter(test))
							{
								ShowDescp();
								printw("\t\t\t[********************* RSA decryption System *********************]\n\n");
								refresh();
								printw("Enter The Second Interger > ");
								scanw(" %[^\n]",test);
								refresh();
							}
							q = convert_enter(test);

							if(pgcd(p,q) != 1)
							{
								clear();
								ShowDescp();
								printw("\t\t\t[********************* RSA decryption System *********************]\n\n");
								printw("Your integers are not coprime and cannot be used for encryption.\n");
								printw("\nRetry \n");
								getch();
								goto Int;
							}

							n = p * q;
							phi = (p - 1) * (q - 1);
							printw("The Public Value Is n = %lld x %lld = %lld\n\n",p,q,n);
							printw("The Euler's Function Is phi(%lld) = (%lld - 1) x (%lld - 1) = %lld\n\n",n,p,q,phi);
							Key :
							
							printw("Enter The Encryption Key > ");
							scanw(" %[^\n]",test);
							while(!veri_enter(test))
							{
								ShowDescp();
								printw("\t\t\t[********************* RSA decryption System *********************]\n\n");
								printw("Enter The Encryption Key > ");
								scanw(" %[^\n]",test);
								refresh();
							}

							e = convert_enter(test);

							if(pgcd(e,phi) != 1)
							{
								clear();
								ShowDescp();
								printw("\t\t\t[********************* RSA decryption System *********************]\n\n");
								printw("Your Intergers Are Not Coprime And Cannot Be Use For Encryption\n\n");
								refresh();
								printw("Retry!\n\n");
								getch();
								goto Key;
							}
							printw("Enter The Message To Be Encrypted > ");
							scanw(" %999[^\n]",m);
							char Copy[1000];
							strcpy(Copy,m);
							printw("\nThe Encrypted Message Of %s Is M = (%s) ^ %lld mod %lld = %s\n\n",Copy,Copy,e,n,Rsa(m,e,n));
							fflush(stdout);
							attron(COLOR_PAIR(4) | A_BOLD);
							printw("\t\t\t<Enter>");
							getch();
							attroff(COLOR_PAIR(4));
							goto RSA;
						}
						break;
						case 2:
						{
							long long int p,q,n,phi;
							char mess[1000];
							attron(A_BOLD);
							Decrypt:
							ShowDescp();
							printw("\t\t\t[********************* RSA decryption System *********************]\n\n");
							printw("Enter teh first integer > ");
							scanw(" %99[^\n]",test);
							while(!veri_enter(test))
							{
								ShowDescp();
								printw("\t\t\t[********************* RSA decryption System *********************]\n\n");
								attroff(COLOR_PAIR(4) | A_BOLD);
								printw("Error :) ! Typing Error !\n\n\t\t\t\t<Enter>");
								getch();
								attroff(COLOR_PAIR(4));
								printw("Enter teh first integer > ");
								scanw(" %99[^\n]",test);
							}

							p = convert_enter(test);

							printw("Enter teh second integer > ");
							scanw(" %99[^\n]",test);
							while(!veri_enter(test))
							{
								ShowDescp();
								printw("\t\t\t[********************* RSA decryption System *********************]\n\n");
								attroff(COLOR_PAIR(4) | A_BOLD);
								printw("Error :) ! Typing Error !\n\n\t\t\t\t<Enter>");
								getch();
								attroff(COLOR_PAIR(4));
								printw("Enter teh first integer > ");
								scanw(" %99[^\n]",test);
							}

							q = convert_enter(test);

							if(pgcd(p,q) == 0)
							{
								printw("It's impossible to perform a decryption with these intergers so they are not coprime ! Please check en retry\n\n");
								attron(COLOR_PAIR(4) | A_BOLD);
								printw("\t\t\t\t<Enter>");
								getch();
								attroff(COLOR_PAIR(4));
								refresh();
								goto Decrypt;
							}

							n = p * q;
							printw("The encryption module is n = %lld x %lld = %lld\n",p,q,n);
							phi = (p -1) * (q - 1);
							printw("The Euler's function is phi(%lld) = (%lld - 1) x (%lld - 1) = %lld\n",n,p,q,phi);
							Dkey:
							printw("Enter de Encryption key > ");
							scanw(" %99[^\n]",test);

							while(!veri_enter(test))
							{
								ShowDescp();
								printw("\t\t\t[********************* RSA decryption System *********************]\n\n");
								attron(COLOR_PAIR(4) | A_BOLD);
								printw("Error :) ! Typing error !\n\n");
								goto Dkey;
							}

							e = convert_enter(test);
							printw("Enter the message to be decrypted > ");
							scanw(" %999[^\n]",mess);
							char decrRsa[1000];
							strcpy(decrRsa,mess);
							if(!decryptRSA(mess,phi,e,n))
							{
								printw("It's impossible to perform a decryption with these integer ! Please check the value of the encryption key and retry !\n");
								attron(COLOR_PAIR(4) | A_BOLD);
								printw("\n\t\t\t\t<Enter>");
								getch();
								refresh();
								goto Dkey;
							}

							printw("The decrypted messge of %s is %s\n\n",decrRsa,decryptRSA(mess,phi,e,n));
							attron(COLOR_PAIR(4) | A_BOLD);
							printw("\t\t\t<Enter>");
							getch();
							attroff(COLOR_PAIR(4));
							refresh();
							goto RSA;	
						}
						break;
						case 3:
						{
							int dec;
							clear();
							do
							{
								ShowDescp();
								attron(COLOR_PAIR(2) | A_BOLD);
								printw("\t\t\t1 --> French Version\n\t\t\t2 --> English Version\n\t\t\t0 --> Return\n");
								printw("\n\t\t\tChose an option : ");
								scanw(" %[^\n]",test);
							}while(!veri_enter(test));
							attroff(COLOR_PAIR(2));
							dec = convert_enter(test);
							switch(dec)
							{
								case 1:
								{
									char *path = "Help/RSAHelpFr.txt";
									helpFr(path);
									refresh();
									attron(COLOR_PAIR(4) | A_BOLD);
									printw("\n\t\t\t<Enter>");
									getch();
									attroff(COLOR_PAIR(4));
									goto RSA;
								}
								break;
								case 2:
								{
									char *path = "Help/RSAHelpEn.txt";
									helpEn(path);
									refresh();
									attron(COLOR_PAIR(4) | A_BOLD);
									printw("\n\t\t\t<Enter>");
									getch();
									attroff(COLOR_PAIR(4));
									goto RSA;
								}
								break;
								case 0:
								{
									goto RSA;
								} 
								break;
								default:
								{
									printw("Invalid Option\n\n");
									attron(COLOR_PAIR(4));
									printw("\t\t\t<Enter>");
									getch();
									attroff(COLOR_PAIR(4));
								}
							}
						}
						break;
						case 0:
						{
							goto MENU;
						}
					}
					
				}
				break;
				case 2:
				{
					int dec;
					clear();
					ShowDescp();
					do
					{
						AFFINE:
						ShowDescp();
						attron(A_BOLD);
						printw("\t\t\t[*********************** Affine Encryption System ***********************]\n");
						printw("\n\t\t\t\t\t1 --> Encrypt\n\t\t\t\t\t2 --> Decrypt\n\t\t\t\t\t3 --> Help\n\t\t\t\t\t0 --> Return\n");
						printw("\n\t\t\t\t\tChose an option : ");
						scanw(" %99[^\n]",test);
						refresh();
					}while(!veri_enter(test));

					dec = convert_enter(test);
					switch(dec)
					{
						case 1 :
						{
							ShowDescp();
							printw("\t\t\t[*********************** Affine Encryption System ***********************]\n");
							AFFINE();
							attron(COLOR_PAIR(4) | A_BOLD);
							printw("\t\t\t<Enter>");
							getch();
							goto AFFINE;
						}
						break;
						case 2 :
						{
							ShowDescp();
							printw("\t\t\t[*********************** Affine Encryption System ***********************]\n");
							printw("This System Is Not Yet Updated\n\t\t\t<Enter>");
							getch();
							goto AFFINE;
						}
						break;
						case 3:
						{
							do
							{
								ShowDescp();
								attron(A_BOLD);
								printw("\t\t\t[*********************** Affine Encryption System ***********************]\n");
								printw("\n\t\t\t\t\t1 --> French version\n\t\t\t\t\t2 --> English version\n\t\t\t\t\t0 --> Return\n\n\t\t\t\t\tChoose an option : ");
								scanw(" %99[^\n]",test);
							}while(!veri_enter(test));
							
							int dec = convert_enter(test);

							switch(dec)
							{
								case 1:
								{
									char *path = "Help/AffineHelpFr.txt";
									helpFr(path);
									printw("\n\n\t\t\t\t<Entrer>");
									getch();
									goto AFFINE;
								}
								break;
								case 2:
								{
									char *path = "Help/AffineHelpEn.txt";
									helpEn(path);
									printw("\n\n\t\t\t\t<Enter>");
									getch();
									goto AFFINE;
								}
								break;
								case 0:
									goto AFFINE;
								break;
								default:
								{
									attron(A_BOLD | COLOR_PAIR(4));
									printw("\nInvalid option\n\n\t\t\t\t<Enter>");
									getch();
									goto AFFINE;
								}
							}
						}
						break;
						case 0:
						{
							goto MENU;
						}
						break;
						default:
						{
							printw("Invalid Option!\n\n");
							attron(COLOR_PAIR(4) | A_BOLD);
							printw("\n\t\t\t<Enter>");
							getch();
							attroff(COLOR_PAIR(4));
						}
					}
				}
				break;
				case 3:
				{
					int dec;
					CESAR:
					attron(A_BOLD);
					do
					{
						ShowDescp();
						attron(A_BOLD);
						printw("\t\t\t[*********************** Cesar Encryption System ***********************]\n");
						printw("\n\t\t\t\t\t0 --> Return\n\t\t\t\t\t1 --> Ecrypt\n\t\t\t\t\t2 --> Decrypt\n\n\t\t\t\t\tChose an option : ");
						scanw(" %[^\n]",test);
						refresh();
					}while(!veri_enter(test));

					dec = convert_enter(test);

					switch(dec)
					{
						case 1:
						{
							ShowDescp();
							printw("\t\t\t[*********************** Cesar Encryption System ***********************]\n");
							CESAR();
							refresh();
							attron(COLOR_PAIR(4));
							printw("\n\t\t\t<Enter>");
							getch();
							attroff(COLOR_PAIR(4));
							goto CESAR;
						}
						break;
						case 2:
						{
							char key,mess[10000];
							int i = 0,see = 0;
							StarT:
							ShowDescp();
							printw("\t\t\t[*********************** Cesar Encryption System ***********************]\n");
							printw("Enter The Encryption Key > ");
							int len = strlen(cle);
							if(scanw(" %c",&key) == 1 && getch() == '\n')
							{
								while(cle[i] != '\0')
								{
									if(cle[i] == toupper(key))
									{
										++see;
										break;
									}
									++i;
									if(i == len)
									{
										printw("Key Not Found!\nPlease Retry\n");
										getch();
										goto StarT;
									}
								}
								printw("Enter The Message To Be Decrypted > ");
								scanw(" %[^\n]",mess);
								char *chif = decryptCESAR(mess,key);
								attron(COLOR_PAIR(3) | A_BOLD);
								printw("\n\nIn Process To Decryption.../\n");
								attroff(COLOR_PAIR(3));
								printw("\nThe Decrypted Message Of %s Is %s\n\n",mess,chif);
								attron(COLOR_PAIR(4) | A_BOLD);
								refresh();
								attron(COLOR_PAIR(4));
								printw("\n\t\t\t<Enter>");
								getch();
								attroff(COLOR_PAIR(4));
								goto CESAR;
							}
							else
							{
								printw("Key Most Be A Single Caracter!\n\n");
								attron(COLOR_PAIR(4) | A_BOLD);
								printw("\t\t\t<enter>");
								getch();
								attroff(COLOR_PAIR(4) | A_BOLD);
								goto StarT;	
							}

						}
						break;
						case 0:
						{
							goto MENU;
						}
						break;
						default:
						{
							printw("Invalid Option!\n");
							attron(COLOR_PAIR(4) | A_BOLD);
							printw("\n\t\t\t<Enter>");
							getch();
						}
					}
				}
				break;
				case 4:
				{
					int dec;
					do
					{
						VIGENERE :
						ShowDescp();
						attron(A_BOLD);
						printw("\t\t\t[*********************** Vigenere Encryption System ***********************]\n");
						printw("\n\t\t\t\t\t0 --> Return\n\t\t\t\t\t1 --> Encrypt\n\t\t\t\t\t2 --> Decrypt\n\n\t\t\t\t\tChose an option : ");
						scanw(" %99[^\n]",test);
						refresh();
					}while(!veri_enter(test));
					dec = convert_enter(test);
					switch(dec)
					{
						case 1:
						{
							char mess[10000],key[10000];
							ShowDescp();
							printw("\t\t\t[*********************** Vigenere Encryption System ***********************]\n");
							Vigenere(mess,key);
							attron(COLOR_PAIR(4) | A_BOLD);
							printw("\t\t\t<Enter>");
							getch();
							attroff(COLOR_PAIR(4));
						}
						break;
						case 2:
						{
							char mess[1000],key[1000];
							do
							{
								ShowDescp();
								printw("\t\t\t[*********************** Vigenere Encryption System ***********************]\n\n");
								printw("Enter The Message To Be Encrypted > ");
								scanw(" %[^\n]",mess);
								printw("Enter The Encrypted Key > ");
								scanw(" %[^\n]",key);
								refresh();
							}while(strlen(key) >= strlen(mess));
							char *chif = decryVigenere(mess,key);
							attron(A_BOLD);
							printw("The Decrypted Message Of %s Is %s\n\n",mess,chif);
							attron(COLOR_PAIR(4));
							printw("\t\t\t<Enter>");
							getch();
							attroff(COLOR_PAIR(4));
						}
						break;
						case 0:
						{
							goto MENU;
						}
						break;
						default:
						{
							ShowDescp();
							attron(A_BOLD);
							printw("\t\t\t[*********************** Vigenere Encryption System ***********************]\n");
							printw("Invalid Option\n");
							attron(COLOR_PAIR(4) | A_BOLD);
							printw("\t\t\t<Enter>");
							getch();
							attroff(COLOR_PAIR(4));
							goto VIGENERE;
						}
					}
				}
				break;
				case 5:
				{
					int dec;
					VERNAM:
					ShowDescp();
					attron(A_BOLD);
					printw("\t\t\t[*********************** Vernam Encryption System ***********************]\n");
					do
					{
						ShowDescp();
						printw("\t\t\t[*********************** Vernam Encryption System ***********************]\n");
						printw("\n\t\t\t\t\t0 --> Return\n\t\t\t\t\t1 --> Encrypt\n\t\t\t\t\t2 --> Decrypt\n\n\t\t\t\t\tChoose an option : ");
						scanw(" %99[^\n]",test);
						refresh();
					}while(!veri_enter(test));

					dec = convert_enter(test);

					switch(dec)
					{
						case 1:
						{
							char mess[10000],key[10000];
							ShowDescp();
							printw("\t\t\t[*********************** Vernam Encryption System ***********************]\n");
							Vernam(mess,key);
							attron(COLOR_PAIR(4) | A_BOLD);
							printw("\n\t\t\t<Enter>");
							getch();
							goto VERNAM;
						}
						break;
						case 2:
						{
							char mess[10000],key[10000];
							do
							{
								ShowDescp();
								printw("\t\t\t[*********************** Vernam Encryption System ***********************]\n");
								printw("Enter The Message To Be Decrypted > ");
								scanw(" %9999[^\n]",mess);
								printw("Enter The Decryption Key > ");
								scanw(" %9999[^\n]",key);
								refresh();
							}while(strlen(mess) != strlen(key));
							char *chif = decryptVernam(mess,key);
							attron(COLOR_PAIR(3) | A_BOLD);
							printw("\nIn To Decryption.../\n");
							napms(2000);
							attroff(COLOR_PAIR(3));
							printw("The Decrypted Message Of %s Is %s\n",mess,chif);
							attron(COLOR_PAIR(4) | A_BOLD);
							printw("\n\t\t\t<Enter>");
							getch();
							refresh();
							goto VERNAM;
						}
						break;
						case 0:
						{
							goto MENU;
						}
						break;
						default:
						{
							printw("Invalid Option!\n");
							attron(COLOR_PAIR(4) | A_BOLD);
							printw("\n\t\t\t<Enter>");
							attroff(COLOR_PAIR(4));
							goto VERNAM;
						}
					}
				}
				break;
				case 6:
				{
					int dec;
					HILL:
					do
					{
						ShowDescp();
						attron(A_BOLD);
						printw("\t\t\t[*********************** Hill Encryption System ***********************]\n");
						printw("\n\t\t\t\t\t0 --> Return\n\t\t\t\t\t1 --> Encrypt\n\t\t\t\t\t2 --> Decrypt\n\t\t\t\t\t3 --> Help\n\n\t\t\t\t\tChoose an option : ");
						scanw(" %99[^\n]",test);
						refresh();
					}while(!veri_enter(test));
					dec = convert_enter(test);

					switch(dec)
					{
						case 1:
						{
							ShowDescp();
							printw("\t\t\t[*********************** Hill Encryption System ***********************]\n");
							refresh();
							HILL();
							attron(COLOR_PAIR(4) | A_BOLD);
							printw("\n\t\t\t<Enter>");
							getch();
							attroff(COLOR_PAIR(4));
							goto HILL;
						}
						break;
						case 2:
						{
							ShowDescp();
							printw("\t\t\t[*********************** Hill Encryption System ***********************]\n");
							printw("\nThis System Is Not Yet Updated!\n");
							attron(COLOR_PAIR(4) | A_BOLD);
							printw("\n\t\t\t<Enter>");
							getch();
							refresh();
							goto HILL;
						}
						break;
						case 3:
						{
							do
							{
								ShowDescp();
								attron(A_BOLD);
								printw("\t\t\t[*********************** Hill Encryption System ***********************]\n");
								printw("\n\t\t\t\t\t\t1 --> French version\n\t\t\t\t\t\t2 --> English version\n\t\t\t\t\t\t0 --> Return\n\n\t\t\t\t\t\tChoose an option : ");
								scanw(" %99[^\n]",test);
							}while(!veri_enter(test));

							int dec = convert_enter(test);
							switch(dec)
							{
								case 1:
								{
									char *path = "Help/HillHelpFr.txt";
									helpFr(path);
									printw("\t\t\t\t<Entrer>");
									getch();
									goto HILL;
								}
								break;
								case 2:
								{
									char *path = "Help/HillHelpEn.txt";
									helpEn(path);
									printw("\t\t\t\t<Enter>");
									getch();
									goto HILL;
								}
								break;
								case 0:
									goto HILL;
								break;
								default:
								{
									attron(COLOR_PAIR(4) | A_BOLD);
									printw("Invalid option :)\n\n\t\t\t<Enter>");
									getch();
									attroff(COLOR_PAIR(4));
									goto HILL;
								}
							}
						}
						break;
						case 0:
						{
							goto MENU;
						}
						break;
						default:
						{
							printw("\nInvalid Option!\n\n");
							attron(COLOR_PAIR(4) | A_BOLD);
							printw("\t\t\t<Enter>");
							getch();
							attroff(COLOR_PAIR(4));
							goto HILL;
						}
					}
				}
				break;
				case 7:
				{
					int dec;
					do
					{
						RECTANGULAR:
						ShowDescp();
						attron(A_BOLD);
						printw("\t\t\t[*********************** Rectangular Transposition Encryption System ***********************]\n");
						printw("\n\t\t\t0 --> Return\n\t\t\t1 --> Encrypt\n\t\t\t2 --> Decrypt\n\n\t\t\tChose an option : ");
						scanw(" %99[^\n]",test);
						refresh();
					}while(!veri_enter(test));
					dec = convert_enter(test);

					switch(dec)
					{
						case 1:
						{
							char mess[10000],key[10000];
							ShowDescp();
							attron(A_BOLD);
							printw("\t\t\t[*********************** Rectangular Transposition Encryption System ***********************]\n");
							do
							{
								ShowDescp();
								printw("\t\t\t[*********************** Rectangular Transposition Encryption System ***********************]\n");
								printw("Enter The Message To Be Encrypted > ");
								scanw(" %[^\n]",mess);
								printw("Enter The Encrypted Key > ");
								scanw(" %[^\n]",key);
								refresh();
							}while(strlen(key) > strlen(mess));

							char *chif = RecTranspos(mess, key);
							printw("The Encrypted Message Of %s Is %s\n\n",mess,chif);
							attron(COLOR_PAIR(4));
							printw("\n\t\t\t<Enter>");
							getch();
							attroff(COLOR_PAIR(4));
							goto RECTANGULAR;
						}
						break;
						case 2:
						{
							char mess[100000],key[100000];
							ShowDescp();
							do
							{
								ShowDescp();
								printw("\t\t\t[*********************** Rectangular Transposition Encryption System ***********************]\n");
								printw("Enter The Message To Be Decrypted > ");
								scanw(" %[^\n]",mess);
								printw("Enter The Decrypted Key > ");
								scanw(" %[^\n]",key);
								refresh();
							}while(strlen(key) > strlen(mess));
							decryptRectangular(mess,key);
							attron(COLOR_PAIR(4));
							printw("\n\t\t\t<Enter>");
							getch();
							attroff(COLOR_PAIR(4));
							goto RECTANGULAR;
						}
						break;
						case 0:
						{
							goto MENU;
						}
						break;
						default:
						{
							printw("Invalid Option!\n\n");
							attron(COLOR_PAIR(4));
							printw("\n\t\t\t<Enter>");
							getch();
							attroff(COLOR_PAIR(4));
							goto RECTANGULAR;
						}
					}
				}
				break;
				case 8:
				{
					ShowDescp();
					attron(A_BOLD);
					printw("\t\t\t[*********************** Feistel Encryption System ***********************]\n");
					int dec;
					char word[100];
					FeistelE : 
					do
					{
						ShowDescp();
						attron(A_BOLD);
						printw("\t\t\t[*********************** Feistel Encryption System ***********************]\n");
						printw("\n\t\t\t\t\t0 --> Return\n\t\t\t\t\t1 --> Encrypt\n\t\t\t\t\t2 --> Decrypt\n\t\t\t\t\t3 --> Help\n\n\t\t\t\t\tChose an option : ");
						scanw(" %99[^\n]",word);
						refresh();
					}while(!veri_enter(word));
					dec = convert_enter(word);
					switch(dec)
					{
						case 1 :
						{
							ShowDescp();
							attron(A_BOLD);
							printw("\t\t\t[*********************** Feistel Encryption System ***********************]\n");
							Feistel *node = NULL, *Key = NULL, *chif = NULL;
							char mess[1000],key[1000],op[50];
							printw("Enter The message to be encrypted > ");
							scanw(" %999[^\n]",mess);
							int len = strlen(mess);

							for(int i = 0; i < len; ++i)
								node = ConvertTobin(node,(int)mess[i]);
							printw("Message :) \n\n");
							Show(node);
							printw("\n\t\t\t<Enter>");
							getch();
							clear();
							refresh();
							int round;
							do
							{
								printw("Enter the number of round > ");
								scanw(" %99[^\n]",test);
							}while(!veri_enter(test));
							round = convert_enter(test);
							printw("Enter The encryption key > ");
							scanw(" %999[^\n]",key);
							int len1 = strlen(key);
							for(int i = 0; i < len1; ++i)
        						Key = ConvertTobin(Key, (int)key[i]);
							refresh();
    						printw("Key :) \n\n");
    						Show(Key);
							refresh();
							printw("\n\t\t\t<Enter>");
							getch();
							refresh();
							clear();
							int number = 0;
							printw("\n\nRound %d\n\n",number + 1);
							printw("Enter The Operator(XOR/OR/AND/C(~)) > ");
							scanw(" %49[^\n]",op);
							refresh();
							chif = feistel(node, Key, op);
							for(int i = 1; i < round; ++i)
							{
								refresh();
								number += 1;
								printw("Enter The Key For The Round %d > ",number + 1);
								scanw(" %999[^\n]",key);
								len1 = strlen(key);
								Key = FreeKey(Key);
								for (int i = 0; i < len1; ++i)
        							Key = ConvertTobin(Key, (int)key[i]);
								printw("Enter The Operator(XOR/OR/AND/C(~)) > ");
								scanw(" %49[^\n]",op);
								refresh();
								chif = feistel(node, Key, op);
								clear();
								refresh();
							}
							refresh();
    						printw("Encrypted message (Binary Format) :)\n\n");
    						ShowF(chif);

							printw("Encrypted message (String Format) :)\n\n");
							char Mess[1000];
							char *chifmess = ConvertToString(chif,Mess);
							len = strlen(chifmess);
							printw("%s\n",Mess);
							printw("\n");
							attron(COLOR_PAIR(4) | A_BOLD);
							printw("\t\t\t<Enter>");
							getch();
							chif = FreeKey(chif);
							attroff(COLOR_PAIR(4));
							refresh();
							goto FeistelE;
						}
						break;
						case 2:
						{
							ShowDescp();
							attron(A_BOLD);
							printw("\t\t\t[*********************** Feistel Encryption System ***********************]\n");
							Feistel *decrypt = NULL,*key = NULL,*node = NULL;
							char mess[1000],Key[1000],op[100];
							printw("Enter The Message To Be Decrypted > ");
							scanw(" %999[^\n]",mess);
							int len = strlen(mess);

							for(int i = 0; i < len; ++i)
								node = ConvertTobin(node,(int)mess[i]);
							printw("\nEncrypted Message :) \n");
							Show(node);
							int round;
							do
							{
								printw("Enter the number of round > ");
								scanw(" %99[^\n]",test);
							}while(!veri_enter(test));
							round = convert_enter(test);

							printw("\nEnter The Key  For the round 1 > ");
							scanw(" %999[^\n]",Key);
							len = strlen(Key);

							for(int i = 0; i < len; ++i)
								key = ConvertTobin(key,(int)Key[i]);
							int number = 0;
							printw("Key :) \n");
							Show(key);
							printw("Enter The Operator(XOR/OR/AND/C(~)) > ");
							scanw(" %99[^\n]",op);
							decrypt = feistel(node,key,op);

							for(int i = 1; i < round; ++i)
							{
								clear();
								refresh();
								number += 1;
								printw("Enter The Key For The Round %d > ",number + 1);
								scanw(" %999[^\n]",Key);
								len = strlen(Key);
								key = FreeKey(key);
								for (int i = 0; i < len; ++i)
        							key = ConvertTobin(key, (int)Key[i]);
								printw("Enter The Operator(XOR/OR/AND/C(~)) > ");
								scanw(" %49[^\n]",op);
								refresh();
								decrypt = feistel(node, key, op);
								clear();
								refresh();
							}
							clear();
							printw("Decrypted Message (Binary format) :) \n");
							ShowF(decrypt);
							printw("\nString format :) ");
							char Dechif[1000];
							char *dechimess = ConvertToString(decrypt,Dechif);
							printw("%s\n\n",dechimess);
							printw("\n\t\t\t<Enter>");
							getch();
							decrypt = FreeKey(decrypt);
							goto FeistelE;
						}
						break;
						case 3:
						{
							int dec;
							clear();
							do
							{
								ShowDescp();
								attron(A_BOLD);
								printw("\t\t\t[*********************** Feistel Encryption System ***********************]\n");
								attron(A_BOLD);
								printw("\t\t\t\t\t1 --> French Version\n\t\t\t\t\t2 --> English Version\n\t\t\t\t\t0 --> Return\n\n\t\t\t\t\tChose an option : ");
								scanw(" %99[^\n]",test);
							}while(!veri_enter(test));
							dec = convert_enter(test);
							switch(dec)
							{
								case 1:
								{
									clear();
									char *path = "Help/FeistelHelpFr.txt";
									helpFr(path);
									refresh();
									attron(COLOR_PAIR(4) | A_BOLD);
									printw("\n\t\t\t<Enter>");
									getch();
									attroff(COLOR_PAIR(4));
									goto FeistelE;
								}
								break;
								case 2:
								{
									clear();
									char *path = "Help/FeistelHelpEn.txt";
									helpEn(path);
									refresh();
									attron(COLOR_PAIR(4) | A_BOLD);
									printw("\n\t\t\t<Enter>");
									getch();
									attroff(COLOR_PAIR(4));
									goto FeistelE;
								}
								break;
								default :
								{
									printw("Invalid Option :)\n");
									attron(COLOR_PAIR(4) | A_BOLD);
									printw("\n\t\t\t<Enter>");
									getch();
									attroff(COLOR_PAIR(4));
									goto FeistelE;
								}
							}
						}
						case 0:
							goto MENU;
						default :
						{
							printw("Invalid Option :)\n");
							attron(COLOR_PAIR(4) | A_BOLD);
							printw("\n\t\t\t<Enter>");
							getch();
							attroff(COLOR_PAIR(4));
							goto FeistelE;
						}

					}
				}
				break;
				case 9:
				{
					ShowDescp();
					attron(A_BOLD);
					printw("\t\t\t[*********************** Playfair Encryption System ***********************]\n");
					printw("\nThis System Is Not Yet Updated!\n\n");
					attron(COLOR_PAIR(4));
					printw("\n\t\t\t<Enter>");
					getch();
					attroff(COLOR_PAIR(4));
					goto MENU;
				}
				break;
				case 0:
				{
					echo();
					refresh();
					endwin();
					goto Deb;
				}
				break;
				default:
				{
					printw("Invalid Option\n\n");
					attron(COLOR_PAIR(4));
					printw("\n\t\t\t<Enter>");
					refresh();
					getch();
					attroff(COLOR_PAIR(4));
					goto MENU;
				}
			}
		}while(1);

	}while(1);
}

