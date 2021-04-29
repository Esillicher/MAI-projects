#include <iostream.h>
#define TRUE 1
#define FALSE 0
#define Node 20 //Максимальное количество вершин в графе.
typedef int Boolean;
typedef struct L *Lref; // Тип: указатель на заголовочный узел.
typedef struct T *Tref; // Тип: указатель на дуговой узел.

//Описание типа заголовочного узла.
typedef struct L 
{ 
  int Key; //Имя заголовочного узла.
  int Count; //Количество предшественников.
  Boolean Flag; //Флаг посещения узла при обходе.
  Tref Trail; //Указатель на список смежности.
  Lref Next; //Указатель на следующий узел в списке заголовочных узлов.
};

//Описание типа дугового узла.
typedef struct T 
{ 
  Lref Id; 
  Tref Next; 
};

class Spisok
{
  private:
    Lref Head; //Указатель на голову списка заголовочных узлов.
    Lref Tail; //Указатель на фиктивный элемент 
               // в конце списка заголовочных узлов.
    int  X[20]; //Результат работы программы.
    void SearchGraph (int, Lref *);
    Lref Search(int);
  public:
    Spisok() {//Инициализация списка заголовочных узлов.
              Head = Tail =  new (L); }
    Lref GetHead() { return Head; }
    Lref GetTail() { return Tail; }
    void MakeGraph ();
    void PrintGraph ();
    void AddGraph(int, int);
    void DeleteGraph(int, int);
    void Clique (int, int);
    void X1 (Lref t) {X[1] = t->Key;};
};

void main ()
{
  Spisok A;
  Lref t; //Рабочий указатель для перемещения 
          // по списку заголовочных звеньев.
  Lref t1;
  int n=0;

  //Построение графа и вывод его структуры Вирта.
  A.MakeGraph ();
  A.PrintGraph (); cout<<endl;
  //Инициализация и подсчет количества вершин графа.
  t = A.GetHead();
  while (t!=A.GetTail())
    { n++; t = (*t).Next; }
  // ------------------------------------ 
  //Нахождение всех клик в графе Head.
  for (int i=3;i<=n;i++)
  {
    //i - количество вершин в клике (i<=3).
    cout << "Перечислим все клики длины " << i << endl;
    t = A.GetHead();
    while (t!=A.GetTail())
    {
       //Инициализация.
       t1 = A.GetHead();
       while (t1!=A.GetTail())
       { t1->Flag = TRUE; t1 = t1->Next;  }
       A.X1(t); t->Flag = FALSE;
       //Отыскание клики с i вершинами, "начинающейся" в вершине t.
       A.Clique (2,i); t = t->Next;
    }
  }
} 

Lref Spisok::Search (int w)
//Функция возвращает указатель на заголовочный узел 
//ключом w. Если узел отсутствует, то функция возвращает NULL .
{
  Lref h = Head;
  (*Tail).Key = w; //Поиск "с барьером".
  while ((*h).Key!=w) h = (*h).Next;
  if (h==Tail) //В списке заголовочных узлов нет узла с ключом w.
    h = NULL;
  return h;
} 

void Spisok::AddGraph (int x,int y)
//Добавление дуги (x,y) (если ее не было!) к структуре
//Вирта, соответствующей ориентированному графу Head.
{
  Lref p,q;    //Рабочие указатели.
  Tref t,r;    //Рабочие указатели.
  Boolean Res; //Флаг наличия в графе данной дуги.

  //Определим, существует ли в графе дуга (x,y)? 
  SearchGraph (x,&p); SearchGraph (y,&q);
  r = (*p).Trail; Res = FALSE;
  while ((r!=NULL)&&(!Res)) 
    if ((*r).Id==q) Res = TRUE; else r = (*r).Next;
  if (!Res)
  { //Если дуга отсутствует, то поместим её в граф.
    t = new (T); (*t).Id = q; (*t).Next = (*p).Trail; 
    (*p).Trail = t; (*q).Count++;
  }
} 

void Spisok::DeleteGraph (int x,int y)
//Функция возвращает указатель Head на структуру 
//Вирта, соответствующую ориентированному графу
//и полученную удалением дуги (x,y).
{
  Lref p,q;    //Рабочие указатели.
  Tref t,r;    //Рабочие указатели.
  Boolean Res; //Флаг наличия в графе данной дуги.

  //Определим, существует ли в графе дуга (x,y)?
  p=Search (x); q= Search (y);
  if ((p!=NULL)&&(q!=NULL))
  { //Вершины x и y в графе есть.
    r = (*p).Trail; Res = FALSE; 
    while ((r!=NULL)&&(!Res)) 
      if ((*r).Id==q) Res = TRUE; 
      else r = (*r).Next; 
   if (Res) //Если дуга существует, то удалим её.
   if (r==(*p).Trail)
     { (*p).Trail = (*(*p).Trail).Next; delete r; (*q).Count--; } 
   else 
    {
      t = (*p).Trail; 
      while ((*t).Next!=r) t = (*t).Next;
      (*t).Next = (*(*t).Next).Next; delete r; (*q).Count--; }
    }
} 

