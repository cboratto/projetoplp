#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER 4196
char str[BUFFER];
char str3[BUFFER];

char identifiedStringsVector[128][30]; //128 posicoes com 30 caracteres cada
int  idxIdentifiedStringVector=0;

char tokenKey[2048][30];
char tokenValue[2048][30];
int  idxToken=0;
int  idxNextToken=0;

static const char TOKEN_FILE[] = "token.txt";
static const char SOURCE_FILE[] = "file.txt";

const char* getRecognizedKeyToken ();
const char* spreadTokenKeyValue(char *tk, int kv);
void addRecognizedToken(char* key, char *value);
void printRecognizedToken();
void tokenLibrary(char * tk);
int identifiedStrings( char * id );
void removeCommentLine();
void cleanTokenFile(char p);
void write(char *tk);
void read(char *filename);
void readToken();
void tokenLibrary(char * tk);


int main() {
	cleanTokenFile('c');
	read(SOURCE_FILE);
    removeCommentLine();
	char *pch;
	pch = strtok(str," ");
	while (pch!= NULL){
		tokenLibrary(pch);
		pch = strtok(NULL, " ");
	}

    //Inicia leitura dos tokens
    readToken();
    pch = strtok(str3," ");
    while (pch!= NULL){        
        addRecognizedToken(spreadTokenKeyValue(pch,0),spreadTokenKeyValue(pch,1));
        pch = strtok(NULL, " ");
    }
	//printRecognizedToken();    
    AnalisadorSintatico();

	return 0;
}

/*******************************************
    Recognized Tokens
*******************************************/
void addRecognizedToken(char* key, char *value) {
    strcpy(tokenKey[idxToken], key);
    strcpy(tokenValue[idxToken], value);
    idxToken++;
}

/*******************************************
    Print Recognized Tokens
*******************************************/
void printRecognizedToken() {
    int i=0;
    for (i=0; i < idxToken ; i ++) {
        printf("%s/%s\n", tokenKey[i],tokenValue[i] );
    }
}
/*******************************************
    get next
*******************************************/
const char* getRecognizedKeyToken(){
    char *tokenKey1 = malloc(30);
    strcpy(tokenKey1,tokenKey[idxNextToken]);
	return tokenKey1;
}
/*******************************************
    get next
*******************************************/
void nextRecognizedKeyToken (){
    if (idxNextToken>=idxToken){
		printf("Iterei ate o limite");
        return;
    }
    //char *tokenKey1 = malloc(30);
    //strcpy(tokenKey1,tokenKey[idxNextToken]);
    idxNextToken++;

}


/*******************************************
    Controla Vetor de strings validas     
*******************************************/
int identifiedStrings( char * id ){
  int i=0;
  char c[2];
  for (i=0; i< idxIdentifiedStringVector ; i++) {
    if (strcmp(identifiedStringsVector[i],id)==0) {
        i = i+1;
        //sprintf(c, "%d", i);
        //return c;
        return i;

    }
  }
  strcpy(identifiedStringsVector[idxIdentifiedStringVector], id);
  i = idxIdentifiedStringVector;
  idxIdentifiedStringVector++;

    i = i+1;
    //sprintf(c, "%d", i);
    //printf("%s\n", c);    
    //return c;
    return i;
}

/*******************************************
    Remove comentarios multline
*******************************************/
void removeCommentLine() {
    char strwithoutcomment[BUFFER];
    int i;
    int strwithoutcommentIDX=0;
    int ignorar=0;
    for (i=1; i < strlen(str); i++ ){        
        if ( str[i] == '*' && str[i-1]=='/') {
            //nao copia
            ignorar=1;
            //anda uma casa para tras no ponteiro para substituir o / que foi colocado
            strwithoutcommentIDX--;
            continue;
        }
        if (str[i] == '/' && str[i-1]=='*' && ignorar==1) {
            ignorar=0;
            continue;
        }

        if (ignorar!=1) {
            //copia
            //printf("%c", str[i]);
            strwithoutcomment[strwithoutcommentIDX] = str[i];
            strwithoutcomment[strwithoutcommentIDX+1] = '\0';
            strwithoutcommentIDX++;
        } 
    }
    strcpy(str,strwithoutcomment);
}

