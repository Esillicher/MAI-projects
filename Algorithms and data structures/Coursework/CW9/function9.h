#ifndef FUNCTION7_H
#define FUNCTION7_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	char key[6]
}t_key;

typedef struct{
	char val[100];
}t_val;

/*******Объявление функций.*********/
void swapf(char* a, char* b);							// swap для ключей.
void swapv(char* a, char* b);							// swap для значений.
void bubble_sort(t_key* skey, t_val* sval, int size);	// Сортировка пузырьком массива ключей skey размера size.
int binary_search(t_key* key, char* x, size_t size);	// Двоичный поиск в массиве key размера size по ключу x.

/***********************************/

void swapf(char* a, char* b){
	char temp[6];
	strcpy(temp, a);
	strcpy(a, b);
	strcpy(b, temp);
	return;
}

void swapv(char* a, char* b){
	char temp[100];
	strcpy(temp, a);
	strcpy(a, b);
	strcpy(b, temp);
	return;
}

void bubble_sort(t_key* skey, t_val* sval, int size) {
	int i, j;
    for (j = 0; j < size-1; j++){
        for (i = 0; i < size - j - 1; i++){
            if (strcmp(skey[i].key,skey[i+1].key)>0){
                swapf(skey[i].key, skey[i+1].key);
                swapv(sval[i].val, sval[i+1].val);
            }
        }
    }
}


int binary_search(t_key* key, char* x, size_t size)
{
    size_t first = 0;
    size_t last = size;
 
    if (size == 0) {
        return -1;
    } 
	else if (strcmp(key[0].key,x) > 0) {
        return -1;
    }
	else if (strcmp(key[size - 1].key, x) < 0) {
        return -1;
    }
    while (first < last) {
        size_t mid = first + (last - first) / 2;
        if (strcmp(x,key[mid].key)<=0)
            last = mid;
        else
            first = mid + 1;
    }
    if (strcmp(key[last].key,x) == 0){
        return last;
	} 
	else {
        return -1;
    }
}


#endif
