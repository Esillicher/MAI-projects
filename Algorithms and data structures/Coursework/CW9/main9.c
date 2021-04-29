#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "function9.h"

int main(){
	FILE* f;
	char fname[50];
	char fkey[6];
	t_key key[12];
	t_val value[12];
	int size=0;
	// Вводим имя файла.
	printf("Enter filename: ");
    scanf("%s",fname);
    f=fopen(fname,"r");
    if(f==NULL){
        printf("File doesn't exist");
        return 0;
    }
    // Печатаем содержимое файла.
    printf("\nDefault table:\n");
    while(fscanf(f,"%s %s",key[size].key,value[size].val)!=EOF){
        printf("%s %s\n",key[size].key,value[size].val);
        size++;
    }
    // Печатаем отсортированное содержимое файла.
    printf("\nSorting table:\n");
    bubble_sort(key ,value, size);
    int i=0;
    for(;i<size;i++){
    	printf("%s %s\n",key[i].key,value[i].val);
    }
    // Вводим ключ, которому соответствует 2 значения.
    printf("\nEnter key to find\n");
    scanf("%s", fkey);
    int k=0;
    int felem=0;
    while(felem!=-1){
    	felem=binary_search(key, fkey, size);
    	if(felem!=-1){
			printf("This element: \n%s\n", value[felem].val);				// Первое значение выводится и свапается с последним
	    	strcpy(key[felem].key,key[size-1].key);
	    	strcpy(value[felem].val,value[size-1].val);
	    	bubble_sort(key ,value, size);
    		size--;															// Размер уменьшаем.
    	}																	// Каждый раз выводится первый эл-т, соотв. ключу. Затем он удаляется и печатается след. и т.д.
    	k++;
    }
    if(k==1)printf("NOT FOUND");
	
	
	return 0;
}
