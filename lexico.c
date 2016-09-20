#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char str[1000];
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
		printf("RECONHECIDO: %s \n", tk );
		write(tk);
	} else if (strcmp("while",tk)==0) {
		printf("RECONHECIDO: %s \n", tk );
		write(tk);
	} else if (strcmp("this",tk)==0) {
		printf("RECONHECIDO: %s \n", tk );
		write(tk);
	} else if (strcmp("new",tk)==0) {
		printf("RECONHECIDO: %s \n", tk );
		write(tk);
	} else if (strcmp("else",tk)==0) {
		printf("RECONHECIDO: %s \n", tk );
		write(tk);
	} else if (strcmp("System.out.println",tk)==0) {
		printf("RECONHECIDO: %s \n", tk );
		write(tk);
	} else if (strcmp("boolean",tk)==0) {
		printf("RECONHECIDO: %s \n", tk );
		write(tk);
	} else if (strcmp("class",tk)==0) {
		printf("RECONHECIDO: %s \n", tk );
		write(tk);
	} else if (strcmp("extends",tk)==0) {
		printf("RECONHECIDO: %s \n", tk );
		write(tk);
	} else if (strcmp("public",tk)==0) {
		printf("RECONHECIDO: %s \n", tk );
		write(tk);
	} else if (strcmp("static",tk)==0) {
		printf("RECONHECIDO: %s \n", tk );
		write(tk);
	} else if (strcmp("void",tk)==0) {
		printf("RECONHECIDO: %s \n", tk );
		write(tk);
	} else if (strcmp("main",tk)==0) {
		printf("RECONHECIDO: %s \n", tk );
		write(tk);
	} else if (strcmp("return",tk)==0) {
		printf("RECONHECIDO: %s \n", tk );
		write(tk);
	} else if (strcmp("int",tk)==0) {
		printf("RECONHECIDO: %s \n", tk );
		write(tk);
	}
	//
	// PONTUACAO
	//
	else if (strcmp("(",tk)==0) {
		printf("RECONHECIDO: %s \n", tk );
		write(tk);		
	} else if (strcmp(")",tk)==0) {
		printf("RECONHECIDO: %s \n", tk );
		write(tk);		
	} else if (strcmp("[",tk)==0) {
		printf("RECONHECIDO: %s \n", tk );
		write(tk);		
	} else if (strcmp("]",tk)==0) {
		printf("RECONHECIDO: %s \n", tk );
		write(tk);		
	} else if (strcmp("{",tk)==0) {
		printf("RECONHECIDO: %s \n", tk );
		write(tk);		
	} else if (strcmp("}",tk)==0) {
		printf("RECONHECIDO: %s \n", tk );
		write(tk);		
	} else if (strcmp(".",tk)==0) {
		printf("RECONHECIDO: %s \n", tk );
		write(tk);		
	} else if (strcmp(",",tk)==0) {
		printf("RECONHECIDO: %s \n", tk );
		write(tk);		
	}
	//
	// OPERADORES
	//
	else if (strcmp("==",tk)==0) {
		printf("RECONHECIDO: %s \n", tk );
		write(tk);		
	} else if (strcmp("&&",tk)==0) {
		printf("RECONHECIDO: %s \n", tk );
		write(tk);		
	} else if (strcmp("-",tk)==0) {
		printf("RECONHECIDO: %s \n", tk );
		write(tk);		
	} else if (strcmp("+",tk)==0) {
		printf("RECONHECIDO: %s \n", tk );
		write(tk);		
	} else if (strcmp("*",tk)==0) {
		printf("RECONHECIDO: %s \n", tk );
		write(tk);		
	} else if (strcmp("!",tk)==0) {
		printf("RECONHECIDO: %s \n", tk );
		write(tk);		
	} else if (strcmp("=",tk)==0) {
		printf("RECONHECIDO: %s \n", tk );
		write(tk);		
	} else if (strcmp("!=",tk)==0) {
		printf("RECONHECIDO: %s \n", tk );
		write(tk);		
	} else if (strcmp("<",tk)==0) {
		printf("RECONHECIDO: %s \n", tk );
		write(tk);		
	} 
	//
	// NUMEROS
	//	
	int i;
	char number[1024];
	int index=0;

	for (i=0; tk[i]!='\n'; i++){		
		if (tk[i]=='0') {	
			number[index++]=tk[i];

		} else if (tk[i]=='1') {
			number[index++]=tk[i];

		} else if (tk[i]=='2') {
			number[index++]=tk[i];

		} else if (tk[i]=='3') {
			number[index++]=tk[i];

		} else if (tk[i]=='4') {
			number[index++]=tk[i];

		} else if (tk[i]=='5') {
			number[index++]=tk[i];

		} else if (tk[i]=='6') {
			number[index++]=tk[i];

		} else if (tk[i]=='7') {
			number[index++]=tk[i];

		} else if (tk[i]=='8') {
			number[index++]=tk[i];

		} else if (tk[i]=='9') {
			number[index++]=tk[i];
		} else {
			break;
		}
	}
	//if (isNumber==1) {
		//number[index++]='\n';
		printf("numero reconhecido %s\n",number);		
	//}



}
