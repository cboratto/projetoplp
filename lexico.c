#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER 2048
char str[BUFFER];

char identifiedStringsVector[128][30]; //128 posicoes com 30 caracteres cada
int  idxIdentifiedStringVector=0;

static const char TOKEN_FILE[] = "token.txt";

int main() {
	cleanTokenFile('c');
	read();
    removeCommentLine();
    //printf("%s\n",str );
	char *pch;
	pch = strtok(str," ");
	while (pch!= NULL){
		//printf("%s\n", pch);
		tokenLibrary(pch);
		pch = strtok(NULL, " ");
	}

	return 0;
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
void read() {
	FILE *fp;
	char c;
	
	fp = fopen("file.txt", "r");
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
            tk[i]=='u' ||tk[i]=='v' ||tk[i]=='x' ||tk[i]=='z' ||tk[i]=='y' ||tk[i]=='w') 
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