/*******************************************
	Cria o arquivo de TOKENs
*******************************************/
void cleanTokenFile(char p) {
   	FILE * fp;
	
    if ( p == 'd') {
        remove(TOKEN_FILE);
    }
    else {
        fp = fopen(TOKEN_FILE, "w+");
        fclose(fp);         
    }
	// todo exemplo

}

/*******************************************
	Função realiza append
	no arquivo de TOKEN 
*******************************************/
void write(char *tk) {
   	FILE * fp;
	
	// todo exemplo
	fp = fopen(TOKEN_FILE, "a");
	fprintf(fp, "%s\n",tk);
	fclose(fp);
}

/*******************************************
	Função realiza realiza a leitura
	e joga todo o arquivo em um buffer
*******************************************/
void read(char *filename) {
	FILE *fp;
	char c;
	
	fp = fopen(filename, "r");
	int ignorarLinha=0;
	while(1) {
		c = fgetc(fp);
      	if(feof(fp)){ 
         break;
      	}
      	
      	if(c != '\n' && ignorarLinha==0) {
            
            if ( c == '/' && str[strlen(str)-1]=='/') {
                //Caso ler um barra e o caracter anterior for barra, entao remove o caracter anterior
                //e liga ignorar resto da linha ate \n
                str[strlen(str)-1] = '\0';    
                ignorarLinha=1;
                continue;

            }
      		str[strlen(str)] = c;
      		str[strlen(str)+1] = '\0';

      	} else if (ignorarLinha==1 && c=='\n') {
            //quando encontrar \n com ignorarlinha ligado concatena espaço
            strcat(str, " ");
            ignorarLinha=0;

        } else if (ignorarLinha==1 & c!='\n') {
            //Caracteres que devem ser ignorados
            continue;
        }
        else {
      		strcat(str, " ");
      	}

	}
   	fclose(fp);
}

/*******************************************
    Separa os tokens em key,value
*******************************************/
const char* spreadTokenKeyValue (char *tk, int kv) {
    char *tokenKey = malloc(30);
    char *tokenValue = malloc(30);    
    //memset(tokenKey,0, 2048);
    //memset(tokenValue,0, 2048);
    int antesVirgula=1;
    int i=0;

    for (i=0; tk[i]!='\0'; i++){
        if (tk[i]=='<') {
            continue;
        } else if (tk[i]==',') {
            antesVirgula=0;
            continue;
        } else if (tk[i]=='>') {
            continue;
        } else {
            if (antesVirgula==1) {
                tokenKey[strlen(tokenKey)] = tk[i];
                tokenKey[strlen(tokenKey)+1] = '\0';
            } else {
                tokenValue[strlen(tokenValue)] = tk[i];
                tokenValue[strlen(tokenValue)+1] = '\0';
            }
        }

    }
    if (kv ==0 ) {
        return tokenKey;
    } else if (kv==1) {
        return tokenValue;
    }

}
/*******************************************
    Função realiza realiza a leitura
    e joga todo o arquivo em um buffer
*******************************************/
void readToken() {
    FILE *fp;
    char c;
    
    fp = fopen(TOKEN_FILE, "r");
    
    int ignorarlinha=0;

    while(1) {
        c = fgetc(fp);
        if(feof(fp)){ 
         break;
        }
        
        if(c != '\n' ) {            
            str3[strlen(str3)] = c;
            str3[strlen(str3)+1] = '\0';
        }
            
        else  {
            strcat(str3, " ");
        }
    }

    fclose(fp);
}

/*******************************************
    Sintaxe
*******************************************/

