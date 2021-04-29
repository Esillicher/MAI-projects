#include <stdio.h>
#include <string.h>
#include "function7.h"

int main(){
	mat a;
	double p;
	char com[10];
	init(&a);
	
	help();
	
	while(strcmp(com, "exit")!=0){
		printf("=>");
		scanf("%s", com);
		
		if(strcmp(com, "read")==0){
			read(&a);
		}
		else if(strcmp(com, "print")==0){
			puts("=====+print+======");
			print(a);
			puts("==================");
		}
		else if(strcmp(com, "inprint")==0){
			puts("====+inprint+=====");
			inprint(a);
			puts("==================");
		}
		else if(strcmp(com, "sol")==0){
			solution(&a);
		}
		else if(strcmp(com, "exit")==0){
			;
		}
		else puts("Unknown command");
	}
	return 0;
}
