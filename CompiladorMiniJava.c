#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER 4196
#define TRUE 1
#define FALSE 0

char str[BUFFER];
char str3[BUFFER];

char identifiedStringsVector[128][30]; //128 posicoes com 30 caracteres cada
int  idxIdentifiedStringVector=0;

char tokenKey[2048][30];
char tokenValue[2048][30];
int  idxToken=0;
int  idxTempToken=0;

static const char TOKEN_FILE[] = "token.txt";
static const char SOURCE_FILE[] = "file.txt";

const char* getRecognizedKeyToken ();
 char* spreadTokenKeyValue(char *tk, int kv);
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
    strcpy(tokenKey1,tokenKey[idxTempToken]);
	return tokenKey1;
}

const char* getRecognizedValueToken(){
    char *tokenValue1 = malloc(30);
    strcpy(tokenValue1,tokenValue[idxTempToken]);
    return tokenValue1;
}
/*******************************************
    get next
*******************************************/
void nextRecognizedKeyToken (){
    if (idxTempToken>=idxToken){
		printf("Iterei ate o limite");
        return;
    }

    char *tokenKeyValye =malloc(100);
    strcpy(tokenKeyValye,tokenKey[idxTempToken]);
    strcat(tokenKeyValye," | ");
    strcat(tokenKeyValye,tokenValue[idxTempToken]);
    
    printf("\tindex: %d -> %s\n",idxTempToken, tokenKeyValye);
    idxTempToken++;

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
 char* spreadTokenKeyValue (char *tk, int kv) {
    char *tokenKey = malloc(30);
    char *tokenValue = malloc(30);    
	//Diretiva para WINDOWS
	//memset adicionado para garantir que nao seja referenciado espacos de memorias pre alocados
    memset(tokenKey,0, 30);
    memset(tokenValue,0, 30);
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
				//strcat(tokenKey, tk[i]+0);
                //printf("%s\n", tokenKey);
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
    Pilha de controle para posicao do vetor
    de tokens reconhecidos
*******************************************/
int idxStack=0;

struct Stack {
   int start;
   int current;
};

struct Stack stack[128];


/*******************************************
    Pilha para log de mensagens
*******************************************/
int idxStackLog=0;
int idxStackLogPop=0;

struct StackLog {
   char mensagem[2048];
   int current;
};
struct StackLog stackLog[128];

void pushLog(char* funcao, char* esperado) {
    char  mensagemFinal[2048];

    strcpy(mensagemFinal,funcao);
    strcat(mensagemFinal," Esperado ");
    strcat(mensagemFinal,esperado);
    strcat(mensagemFinal,". Recebido ");
    strcat(mensagemFinal,tokenKey[getCurrentPosOnStack()]);    
    strcpy(stackLog[idxStackLog].mensagem,mensagemFinal);
    stackLog[idxStackLog].current = getCurrentPosOnStack();
    
    idxStackLog++;
}

int popLog(){        
    if (idxStackLog==1){
        return FALSE;
    }
    char currentTempString[30];
    sprintf(currentTempString, "%d", stackLog[idxStackLog].current);

    char  mensagemFinal[2048];
    strcpy(mensagemFinal,"Posicao ");
    strcat(mensagemFinal,currentTempString);
    strcat(mensagemFinal,": ");
    strcat(mensagemFinal,stackLog[idxStackLog].mensagem);
    idxStackLog--;
    printf("%s\n",mensagemFinal );
    return TRUE;
}

/*******************************************
    Pilha de controle para posicao do vetor
    de tokens reconhecidos
*******************************************/
int match(char* tk, char* word){
    if (strcmp(tk,word)==0) {
        return TRUE;
    } else {
        return FALSE;
    }
}


void update(int newvalue) {
    //printf("update - current %d\n",newvalue);
    stack[idxStack].current=newvalue;
}

void increment() {
    //printf("increment - atualizando current para %d\n",stack[idxStack].current+1 );
    stack[idxStack].current=stack[idxStack].current+1;

}

void push(int vstart, int vcurrent ) {    
    idxStack++;
    printf("push \n\tstart: %d\n\tcurrent: %d\n\tidxStack: %d\n",vstart,vcurrent,idxStack );
    stack[idxStack].start=vstart;
    stack[idxStack].current=vcurrent;

    
}

void pop() {
    //printf("pop %d \n",idxStack );
    if (idxStack<0) {
        printf("[ERRO]deu ruim na pilha\n");
        exit(-1);
    }
    idxStack--;
}

int getCurrentPosOnStack(){
    return stack[idxStack].current;
}


int lookahead(char* word) {

    if (match(tokenKey[getCurrentPosOnStack()],word)) {
        printf("LIDO: %s\n",tokenKey[getCurrentPosOnStack()] );
        increment();
        return TRUE;
    } else {
        printf("ESPERADO: %s | LIDO %s\n",word,tokenKey[getCurrentPosOnStack()] );
        return FALSE;
    }
}

void nonTerminalStart() {
    push(stack[idxStack].current,stack[idxStack].current);
}

void nonTerminalError() {
    pop();
    push(stack[idxStack].current,stack[idxStack].current);
}

int nonTerminalRefuse() {
    pop();
    return FALSE;
}

int nonTerminalAccept() {
    int newCurrentPosition=getCurrentPosOnStack();
    pop();
    update(newCurrentPosition);

    return TRUE;
}


int PARAMS() {

    nonTerminalStart();

    if (lookahead("int") ||lookahead("boolean") ) {
        if (lookahead("id") ) {
            return nonTerminalAccept();
        } else {
            pushLog("[PARAMS]", "id");
            nonTerminalError();
        }
    } else {
        pushLog("[PARAMS]", "int ou boolean");
        nonTerminalError();
    }
}

int VAR() {
    nonTerminalStart();

    if (lookahead("int") ) {
        if (lookahead("id") ) {
            if (lookahead("PV") ) {
                return nonTerminalAccept();
            } else {
                pushLog("[VAR]", "PV");
                nonTerminalError();
            }
        } else {
            pushLog("[VAR]", "id");
            nonTerminalError();
        }
    } else {
        pushLog("[VAR]", "int");
        nonTerminalError();
    }
    if (lookahead("boolean") ) {
        if (lookahead("id") ) {
            if (lookahead("PV") ) {
                return nonTerminalAccept();
            } else {
                pushLog("[VAR]", "PV");
                nonTerminalError();
            }
        } else {
            pushLog("[VAR]", "id");
            nonTerminalError();
        }
    } else {
        pushLog("[VAR]", "boolean");
        nonTerminalError();
    }

    pushLog("[VAR]", "<nenhuma das derivacoes foi identificada>");
    return nonTerminalRefuse();
}


int METODO () {
    nonTerminalStart();
    if (lookahead("public") ) {
        if (lookahead("int") || lookahead("boolean")  ) {
            if (lookahead("id") ) {
                if (lookahead("AP") ) {
                    if (PARAMS() ) {
                        if (lookahead("FP") ) {
                            if (lookahead("ACH") ) {
                                METODO_VAR:
                                if (VAR() ) {
                                    goto METODO_VAR;
                                } else {
                                    METODO_RETENTA_COMANDO: 
                                    if (CMD()) {
                                        goto METODO_RETENTA_COMANDO;
                                    } else {
                                        if (lookahead("return") ) {
                                            if (EXP() ) {
                                                if (lookahead("PV") ) {
                                                    if (lookahead("FCH") ) {
                                                        return nonTerminalAccept();
                                                    } else {
                                                        pushLog("[METODO]", "FCH");
                                                        nonTerminalError();
                                                    }
                                                } else {
                                                    pushLog("[METODO]", "PV");
                                                    nonTerminalError();
                                                }
                                            } else {
                                                pushLog("[METODO]", "<TENTATIVA EXP()>");
                                                nonTerminalError();
                                            }
                                        } else {
                                            pushLog("[METODO]", "return");
                                            nonTerminalError();
                                        }
                                    }
                                }
                            } else {
                                pushLog("[METODO]", "FP");
                                nonTerminalError();
                            }
                        } else {
                            pushLog("[METODO]", "FP");
                            nonTerminalError();
                        }
                    } else {
                        pushLog("[METODO]", "PARAMS()");
                        nonTerminalError();
                    }
                } else {
                    pushLog("[METODO]", "AP");
                    nonTerminalError();
                }
            } else {
                pushLog("[METODO]", "id");
                nonTerminalError();
            }
        } else {
            pushLog("[METODO]", "int ou boolean");
            nonTerminalError();
        }
    } else {
        pushLog("[METODO]", "public");
        nonTerminalError();
    }
    

    pushLog("[METODO]", "<nenhuma das derivacoes foi identificada>");
    return nonTerminalRefuse();
}
int CLASSE() {
    nonTerminalStart();

    if (lookahead("class") ) {
        if (lookahead("id") ) {
            if (lookahead("extends") ) {
                if (lookahead("id") ) {
                    goto APOS_EXTENDS;
                } else {
                    pushLog("[CLASSE]", "id");
                    nonTerminalError();
                }
            } else {
                APOS_EXTENDS:
                if (lookahead("ACH") ) {
                    VAR_TESTE_AGAIN:
                    if (VAR() ) {   
                        goto VAR_TESTE_AGAIN;                                             
                    } else {
                        //CASO NAO HOUVER DECLARAO DE VAR OK
                        if ( METODO() ) {
                            if (lookahead("FCH") ) {
                                return nonTerminalAccept();
                            } else {
                                pushLog("[CLASSE]", "FCH");
                                nonTerminalError();
                            }
                        } else {
                            pushLog("[CLASSE]", "<TENTATIVA METODO()>");
                            nonTerminalError();
                        }
                    }
                } else {
                    pushLog("[CLASSE]", "ACH");
                    nonTerminalError();
                }
            }
        } else {
            pushLog("[CLASSE]", "id");
            nonTerminalError();
        }
    } else {
        pushLog("[CLASSE]", "class");
        nonTerminalError();
    }

    pushLog("[CLASSE]", "<nenhuma das derivacoes foi identificada>");
    return nonTerminalRefuse();
}

int PEXP2() {
    nonTerminalStart();

    //PEXP . ID '(' [EXPS] ')'    
    if (lookahead("PONTO") ) {
        if (lookahead("id") ) {
            if (lookahead("AP") ) {
                if ( EXP() ) {
                    if (lookahead("FP") ) {
                        return nonTerminalAccept();
                    } else {
                        pushLog("[PEXP2]", "FP");
                        nonTerminalError();
                    }
                } else {
                    pushLog("[PEXP2]", "<TENTATIVA EXP(9)>");
                    nonTerminalError();
                }
            } else {
                pushLog("[PEXP2]", "AP");
                nonTerminalError();
            }
        } else {
            pushLog("[PEXP2]", "id");
            nonTerminalError();
        }
    } else {
        pushLog("[PEXP2]", "PONTO");
        nonTerminalError();
    }

    pushLog("[PEXP2]", "<nenhuma das derivacoes foi identificada>");
    return nonTerminalRefuse();
}

int  PEXP() {
    nonTerminalStart();
    
    if (lookahead("AP") ) {
        if (PEXP() ) {
            if (lookahead("FP") ) {
                return nonTerminalAccept();
            } else {
                pushLog("[PEXP]", "<FP");
                nonTerminalError();
            }
        } else {
            pushLog("[PEXP]", "<TENTATIVA PEXP(99)>");
            nonTerminalError();
        }
    } else {
        pushLog("[PEXP]", "AP");
        nonTerminalError();
    }

    if (lookahead("id") ) {
        return nonTerminalAccept();
    } else {
        pushLog("[PEXP]", "id");
        nonTerminalError();
    }

    //this
    if (lookahead("this") ) {
        if (PEXP2() ) {
            return nonTerminalAccept(); 
        } else {
            pushLog("[PEXP]", "PEXP2(2)");
            nonTerminalError();            
        }
    } else {
        pushLog("[PEXP]", "this");
        nonTerminalError();
    }
    //new id ( ) . id ( exp )
    if (lookahead("new") ) {
        if (lookahead("id") ) {
            if (lookahead("AP") ) {
                if (lookahead("FP") ) {
                    if ( PEXP2() ) {
                        return nonTerminalAccept();
                    } else {
                        pushLog("[PEXP]", "<TENTATIVA PEXP2()>");
                        nonTerminalError();
                    }
                } else {
                    pushLog("[PEXP]", "FP");
                    nonTerminalError();
                }
            } else {
                pushLog("[PEXP]", "AP");
                nonTerminalError();
            }
        } else {
            pushLog("[PEXP]", "id");
            nonTerminalError();
        }
    } else {
        pushLog("[PEXP]", "new");
        nonTerminalError();
    }

    //new id ( )
    if (lookahead("new") ) {
        if (lookahead("id") ) {
            if (lookahead("AP") ) {
                if (lookahead("FP") ) {
                    return nonTerminalAccept();
                } else {
                    pushLog("[PEXP]", "FP");
                    nonTerminalError();
                }
            } else {
                pushLog("[PEXP]", "AP");
                nonTerminalError();
            }
        } else {
            pushLog("[PEXP]", "id");
            nonTerminalError();
        }
    } else {
        pushLog("[PEXP]", "new");
        nonTerminalError();
    }


    pushLog("[PEXP]", "<nenhuma das derivacoes foi identificada>");
    return nonTerminalRefuse();
}

int SEXP() {
    nonTerminalStart();
    
    if (lookahead("true") ) {
        return nonTerminalAccept();
    } else {
        pushLog("[SEXP]", "true");
        nonTerminalError();
    }

    //false
    if (lookahead("false") ) {
        return nonTerminalAccept();
    } else {
        pushLog("[SEXP]", "false");
        nonTerminalError();
    }
    //num
    if (lookahead("num") ) {
        return nonTerminalAccept();
    } else {
        pushLog("[SEXP]", "num");
        nonTerminalError();
    }
    //null
    if (lookahead("null") ) {
        return nonTerminalAccept();
    } else {
        pushLog("[SEXP]", "null");
        nonTerminalError();
    }
    //new int [ EXP ]
    if (lookahead("new") ) {
        if (lookahead("int") ) {
            if (lookahead("AC") ) {
                if (EXP()) {
                    if (lookahead("FC")) {
                        return nonTerminalAccept();
                    } else {
                        pushLog("[SEXP]", "FC");
                        nonTerminalError();
                    }                
                } else {
                    pushLog("[SEXP]", "<TENTATIVA EXP(8)>");
                    nonTerminalError();
                }                    
            } else {
                pushLog("[SEXP]", "AC");
                nonTerminalError();
            }                
        } else {
            pushLog("[SEXP]", "int");
            nonTerminalError();
        }            
    } else {
        pushLog("[SEXP]", "new");
        nonTerminalError();
    }
    //PEXP [ EXP ]
    /*if ( PEXP() ) {
        if (lookahead("AC") ) {
            if ( EXP() ) {
                if (lookahead("FC")) {

                } else {
                    pushLog("[SEXP]", "FC");
                    nonTerminalError();                    
                }
            } else {
                pushLog("[SEXP]", "null");
                nonTerminalError();
            }
        } else {
            pushLog("[SEXP]", "null");
            nonTerminalError();
        }
    } else {
        pushLog("[SEXP]", "null");
        nonTerminalError();
    }
    */

    pushLog("[SEXP]", "<nenhuma das derivacoes foi identificada>");
    return nonTerminalRefuse();
}

int MEXP() {
    nonTerminalStart();
    //ID OU NUM * ID OU NUM
    if (lookahead("id") || lookahead("num") ) {
        if (lookahead("MULT")) {
            if (lookahead("id")  || lookahead("num")) {
                return nonTerminalAccept();
            } else {
                pushLog("[MEXP]", "[1] id ou num");
                nonTerminalError();
            }   
        } else {
            pushLog("[MEXP]", "MULT");
            nonTerminalError();         
        }
    } else {
        pushLog("[MEXP]", "[2] id ou num");
        nonTerminalError();
    }

    if (lookahead("id") ) {
        if (lookahead("MULT")) {
            if ( PEXP() ) {
                return nonTerminalAccept();
            } else {
                pushLog("[MEXP]", "[1] id ou num");
                nonTerminalError();
            }   
        } else {
            pushLog("[MEXP]", "MULT");
            nonTerminalError();         
        }
    } else {
        pushLog("[MEXP]", "[2] id ou num");
        nonTerminalError();
    }

    pushLog("[MEXP]", "<nenhuma das derivacoes foi identificada>");
    return nonTerminalRefuse();
}

int AEXP() {
    nonTerminalStart();
    //ID OU NUM + ID OU NUM
    if (lookahead("id") || lookahead("num") ) {
        if (lookahead("PLUS")) {
            if (lookahead("id")  || lookahead("num")) {
                return nonTerminalAccept();
            } else {
                pushLog("[AEXP-1]", "[1] id ou num");
                nonTerminalError();
            }   
        } else {
            pushLog("[AEXP-1]", "PLUS");
            nonTerminalError();         
        }
    } else {
        pushLog("[AEXP-1]", "[2] id ou num");
        nonTerminalError();
    }

    //ID OU NUM - ID OU NUM
    if (lookahead("id") || lookahead("num") ) {
        if (lookahead("MINUS")) {
            if (lookahead("id")  || lookahead("num")) {
                return nonTerminalAccept();
            } else {
                pushLog("[AEXP-2]", "[3] id ou num");
                nonTerminalError();
            }   
        } else {
            pushLog("[AEXP-2]", "MINUS");
            nonTerminalError();         
        }
    } else {
        pushLog("[AEXP-2]", "[4] id ou num");
        nonTerminalError();
    }

    pushLog("[AEXP]", "<nenhuma das derivacoes foi identificada>");
    return nonTerminalRefuse();
}

int REXP() {
    nonTerminalStart();
    //REXP < AEXP
    if (lookahead("id") || lookahead("num") ) {
        if (lookahead("LT")) {
            if (lookahead("id")  || lookahead("num")) {
                return nonTerminalAccept();
            } else {
                pushLog("[REXP-1]", "[5]id ou num");
                nonTerminalError();
            }   
        } else {
            pushLog("[REXP-1]", "LT");
            nonTerminalError();         
        }
    } else {
        pushLog("[REXP-1]", "[6]id ou num");
        nonTerminalError();
    }

    //REXP == AEXP
    if (lookahead("id") || lookahead("num") ) {
        if (lookahead("LT")) {
            if (lookahead("id") || lookahead("num")) {
                return nonTerminalAccept();
            } else {
                pushLog("[REXP-2]", "[1] id ou num");
                nonTerminalError();      
            }   
        } else {
            pushLog("[REXP-2]", "LT");
            nonTerminalError();
        }
    } else {
        pushLog("[REXP-2]", "[2]id ou num");
        nonTerminalError();
    }

    //REXP != AEXP
    if (lookahead("id") || lookahead("num") ) {
        if (lookahead("DIF")) {
            if (lookahead("id") || lookahead("num")) {
                return nonTerminalAccept();
            } else {
                pushLog("[REXP-3]", "[3] id ou num");
                nonTerminalError();      
            }   
        } else {
            pushLog("[REXP-3]", "LT");
            nonTerminalError();
        }
    } else {
        pushLog("[REXP-3]", "[4]id ou num");
        nonTerminalError();
    }

    pushLog("[REXP]", "<nenhuma das derivacoes foi identificada>");
    return nonTerminalRefuse();
}
int EXP() {
    nonTerminalStart();
    if (REXP()) {
        return nonTerminalAccept();        
    }
    if (AEXP()) {
        return nonTerminalAccept();        
    }
    if (MEXP()) {
        return nonTerminalAccept();        
    }
    if (SEXP()) {
        return nonTerminalAccept();        
    }
    if (PEXP()) {
        return nonTerminalAccept();        
    }

    pushLog("[EXP]", "<nenhuma das derivacoes foi identificada>");
    return nonTerminalRefuse();
}

int CMD() {
    nonTerminalStart();

    //'{' {CMD} '}'
    if (lookahead("ACH")) {
        if (CMD()) {
            if (lookahead("FCH")) {
                return nonTerminalAccept();
            } else {
                    pushLog("[CMD-1]", "FCH");
                    return nonTerminalRefuse();
            }
        } else {
            pushLog("[CMD-1]", "<TENTATIVA CMD(1)>");
            return nonTerminalRefuse();
        }
    } 
    //if '(' EXP ')' CMD else CMD
    if (lookahead("if")) {
        if (lookahead("AP")) {
            if (EXP()) {
                if (lookahead("FP")) {
                    if (CMD()) {
                        if (lookahead("else")) {
                            if (CMD()) {
                                return nonTerminalAccept();
                            } else {
                                pushLog("[CMD-2]", "<TENTATIVA CMD(2)>");
                                return nonTerminalRefuse();
                            }
                        } else {
                            pushLog("[CMD-2]", "else");
                            return nonTerminalRefuse();
                        }
                    } else {
                        pushLog("[CMD-2]", "<TENTATIVA CMD(3)>");
                        return nonTerminalRefuse();
                    }
                } else {
                    pushLog("[CMD-2]", "FP");
                    return nonTerminalRefuse();
                }
            } else {
                pushLog("[CMD-2]", "<TENTATIVA EXP(1)>");
                return nonTerminalRefuse();
            }
        } else {
            pushLog("[CMD-2]", "AP");
            return nonTerminalRefuse();
        }
    } 
    //if '(' EXP ')' CMD
    if (lookahead("if")) {
        if (lookahead("AP")) {
            if (EXP()) {
                if (lookahead("FCP")) {
                    if (CMD()) {
                        return nonTerminalAccept();
                    } else {
                        pushLog("[CMD-3]", "<TENTATIVA CMD(4)>");
                        return nonTerminalRefuse();
                    }
                } else {
                        pushLog("[CMD-3]", "FCP");
                        return nonTerminalRefuse();
                }
            } else {
                pushLog("[CMD-3]", "<TENTATIVA EXP(2)>");
                return nonTerminalRefuse();
            }
        } else {
            pushLog("[CMD-3]", "AP");
            return nonTerminalRefuse();
        }
    } 
    //while '(' EXP ')' CMD
    if (lookahead("while")) {
        if (lookahead("AP")) {
            if (EXP()) {
                if (lookahead("FCP")) {
                    if (CMD()) {
                        return nonTerminalAccept();
                    } else {
                        pushLog("[CMD-4]", "<TENTATIVA CMD(5)>");
                        return nonTerminalRefuse();
                    }
                } else {
                        pushLog("[CMD-4]", "FCP");
                        return nonTerminalRefuse();
                }
            } else {
                pushLog("[CMD-4]", "<TENTATIVA EXP(3)>");
                return nonTerminalRefuse();
            }
        } else {
            pushLog("[CMD-4]", "AP");
            return nonTerminalRefuse();
        }
    }
    //System.out.println '(' EXP ')' ;
    if (lookahead("System.out.println")) {
        if (lookahead("AP")) {
            if (EXP()) {
                if (lookahead("FP")) {
                    if (lookahead("PV")) {
                        return nonTerminalAccept();
                    } else {
                        pushLog("[CMD-5]", "PV");
                        return nonTerminalRefuse();                    
                    }
                } else {
                    pushLog("[CMD-5]", "FP");
                    return nonTerminalRefuse();                    
                }
            } else {
                pushLog("[CMD-5]", "<TENTATIVA EXP(4)>");
                return nonTerminalRefuse();
            }
        } else {
            pushLog("[CMD-5]", "AP");
            return nonTerminalRefuse();
        }
    } 
    //ID = EXP ;
    if (lookahead("id")) {
        if (lookahead("ATR")) {
            if (EXP()) {
                if (lookahead("PV")) {
                    return nonTerminalAccept();
                } else {
                    pushLog("[CMD-6]", "PV");
                    return nonTerminalRefuse();
                }
            } else {
                pushLog("[CMD-6]", "<TENTATIVA EXP(5)>");
                return nonTerminalRefuse();
            }
        } else {
            pushLog("[CMD-6]", "ATR");
            return nonTerminalRefuse();
        }
    } 
    //ID '[' EXP ']' = EXP ;
    if (lookahead("id")) {
        if (lookahead("AC")) {
            if (EXP()) {
                if (lookahead("FC")) {
                    if (lookahead("ATR")) {
                        if (EXP()) {
                            if (lookahead("PV")) {
                                return nonTerminalAccept();
                            } else {
                                pushLog("[CMD-7]", "PV");
                                return nonTerminalRefuse();                        
                            }
                        } else {
                            pushLog("[CMD-7]", "<TENTATIVA EXP(6)>");
                            return nonTerminalRefuse();                        
                        }
                    } else {
                        pushLog("[CMD-6]", "ATR");
                        return nonTerminalRefuse();                        
                    }
                } else {
                    pushLog("[CMD-7]", "FC");
                    return nonTerminalRefuse();
                }
            } else {
                pushLog("[CMD-7]", "<TENTATIVA EXP(7)>");
                return nonTerminalRefuse();
            }
        } else {
            pushLog("[CMD-7]", "AC");
            return nonTerminalRefuse();
        }
    }

    pushLog("[CMD]", "<nenhuma das derivacoes foi identificada>");
    return nonTerminalRefuse();
 
}

int MAIN() {
    nonTerminalStart();

    if (lookahead("class")){
        if (lookahead("id")) {
            if (lookahead("ACH")) {
                if (lookahead("public")) {
                    if (lookahead("static")) {
                        if (lookahead("void")) {
                            if (lookahead("main")) {
                                if (lookahead("AP")) {
                                    if (lookahead("id")) {
                                        if (lookahead("AC")) {
                                            if (lookahead("FC")) {
                                                if (lookahead("id")) {
                                                    if (lookahead("FP")) {
                                                        if (lookahead("ACH")) {
                                                            if (CMD()) {
                                                                if (lookahead("FCH")) {
                                                                    if (lookahead("FCH")) {
                                                                        return nonTerminalAccept();
                                                                    } else {
                                                                        //FCH
                                                                        pushLog("[MAIN]", "FCH");
                                                                        return nonTerminalRefuse();
                                                                    }
                                                                } else {
                                                                    //FCH
                                                                    pushLog("[MAIN]", "FCH");
                                                                    return nonTerminalRefuse();                                                                    
                                                                }
                                                            } else {
                                                                //FP
                                                                pushLog("[MAIN]", "CMD()");
                                                                return nonTerminalRefuse();
                                                            }
                                                        } else {
                                                            //ACH
                                                            pushLog("[MAIN]", "ACH");
                                                            return nonTerminalRefuse();                                                            
                                                        }
                                                    } else {
                                                        //FP
                                                        pushLog("[MAIN]", "FP");
                                                        return nonTerminalRefuse();                                                        
                                                    }
                                                } else {
                                                    //id
                                                    pushLog("[MAIN]", "id");
                                                    return nonTerminalRefuse();                                                    
                                                }
                                            } else {
                                                //FC
                                                pushLog("[MAIN]", "FC");
                                                return nonTerminalRefuse();                                                
                                            }
                                        } else {
                                            //AC
                                            pushLog("[MAIN]", "AC");
                                            return nonTerminalRefuse();                                            
                                        }
                                    } else {
                                        //id
                                        pushLog("[MAIN]", "id");
                                        return nonTerminalRefuse();
                                    }
                                } else {
                                    //AP
                                    pushLog("[MAIN]", "AP");
                                    return nonTerminalRefuse();                                     
                                }                                
                            } else {
                                //main
                                pushLog("[MAIN]", "main");
                                return nonTerminalRefuse();                                
                            }
                        } else {
                            //void
                            pushLog("[MAIN]", "void");
                            return nonTerminalRefuse();                            
                        }                        
                    } else {
                        //static
                        pushLog("[MAIN]", "static");
                        return nonTerminalRefuse();                         
                    }
                } else {
                    //public
                    pushLog("[MAIN]", "public");
                    return nonTerminalRefuse();                    
                }
            } else {
                //ACH
                pushLog("[MAIN]", "ACH");
                return nonTerminalRefuse();                

            }
        } else {
            pushLog("[MAIN]", "id");
            return nonTerminalRefuse();
        }
    } else {
        pushLog("[MAIN]", "class");
        return nonTerminalRefuse();
    }


    
}

int PROG() {
    nonTerminalStart();

    if (MAIN()){
        if (CLASSE()) {
            return nonTerminalAccept();    
        }
    } else {
        pushLog("[PROG]", "CLASSE()");
        return nonTerminalRefuse();
    } 

    if (MAIN()) {
        return nonTerminalAccept();
    } else {
        pushLog("[PROG]", "MAIN()");
        return nonTerminalRefuse();
    }

}

void AnalisadorSintatico(){
    if (PROG()) {
        printf("LEITUTRA SINTATIC OK\n");
    } else {
        printf("/**************************************\n\tPILHA DE ERRO\n*************************************/\n");
        while (popLog()) {
            NULL;
        }
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