void AnalisadorSintatico() {
    goto MAIN;
    
	CLASSE: 
		if (strcmp(getRecognizedKeyToken(),"AC")==0) {
			nextRecognizedKeyToken();
			if (strcmp(getRecognizedKeyToken(),"extends")==0) {
				nextRecognizedKeyToken();
				if (strcmp(getRecognizedKeyToken(),"id")==0) {
					nextRecognizedKeyToken();
					if (strcmp(getRecognizedKeyToken(),"ACH")==0) {
						printf("teste 2");
					} else {
						//ach
						printf("[ERRO SINTATICO][18] Esperado ACH. Encontrado %s\n",getRecognizedKeyToken());
					}
				} else {
					//id
					printf("[ERRO SINTATICO][17] Esperado id. Encontrado %s\n",getRecognizedKeyToken());
				}
			} else {
				//extends
				printf("[ERRO SINTATICO][16] Esperado extends. Encontrado %s\n",getRecognizedKeyToken());
			}
		} else {
			//AC
			printf("[ERRO SINTATICO][15] Esperado AC. Encontrado %s\n",getRecognizedKeyToken());
			
		}

    MAIN: 
		if (strcmp(getRecognizedKeyToken(),"class")==0) {
			nextRecognizedKeyToken();
			if (strcmp(getRecognizedKeyToken(),"id")==0) {
				nextRecognizedKeyToken();
				if (strcmp(getRecognizedKeyToken(),"AC")==0) {
					goto CLASSE;
				} else if (strcmp(getRecognizedKeyToken(),"ACH")==0) {
					nextRecognizedKeyToken();
					if (strcmp(getRecognizedKeyToken(),"public")==0) {
						nextRecognizedKeyToken();
						if (strcmp(getRecognizedKeyToken(),"static")==0)  {
							nextRecognizedKeyToken();
							if (strcmp(getRecognizedKeyToken(),"void")==0) {
								nextRecognizedKeyToken();
								if (strcmp(getRecognizedKeyToken(),"main")==0) {
									nextRecognizedKeyToken();
									if (strcmp(getRecognizedKeyToken(),"AP")==0) {
										nextRecognizedKeyToken();
										if (strcmp(getRecognizedKeyToken(),"id")==0) {
											nextRecognizedKeyToken();
											if (strcmp(getRecognizedKeyToken(),"AC")==0) {
												nextRecognizedKeyToken();
												if (strcmp(getRecognizedKeyToken(),"FC")==0) {
													nextRecognizedKeyToken();
													if (strcmp(getRecognizedKeyToken(),"FP")==0){
														nextRecognizedKeyToken();
														if (strcmp(getRecognizedKeyToken(),"ACH")==0){
															nextRecognizedKeyToken();
                                                            //CMD
															CMD: 
                                                                if (strcmp(getRecognizedKeyToken(),"System.out.println")==0) {
                                                                    nextRecognizedKeyToken();
                                                                    if (strcmp(getRecognizedKeyToken(),"AP")==0) {
                                                                        nextRecognizedKeyToken();
                                                                        if (strcmp(getRecognizedKeyToken(),"new")==0) {
                                                                            nextRecognizedKeyToken();
                                                                            if (strcmp(getRecognizedKeyToken(),"id")==0) {
                                                                                nextRecognizedKeyToken();
                                                                                if (strcmp(getRecognizedKeyToken(),"AP")==0) {
                                                                                    nextRecognizedKeyToken();
                                                                                    if (strcmp(getRecognizedKeyToken(),"FP")==0) {
                                                                                        nextRecognizedKeyToken();
                                                                                        if (strcmp(getRecognizedKeyToken(),"PONTO")==0) {
                                                                                            nextRecognizedKeyToken();
                                                                                            if (strcmp(getRecognizedKeyToken(),"id")==0) {
                                                                                                nextRecognizedKeyToken();
                                                                                                if (strcmp(getRecognizedKeyToken(),"AP")==0) {
                                                                                                    nextRecognizedKeyToken();
                                                                                                    if (strcmp(getRecognizedKeyToken(),"num")==0) {
                                                                                                        nextRecognizedKeyToken();
                                                                                                        if (strcmp(getRecognizedKeyToken(),"FP")==0) {
                                                                                                            nextRecognizedKeyToken();
                                                                                                            if (strcmp(getRecognizedKeyToken(),"FP")==0) {
                                                                                                                nextRecognizedKeyToken();
                                                                                                                if (strcmp(getRecognizedKeyToken(),"PV")==0) {
                                                                                                                    goto CMD;
                                                                                                                } else {
                                                                                                                    printf("[ERRO SINTATICO][29] Esperado PV. Encontrado %s\n",getRecognizedKeyToken());
                                                                                                                }                                                                                                                
                                                                                                            } else {
                                                                                                                printf("[ERRO SINTATICO][29] Esperado FP. Encontrado %s\n",getRecognizedKeyToken());
                                                                                                            }
                                                                                                        } else {
                                                                                                            printf("[ERRO SINTATICO][28] Esperado FP. Encontrado %s\n",getRecognizedKeyToken());
                                                                                                        }
                                                                                                    } else {
                                                                                                        printf("[ERRO SINTATICO][27] Esperado num. Encontrado %s\n",getRecognizedKeyToken());
                                                                                                    }
                                                                                                } else {
                                                                                                    printf("[ERRO SINTATICO][26] Esperado AP. Encontrado %s\n",getRecognizedKeyToken());
                                                                                                }
                                                                                            } else { 
                                                                                                printf("[ERRO SINTATICO][25] Esperado id. Encontrado %s\n",getRecognizedKeyToken());
                                                                                            }
                                                                                        } else {
                                                                                            printf("[ERRO SINTATICO][24] Esperado PONTO. Encontrado %s\n",getRecognizedKeyToken());
                                                                                        }
                                                                                    } else {
                                                                                        printf("[ERRO SINTATICO][23] Esperado FP. Encontrado %s\n",getRecognizedKeyToken());
                                                                                    }
                                                                                } else {
                                                                                    printf("[ERRO SINTATICO][22] Esperado AP. Encontrado %s\n",getRecognizedKeyToken());
                                                                                }
                                                                            } else {
                                                                                printf("[ERRO SINTATICO][21] Esperado id. Encontrado %s\n",getRecognizedKeyToken());
                                                                            }
                                                                        } else {
                                                                            printf("[ERRO SINTATICO][20] Esperado new. Encontrado %s\n",getRecognizedKeyToken());
                                                                        }
                                                                    } else {
                                                                        printf("[ERRO SINTATICO][19] Esperado AP. Encontrado %s\n",getRecognizedKeyToken());
                                                                    }
                                                                //DECLARACAO DE VARIAVEL(IS)
                                                                } else if (strcmp(getRecognizedKeyToken(),"if")==0)  {
                                                                    nextRecognizedKeyToken();
                                                                    if (strcmp(getRecognizedKeyToken(),"AP")==0) {
                                                                        COND:
                                                                        if (strcmp(getRecognizedKeyToken(),"num")==0) {
                                                                            if (strcmp(getRecognizedKeyToken(),"EQ")==0 || (strcmp(getRecognizedKeyToken(),"LT")==0) ) {
                                                                                if (strcmp(getRecognizedKeyToken(),"num")==0) {
                                                                                    if (strcmp(getRecognizedKeyToken(),"AND")==0||strcmp(getRecognizedKeyToken(),"OR")==0) {
                                                                                        goto COND;
                                                                                    } else if (strcmp(getRecognizedKeyToken(),"FP")==0) {
                                                                                        if (strcmp(getRecognizedKeyToken(),"ACH")==0) {
                                                                                            goto CMD;
                                                                                        } 

                                                                                    } else {
                                                                                        printf("[ERRO SINTATICO][34] Esperado FP. Encontrado %s\n",getRecognizedKeyToken());
                                                                                    }
                                                                                } else {
                                                                                    //esperava num
                                                                                    printf("[ERRO SINTATICO][33] Esperado num. Encontrado %s\n",getRecognizedKeyToken());
                                                                                }
                                                                            } else {
                                                                                //esperava comparacao
                                                                                printf("[ERRO SINTATICO][32] Esperado EQ, LT. Encontrado %s\n",getRecognizedKeyToken());
                                                                            }
                                                                        } else {
                                                                            //num
                                                                            printf("[ERRO SINTATICO][31] Esperado num. Encontrado %s\n",getRecognizedKeyToken());
                                                                        }
                                                                    } else {
                                                                        //AP
                                                                        printf("[ERRO SINTATICO][30] Esperado AP. Encontrado %s\n",getRecognizedKeyToken());
                                                                    }
                                                                                                                           
                                                                }
                                                                // IF 
                                                                else if (strcmp(getRecognizedKeyToken(),"PV")==0)  {

                                                                }
                                                                //WHILE
                                                                else if (strcmp(getRecognizedKeyToken(),"PV")==0) {

                                                                }

                                                                //CMD
														} else {															
															printf("[ERRO SINTATICO][13] Esperado ACH. Encontrado %s\n",getRecognizedKeyToken());
														}
													} else {														
														printf("[ERRO SINTATICO][12] Esperado FP. Encontrado %s\n",getRecognizedKeyToken());
													}
												} else {
													printf("[ERRO SINTATICO][11] Esperado FC. Encontrado %s\n",getRecognizedKeyToken());
												}
											} else {
												printf("[ERRO SINTATICO][10] Esperado AC. Encontrado %s\n",getRecognizedKeyToken());
											}
										} else {
											printf("[ERRO SINTATICO][9] Esperado id. Encontrado %s\n",getRecognizedKeyToken());
										}
									} else {
										printf("[ERRO SINTATICO][8] Esperado AP. Encontrado %s\n",getRecognizedKeyToken());
									}
								} else {
									printf("[ERRO SINTATICO][7] Esperado main. Encontrado %s\n",getRecognizedKeyToken());
								}
							} else {
								printf("[ERRO SINTATICO][6] Esperado void. Encontrado %s\n",getRecognizedKeyToken());
							}
						} else {
							printf("[ERRO SINTATICO][5] Esperado static. Encontrado %s\n",getRecognizedKeyToken());
						}
					} else {
						printf("[ERRO SINTATICO][4] Esperado public. Encontrado %s\n",getRecognizedKeyToken());
					}
				} else {
					printf("[ERRO SINTATICO][3] Esperado ACH. Encontrado %s\n",getRecognizedKeyToken());
				}
			} else {
				printf("[ERRO SINTATICO][2] Esperado id. Encontrado %s\n",getRecognizedKeyToken());
			}
		} else {
			printf("[ERRO SINTATICO][1] Esperado class. Encontrado %s\n",getRecognizedKeyToken());
		}
        
        
            
}


