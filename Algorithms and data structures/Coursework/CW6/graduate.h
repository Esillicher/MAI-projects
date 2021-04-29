#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifndef __graduate_h__
#define __graduate_h__
#define MAX_GR 9

typedef struct{
	char name[50];
	char init[3];
	char gender[8];
	int cl_num;
	char cl_alph;
	char work[50];
}graduate;

char filename[50];

//-------------------------
int scan(graduate *g); //заполняет структуру, ввод с клавиатуры. возвращает количество считанных аргументов
void add(FILE *out); // заполняет файл, ввод из клавиатуры/из текстового файла файла
void print_help(); //очевидно
FILE* open_file(); // открывает файл и возвращает указатель на него
void rewrite(FILE *f, int size, int str_num); //перезаписывает файл, исключая нужную строку(str_num). f- укзатель на файл
// size - размер структуры
void del(FILE *f); //удаляет запись из f
void print(FILE *f); //печатает бд
graduate gen(); // генерирует структуру
void gen_db(); // заполняет файл с помощью функции выше
int count(FILE *f);//считает, сколько записей размера sizeof(graduate) имеется в файле(количество выпускников)
void solution(FILE* f); // собственно, задание
//-------------------------

void print_help(){
	puts("------------------------------------");
	puts("open \"file\"					- open file.");
	puts("close						- close current file.");
	puts("add						- add graduate.");
	puts("	-f \"filename\"				- from file.");
	puts("	-m \"information\"*			- manually.");
	puts("gen \"filename\" \"number of graduates\" 		- generate database.");
	puts("del \"student_name\"				- delete student");
	puts("print						- print current file. ");
	puts("solution					- solve the problem.");
	puts("help						- show help(this).");
	puts("clear						- clear screen.\n");
	puts("*graduate information format:\n\"name\" \"initials\" \"gender\" \"class number\" \"class letter\" \"workplace\"\n");
	puts("------------------------------------");
	return;
}

int scan(graduate *g){
	return scanf("%s %s %s %d %c %s", g->name, g->init, g->gender, &g->cl_num, &g->cl_alph, g->work);
}

void add(FILE *out){
	graduate g;
	char flag[3]; //переменная для параметра
	scanf("%s", flag);
	fseek(out,0,SEEK_END);
	if(strcmp(flag, "-f")==0){
		FILE *in; 
		char o_filename[50]; //имя файла, из которого идет заполнение
		scanf("%s", o_filename);
		if ((in = fopen(o_filename, "r")) == NULL){
			printf("%s - no such file.\n", o_filename);
            return;
		}
		//читаем из in и записываем в out
		while(fscanf(in, "%s %s %s %d %c %s", g.name, g.init, g.gender, &g.cl_num, &g.cl_alph, g.work)==6){
			fwrite(&g, sizeof(g), 1, out);
		}
		puts("Base successfully filled.");
		fclose(in);
	}
	else if(strcmp(flag,"-m")==0){
		if(scan(&g)==6){ //считывваем данные с клавиатуры
			fwrite(&g, sizeof(g), 1, out); //записываем в файл
		}
		else{
			puts("Something wrong.");
		}
	}
	else
		puts("Wrong parameter. Press ENTER.");
	return;
}

FILE* open_file(){
	FILE* f;
	scanf("%s", filename); //имя открываемого файла. переменная объявлена глобальной, чтобы отображать открытый файл.
	if((f=fopen(filename,"a+b")) == NULL){
		puts("Error while opened file.");
		strcmp(filename, "");
	}
	else{
		puts("File opened.");
	}
	return f;
}

void rewrite(FILE *f, int size, int str_num){
    FILE *t;
    int i=0;
	graduate g;
    t=fopen("temp", "a+b");
    fseek(f, 0, SEEK_SET); //устанавливаем указатель на начало файла
    
    while(fread(&g, size, 1, f)==1){ //читаем запись
        if(i!=str_num){ // записываем все строки кроме i-й
            fwrite(&g, size, 1,t);
        }
        i++;
    }
    
    //записываем из временного файла обратно в основной
    fclose(f);
    f=fopen(filename, "w+b");
    fseek(t, 0, SEEK_SET);
    while(fread(&g, size, 1, t)==1){
        fwrite(&g, size, 1, f);
    }
    fclose(t);
    fclose(f);
    remove("temp"); // UNIX: system("rm temp");
    f=fopen(filename, "a+b");
	return;
}

void del(FILE *f){
	graduate g;
	int size=sizeof(g), i=0;
	char name[50]; //фамилия удаляемого
	char init[3]; // инициалы
	scanf("%s %s", name, init);
	fseek(f, 0, SEEK_SET);
	
	while(fread(&g, size, 1, f)==1){
		if(strcmp(name, g.name)==0 && strcmp(init, g.init)==0){ //сравниваем имеющиеся фамилию и инициалы с записью
			rewrite(f,size,i);
			printf("%s %s deleted.\n", g.name, g.init);
			return;
		}
		++i;
	}
	printf("Graduate %s %s wasn't found.\n", name, init);
	return;
}

