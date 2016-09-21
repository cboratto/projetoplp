#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char str[2048];
static const char TOKEN_FILE[] = "filew.txt";

int main() {
	cleanTokenFile();
	read();
	//printf(str);
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
	Cria o arquivo de TOKENs
*******************************************/
void cleanTokenFile() {
   	FILE * fp;
	
	// todo exemplo
	fp = fopen(TOKEN_FILE, "w+");
	fclose(fp);	
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
	
	while(1) {
		c = fgetc(fp);
      	if(feof(fp)){ 
         break;
      	}
      	
      	if(c != '\n') {
      		str[strlen(str)] = c;
      		str[strlen(str)+1] = '\0';
      	}else {
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
	} else if (strcmp("while",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<while>");
	} else if (strcmp("this",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<this>");
	} else if (strcmp("new",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<new>");
	} else if (strcmp("else",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<else>");
	} else if (strcmp("System.out.println",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<System.out.println>");
	} else if (strcmp("boolean",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<boolean>");
	} else if (strcmp("class",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<class>");
	} else if (strcmp("extends",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<class>");
	} else if (strcmp("public",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<public>");
	} else if (strcmp("static",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<static>");
	} else if (strcmp("void",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<void>");
	} else if (strcmp("main",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<main>");
	} else if (strcmp("return",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<return>");
	} else if (strcmp("int",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<int>");
	}
	//
	// PONTUACAO
	//
	else if (strcmp("(",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<AP>");		
	} else if (strcmp(")",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<FP>");		
	} else if (strcmp("[",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<AC>");		
	} else if (strcmp("]",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<FC>");		
	} else if (strcmp("{",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<ACH>");		
	} else if (strcmp("}",tk)==0) {
		printf("RECONHECIDO: %s \n", tk );
		write("<FCH>");		
	} else if (strcmp(".",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<.>");		
	} else if (strcmp(",",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<,>");		
	}
	//
	// OPERADORES
	//
	else if (strcmp("==",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<OP,EQ>");		
	} else if (strcmp("&&",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<OP,AND>");
	} else if (strcmp("-",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<OP,MINUS>");		
	} else if (strcmp("+",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<OP,PLUS>");		
	} else if (strcmp("*",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<OP,MULT>");		
	} else if (strcmp("!",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<OP,NOT>");		
	} else if (strcmp("=",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<OP,ATR>");		
	} else if (strcmp("!=",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<OP,DIF>");		
	} else if (strcmp("<",tk)==0) {
		//printf("RECONHECIDO: %s \n", tk );
		write("<OP,LT>");		
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
        }
}
