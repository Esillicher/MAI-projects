#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function8.h"


int main(){
	list l;
	list_init(&l);
	char com[10];
	unsigned char liter;
	int pos;
	int err_num; 		//переменная ошибок.
	
	help();
	
	while(strcmp(com,"exit")!=0){
		printf("=>");
		scanf("%s", com);
		
		if(strcmp(com, "help")==0){
			help();
		}
		else if(strcmp(com, "in")==0){
			scanf("%d %c", &pos, &liter);
			err_num=insert(&l, pos, liter);
			if(err_num){
				printf("Error. Code %d\n", err_num);
			}
		}
		else if(strcmp(com, "pb")==0){
			scanf(" %c", &liter);
			err_num=push_back(&l,liter);
			if(err_num){
				printf("Error. Code %d\n", err_num);
			}
		}
		else if(strcmp(com,"del")==0){
			scanf(" %c", &liter);
			err_num=del(&l, liter);
			if(err_num){
				printf("Error. Code %d\n", err_num);
			}
		}
		else if(strcmp(com, "print")==0){
			list_print(&l);
		}
		else if(strcmp(com,"size")==0){
			printf("%d\n", list_size(l));
		}
		else if(strcmp(com, "solution")==0){
			solution(&l);
		}
		else if(strcmp(com,"exit")==0){
			;
		}
		else printf("Unknown command.\n");
	}
	
	free(l.vec);
	return 0;
}