void Spisok::SearchGraph (int w, Lref *h)
//Функция возвращает указатель на заголовочный узел 
//с ключом w в графе, заданном структурой Вирта с указателем Head. 
{
  *h = Head; (*Tail).Key = w;
  while ((**h).Key!=w) *h = (**h).Next;
  if (*h==Tail)
  //В списке заголовочных узлов нет узла с ключом w.
  //Поместим его в конец списка Head.
  { Tail = new (L); (**h).Count = 0; 
    (**h).Trail = NULL; (**h).Next = Tail; }
}

void Spisok::MakeGraph ()
//Функция возвращает указатель Head на структуру 
//Вирта, соответствующую ориентированному графу.
{
  int x,y;
  Lref p,q; //Рабочие указатели.
  Tref t,r; //Рабочие указатели.
  Boolean Res; //Флаг наличия дуги.
  cout<<"Вводите начальную вершину дуги: ";
  cin>>x;
  while (x!=0)
  {
     cout<<"Вводите конечную вершину дуги: "; cin>>y;
     //Определим, существует ли в графе дуга (x,y)?
     SearchGraph (x, &p); SearchGraph (y,&q);
     r = (*p).Trail; Res = FALSE; 
     while ((r!=NULL)&&(!Res)) 
       if ((*r).Id==q) Res = TRUE; 
       else r = (*r).Next; 
     if (!Res) //Если дуга отсутствует, то поместим её в граф.
      { t = new (T); (*t).Id = q; 
        (*t).Next = (*p).Trail; (*p).Trail = t; (*q).Count++; } 
     cout<<"Вводите начальную вершину дуги: "; cin>>x;
  }
}

void Spisok::PrintGraph ()
//Вывод структуры Вирта, заданной указателем 
//Head и соответствующей ориентированному графу.
{
  Lref p; //Рабочий указатель.
  Tref q; //Рабочий указатель.

  p = Head;
  while (p!=Tail)
  {
     cout<< (*p).Key << "("; q = (*p).Trail; 
     while (q!=NULL) 
      { cout<<(*(*q).Id).Key; q = (*q).Next; } 
     cout<<")"; p = (*p).Next; cout<<" ";
  }
}

void Spisok::Clique (int k, int m)
//Нахождение всех клик, содержащих m вершин, в графе,
//заданном структурой Вирта с указателем Head,
//k - количество вершин в частичном решении.
{
  Tref r,r1;   //Рабочие указатели.
  Lref p,q;    //Рабочие указатели.
  Lref t;      //Указатель на k-ю вершину частичного решения.
  int v;       //Вершина - кандидат на дополнение к частичному решению.
  Boolean Res; //Флаг клики.
  Boolean Res1;//Флаг существования ребра.
  int i;       //Параметр цикла.

  SearchGraph (X[k-1], &t);
  r = t->Trail;
  while ( r != NULL )
  {
    v = r->Id->Key;
    //Проверим, смежна ли вершина v с вершинами X[1],X[2],...,X[k-1].
    Res = TRUE;
    for (i=1;i<=k-1;i++)
    {
      //Cуществует ли в графе ребро (X[i],v)?
      SearchGraph (v, &p);
      SearchGraph (X[i], &q);
      r1 = p->Trail;
      Res1 = FALSE;
      while  (r1 != NULL && !Res1)
       if ( r1->Id==q ) Res1 = TRUE;
       else  r1 = r1->Next;
      Res = (Res && Res1);
    }
    if (!Res) r->Id->Flag = FALSE;
    // -------------------------- 
    if  (k==m && Res)
      //Количество вершин в графе равно m, и 
      //вершины X[1],X[2],...,X[k] образуют клику.
      {
        //Вывод клики на экран дисплея.
        for (i=1;i<=k-1;i++) cout << X[i] << " ";
        cout << v << endl;
      }
    else  
      if ( r->Id->Flag )
      {
        X[k] = r->Id->Key;
        r->Id->Flag = FALSE;
        Clique (k+1,m);
        r->Id->Flag = TRUE;
      }
    r = r->Next;
  }
}