/*******************************************
	Biblioteca de TOKENs
*******************************************/
void tokenLibrary(char * tk) {
	//
	// PALAVRAS RESERVADAS
	//
	if (strcmp("if",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<if>");
        return;
	} else if (strcmp("while",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<while>");
        return;
	} else if (strcmp("this",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<this>");
        return;
	} else if (strcmp("new",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<new>");
        return;
	} else if (strcmp("else",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<else>");
        return;
	} else if (strcmp("System.out.println",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<System.out.println>");
        return;
	} else if (strcmp("boolean",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<boolean>");
        return;
	} else if (strcmp("class",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<class>");
        return;
	} else if (strcmp("extends",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<extends>");
        return;
	} else if (strcmp("public",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<public>");
        return;
	} else if (strcmp("static",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<static>");
        return;
	} else if (strcmp("void",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<void>");
        return;
	} else if (strcmp("main",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<main>");
        return;
	} else if (strcmp("return",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<return>");
        return;
	} else if (strcmp("int",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<int>");
        return;
	}
	//
	// PONTUACAO
	//
	else if (strcmp("(",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<AP>");		
        return;
	} else if (strcmp(")",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<FP>");		
        return;
	} else if (strcmp("[",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<AC>");		
        return;
	} else if (strcmp("]",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<FC>");		
        return;
	} else if (strcmp("{",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<ACH>");		
        return;
	} else if (strcmp("}",tk)==0) {		
		write("<FCH>");		
        return;
	} else if (strcmp(".",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<PONTO>");		
        return;
	} else if (strcmp(",",tk)==0) {
        //printf("RECONHECIDO: %s \n", tk );
        write("<VIRG>");       
        return;
    } else if (strcmp(";",tk)==0) {
        //printf("RECONHECIDO: %s \n", tk );
        write("<PV>");       
        return;
    }
	//
	// OPERADORES
	//
	else if (strcmp("==",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<EQ>");		
        return;
	} else if (strcmp("&&",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<AND>");
        return;
	} else if (strcmp("-",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<MINUS>");		
        return;
	} else if (strcmp("+",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<PLUS>");		
        return;
	} else if (strcmp("*",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<MULT>");		
        return;
	} else if (strcmp("!",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<NOT>");		
        return;
	} else if (strcmp("=",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<ATR>");		
        return;
	} else if (strcmp("!=",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<DIF>");		
        return;
	} else if (strcmp("<",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<LT>");		
        return;
	}
    //
    // NUMEROS
    //  
    int i;
    char number[1024];
    //Limpa area de memoria. Necessario para concatenacao de Numero realizada mais abaixo
    memset(number,0, 1024);
    int index=0;
    int totalTimesCountNumber=0;
    int totalTimesIterate=0;
    


    for (i=0; tk[i]!='\0'; i++){        
        if (tk[i]=='0') {   
            number[index++]=tk[i];
            totalTimesCountNumber++;

        } else if (tk[i]=='1') {
            number[index++]=tk[i];
            totalTimesCountNumber++;

        } else if (tk[i]=='2') {
            number[index++]=tk[i];
            totalTimesCountNumber++;

        } else if (tk[i]=='3') {
            number[index++]=tk[i];
            totalTimesCountNumber++;

        } else if (tk[i]=='4') {
            number[index++]=tk[i];
            totalTimesCountNumber++;

        } else if (tk[i]=='5') {
            number[index++]=tk[i];
            totalTimesCountNumber++;

        } else if (tk[i]=='6') {
            number[index++]=tk[i];
            totalTimesCountNumber++;

        } else if (tk[i]=='7') {
            number[index++]=tk[i];
            totalTimesCountNumber++;

        } else if (tk[i]=='8') {
            number[index++]=tk[i];
            totalTimesCountNumber++;

        } else if (tk[i]=='9') {
            number[index++]=tk[i];
            totalTimesCountNumber++;
        } 
        totalTimesIterate++;
    }

    if (totalTimesCountNumber==totalTimesIterate) {
        char n[1024];
        strcpy(n, "<num,");
        strcat(n, number);
        strcat(n, ">"); 
        write(n); 
        //identificou numero, portanto, deve parar execucao
        return;
    }
    //
    // VARIAVEIS
    //
    int primeiraLeitura=1;
    char variavel[1024];
    index=0;
    memset(variavel,0,1024);
    for (i=0; tk[i]!='\0'; i++){
        if (tk[i]=='a' || tk[i]=='b' ||tk[i]=='c' ||tk[i]=='d' ||tk[i]=='e' ||tk[i]=='f' ||tk[i]=='g' ||
            tk[i]=='h' ||tk[i]=='i' ||tk[i]=='j' ||tk[i]=='k' ||tk[i]=='l' ||tk[i]=='m' ||tk[i]=='n' ||
            tk[i]=='o' ||tk[i]=='p' ||tk[i]=='q' ||tk[i]=='r' ||tk[i]=='r' ||tk[i]=='s' ||tk[i]=='t' ||
            tk[i]=='u' ||tk[i]=='v' ||tk[i]=='x' ||tk[i]=='z' ||tk[i]=='y' ||tk[i]=='w' ||
            tk[i]=='A' || tk[i]=='B' ||tk[i]=='C' ||tk[i]=='D' ||tk[i]=='E' ||tk[i]=='F' ||tk[i]=='G' ||
            tk[i]=='H' ||tk[i]=='I' ||tk[i]=='J' ||tk[i]=='K' ||tk[i]=='L' ||tk[i]=='M' ||tk[i]=='N' ||
            tk[i]=='O' ||tk[i]=='P' ||tk[i]=='Q' ||tk[i]=='R' ||tk[i]=='R' ||tk[i]=='S' ||tk[i]=='T' ||
            tk[i]=='U' ||tk[i]=='V' ||tk[i]=='X' ||tk[i]=='Z' ||tk[i]=='Y' ||tk[i]=='W' 
            ) 
        {
            //
            primeiraLeitura=0;
            //
            variavel[index++]=tk[i];

        } else if (tk[i]=='0'||tk[i]=='1'||tk[i]=='2'||tk[i]=='3'||tk[i]=='4'||tk[i]=='5'||tk[i]=='6'||
                    tk[i]=='7'||tk[i]=='8'||tk[i]=='9'|| tk[i]=='_')
        {
            if (primeiraLeitura==1){
                //Leu um caracter diferente de ALPHA como primeiro caracter entao nao é variavel
                printf("ERRO LEXICO: %s\n", tk);
                exit(-1);
            }
            primeiraLeitura=0;
            variavel[index++]=tk[i];

        } else {
            printf("ERRO LEXICO: %s\n", tk);
            exit(-1);
        }

    }
    char n[1024];
    int idIndex =identifiedStrings(variavel);
    char idIndexString[2];
    sprintf(idIndexString, "%d", idIndex);
    strcpy(n, "<id,");
    strcat(n, idIndexString);
    strcat(n, ">"); 
    write(n);   
    return; 

}
