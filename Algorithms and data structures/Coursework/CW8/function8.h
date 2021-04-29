#ifndef FUNCTION8_H
#define FUNCTION8_H

#include <stdio.h>
#include <stdlib.h>

#define START_LIST_SIZE 10					// Начальный размер списка.
#define MEM_EPS 5							// Разница между размером списка и выделенной памятью, после которой происходит удвоение.

typedef struct{
	unsigned char* vec;						// Массив, хранящий список.
	int mem_inf;							// Инормация о памяти, занимаемой массивом.
}list;

/*******Объявление функций.*********/
void help();								// Печать помощи.

void list_print(list*);						// Печать списка. 
int insert(list*, int, unsigned char);		// Вставка элемента в список. Возврат: 0 - ок, 1 - индекс вне размеров списка.
int del(list*, unsigned char);				// Удаление элемента из списка. Возврат: 0 - ок, -1 - элемент не найден.
int list_size(list);						// Подсчет длины списка. Возвращает количество элементов в списке.
int list_find(list, unsigned char);			// Поиск элемента в списке. Возвращает индекс или -1, если элемент не наден.

void list_init(list*);						// Инициализация списка.
void list_resize(list*); 					// Удваивает память для хранения списка.

unsigned char pop_back(list *l);			//Возвращает последний элемент и удаляет его.
int solution(list*);						//Выполняет задание, т.е. переставляет 1-ю и вторую половину списка.
/***********************************/

void help(){
	puts("==========================================================");
	puts("help........................print help");
	puts("print.......................pint list");
	puts("in <pos> <let>..............insert letter into list at pos");
	puts("pb <let>....................add letter in the list end");
	puts("del <let>...................delete letter from list");
	puts("size........................print list size");
	puts("solution....................solve the problem.");
	puts("==========================================================");
}

void list_init(list* l){
	l->vec=NULL;															// Зануляем указатель (на всякий случай)
	l->vec=(unsigned char*)malloc(START_LIST_SIZE*sizeof(unsigned char));	// Выделяем память на START_LIST_SIZE элементов
	l->mem_inf=START_LIST_SIZE;												// Сообщаем, сколько памяти было выделено.
	l->vec[0]=0;															// Присваиваем первому элементу 0(конец массива).
}

void list_resize(list*l){
	l->vec=realloc(l->vec,2*sizeof(l->vec));			// Перераспределяем память(выделяем в 2 раза больше)
	l->mem_inf*=2;
}

void list_print(list* l){
	int i;
	for(i=0;i<list_size(*l);i++){
		printf("%d. %c\n",i, l->vec[i]);
	}
	return;
}

int list_size(list l){
	int size = 0;
	while(l.vec[size]!=0){
		size++;
	}
	return size;
}

int insert(list* l,int index, unsigned char c){
	//index--;											// Если первый элемент нулевой, убрать эту строку.
	int size=list_size(*l),i;
	unsigned char temp[2];
	if((l->mem_inf - size) < MEM_EPS) list_resize(l);	// Проверяем размер массива. Увеличиваем, если надо.
	if(index>size || index<0){ 							// Если индекс вне границ списка, выходим с ошибкой.
		return -1;
	}
	else{ 												// Если все хорошо, вставляем элемент.
		temp[index%2]=c;
		for(index; index<size+1; index++){
			//printf("DEBUG: iter\n");
			temp[(index+1)%2]=l->vec[index];
			l->vec[index]=temp[index%2];
		}
		l->vec[index]=0;
	}
	return 0;
}

int list_find(list l, unsigned char c){
	int index=0;
	while(l.vec[index]!=0){
		if(l.vec[index]==c) return index;
		index++;
	}
	return -1;									// Не нашли, возвращаем -1.
}

int del(list* l, unsigned char c){
	int index, size=list_size(*l), i;
	index=list_find(*l, c);
	if(index==-1){
		return -1;
	}
	else{
		for(i=index;i<size;i++){
			l->vec[i]=l->vec[i+1];
		}
	}
	return 0;
}

int push_back(list* l, unsigned char c){
	return insert(l, list_size(*l), c);
}


unsigned char pop_back(list *l){
	unsigned char c;
	int size=list_size(*l);
	c = l->vec[size-1];
	l->vec[size-1]=l->vec[size];
	return c;
}

int solution(list *l){
	int size = list_size(*l);
	int i,k = (size-size%2)/2;
	unsigned char c;
	for(i=0;i<k;i++){
		c = pop_back(l);
		insert(l,0,c);
	}
	return 0;
}





#endif