void print(FILE *f){
	graduate g;
	int i=1;
	fseek(f,0,SEEK_SET);
	printf("%s\n", filename);
	puts("============================================");
	while(fread(&g, sizeof(g),1,f)==1){
		printf("%3.d. %-20s %s %-8s %2.d %c %s\n",i, g.name, g.init, g.gender, g.cl_num, g.cl_alph, g.work);
		i++;
	}
	puts("============================================");
	return;
}

graduate gen(){
    graduate g;
    int i;
    unsigned char w[15][50]={{"Kalinina"},{"Mizulina"},{"Kuzmenko"},{"Mamedova"},{"Arefieva"},{"Basharina"},{"Borisenko"},{"Gurskaya"},{"Krutikova"},
        {"Antonova"},{"Smertina"},{"Sinegubova"},{"Gorbunova"},{"Zlobina"},{"Rzhavina"}},
    m[15][50]={{"Deryabin"},{"Milonov"},{"Zhirinovsky"},{"Malyshev"},{"Volok"},{"Zaycev"},{"Makarov"},{"Ilyin"},{"Shipunov"},{"Kovshov"},{"Senechkin"},
        {"Klimovich"},{"Sergeev"},{"Uvarov"},{"Kalashnikov"}},
	wplace[15][50]={{"IzGTU"},{"MPU"},{"MAI"},{"MIPT"},{"MSU"},{"MATI"},{"ZAVOD"},{"BIBLIOTEKA"},{"UBORSHIK"},
	{"KASSIR"},{"LETCHIK"},{"BUS_IN_ASS_MAN"},{"PROGRAMMIST"},{"DANTIST"},{"MANAGER"}};
        //список фамилий/мест работы. лучше замените своим
        
	
	g.init[0]='A'+rand()%26; //генерим инициалы
    g.init[1]='A'+rand()%26;
    g.init[2]='\0';
    
    if(rand()%2){
        strcpy(g.name,w[rand()%15]); //если четное-девушка
        strcpy(g.gender,"female");
        strcpy(g.work,wplace[2+rand()%12]);
    }
    else{
        strcpy(g.name,m[rand()%15]); //нечетное - догадаешься
        strcpy(g.gender,"male");
        strcpy(g.work,wplace[rand()%15]);
    }
    srand(rand());
    g.cl_num=7+rand()%5;
    g.cl_alph='A'+rand()%4;
    return g;
}

void gen_db(){
	FILE *db;
	char db_name[50];
	int number,i; //number-количество записей, i-счетчик
	graduate g;
	scanf("%s", db_name);
    scanf("%d", &number);
    
    db=fopen(db_name, "w+b");
    
    for(i=0;i<number;i++){
    	g = gen();
    	fwrite(&g, sizeof(g), 1, db);
    }
    fclose(db);
}

int count(FILE *f){ 
	graduate g;
	int begin, end;
	fseek(f, 0, SEEK_SET);
	begin=ftell(f);
	fseek(f,0,SEEK_END);
	end=ftell(f);
	return (end-begin)/sizeof(g);
}

void solution(FILE* f){ //функция, решающая задание
	graduate g1, g2;
	int sm_count=0; //счетчик однофамильцев
	int number=count(f); //количество записей в файле
	int size=sizeof(graduate); // размер одной записи
	int *fb_str,*sm; // строки, которые не надо читать(в них записаны однофамильцы людей, что выше по списку)
	int i,j,flag; // счетчики и флаг. флаг показывает, был записан первый однофамилец или нет. 
	fb_str= (int*)malloc(number*sizeof(int));
	sm=(int*)malloc(number/2*sizeof(int));
	
	for(i=0;i<number;i++){
		fb_str[i]=-1; //-1 означает, что строку нужно читать. По умолчанию читаются все строки
		// строки, в которых записаны однофамильцы не читаются
	}
	//-------------
	fseek(f,0, SEEK_SET); //установили указатель на начало файла
	
	for(i=0;i<number-1;i++){ //начинаем перебирать записи. сравниваем выпускника со всеми последующими, и так с каждым, кроме уже найденных однофамильцев
		flag=0;
		
		if(fb_str[i]==-1){ //если в строке не однофамилец, читать
			fseek(f,i*size, SEEK_SET);
			fread(&g1, size, 1, f);
			
			for(j=i+1;j<number;j++){//ищем однофвмильцев
				if(fb_str[j]==-1){//если в строке не однофамилец, читать
					fseek(f,j*size, SEEK_SET);
					fread(&g2, size, 1, f);
					
					if(strcmp(g1.name,g2.name)==0 && g1.cl_num==g2.cl_num){ //если фамилии одинаковые и классы параллельные,
					// заносим номер записи в fb_str и инкрементируем счетчик
						if(!flag){ //Обладатель фамилии, сравниваемой с остальными
							sm[sm_count]=i;
							fb_str[i]=0;
							sm_count++;
							flag=1;
						}
					sm[sm_count]=j; //его однофамилец
					fb_str[j]=0;
					sm_count++;
					}
					
				}
			}
			
		}
		
	}
	//-------------
// выводим на экран всех однофамильцев в параллельных классах.
	for(i=0;i<sm_count;i++){ 
		fseek(f,sm[i]*size,SEEK_SET);
		fread(&g1, size, 1, f);
		printf("%3.d. %-20s %s, %2.d %c\n",sm[i]+1, g1.name, g1.init, g1.cl_num, g1.cl_alph);
	}
}


#endif
