#include <stdio.h>
#include "graduate.h"


int main(){
	char com[10], cur_file[50]; // com - тут хранится текущая команда, cur_file - имя открытого файла.
	strcpy(cur_file, "");
	FILE *f = NULL;
	print_help();
	
	
	while(strcmp(com, "exit")!=0){
		printf("Current file: %s\n", cur_file);
		printf("=:> ");
		scanf("%s", com); // считываем команду. Дальше в зависимости от выбора управление передается одной из функций.
		
		//описание функций в заголовочном файле .h
		if(strcmp(com, "help") == 0){ 
			print_help();
		}
		else if(strcmp(com, "clear")==0){ 
			system("cls"); // UNIX: system("clear");
		}
		else if(strcmp(com, "open")==0){ 
			fclose(f);
			f=open_file();
			strcpy(cur_file, filename);
		}
		else if(strcmp(com, "gen") == 0){ 
			srand(time(NULL));
			gen_db();
		}
		else if(strcmp(com,"exit")==0){
			;
		}
		else if(f==NULL){
			puts("There is no opened file!");
		}
		else if(f!=NULL){
			if(strcmp(com, "add")==0){
				add(f);
			}
			else if(strcmp(com, "del") == 0){
				del(f);
			}
			else if(strcmp(com, "print") == 0){
				print(f);
			}
			else if(strcmp(com, "close") == 0){
				fclose(f);
				strcpy(cur_file, "");
				f=NULL;
			}
			else if(strcmp(com, "sol") == 0){
				solution(f);
			}	
		}
		else{
			if(f==NULL){
				puts("There is no opened file!");
			}
			else{
				puts("Unknown command.");
			}
		}
	}
	fclose(f);
	return 0;
}
