#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char str[1000];

int main() {
	read();
	printf(str);
	return 0;
}

void write() {
   	FILE * fp;
	
	// todo exemplo
	fp = fopen("file.txt", "w+");
	fprintf(fp, "%s %s %s %d", "We", "are", "in", 2015);
	fclose(fp);
}

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
