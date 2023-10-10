#include <iostream>
//Занесение X в стек на базе линейного двунаправленного
//связанного списка.

using namespace std;
struct node2
{
    node2 *next, *prev;
    int info;
};

node2 *addstack (node2 *lst, int x)
{
    node2 *p = new node2;
    p->info=x;
    if(lst!=NULL)
        lst->prev=p; /* новая запись размещается перед той, на
которую указывал lst */
    p->next=lst;
    p->prev=NULL;
    lst=p;
    return (lst) ;
}

void printlist_2(node2 *lst)
{ node2 *p,*t;

    p=lst;
    cout<<"forward";
    while(p)
    {
        cout<<' '<<p->info;
        t=p;p=p->next;
    }
    cout<<"\nback";
    p=t;
    while(p)
    {
        cout<<' '<<p->info;
        p=p->prev;
    }
    cout<<endl;
}

void free_memory2(node2 *lst) //аналогично односвязному списку
{ node2 *now=lst, *next=lst;
    while (next)
    {next=now->next;
        delete(now);
        now=next;
    }
    cout<<"\nNow memory is free";
}

node * del (node *lst, int x1)
{
    node *tek,*pred, *t;
    tek=lst->next; //указатель на текущий элемент
    pred=lst; //указатель на предыдущий элемент
    while (lst&&lst->info<x1) //пока удаляется первый элемент
        if (lst->next==lst) //если элемент первый и единственный
        {
            delete(lst); lst=NULL;
        }
        else //если первый и не единственный
        { t=lst; //поиск нового lst – он будет перед исходным lst
            do
                t=t->next;
            while (t->next!=lst);
            t->next=pred->next;
            delete(lst);
            lst=t;
            pred=t;
        }

    if (lst!=NULL)
//если список еще не удален полностью
        do
            if (tek->info<x1)
            { //удаление элемента из середины списка
                pred->next=tek->next;
                delete(tek);
                tek=pred->next;
            }
            else //движение по списку
                pred=tek,tek=tek->next;
        while (tek!=lst);

    return(lst);
}

int main()
{ node2 *lst=NULL; int n=1;
    cout<<"Enter positive integers \n";
    while(n>0)
    {cin>>n;
        if(!cin.fail()&&n>0) lst=addstack(lst,n);}
    if (lst)
    { printlist_2(lst); free_memory2(lst); }
    else cout<<" No list";
    return 0;}

    //бинарные деревья

struct node
{int info;
    node *left,*right;
};
//новый узел с числом p
node *newn(int p)
{
    node *uk = new node;
    uk->info=p;
    uk->left=uk->right=NULL;
    return(uk);
}

//присоединение нового узла
// c числом x к узлу p слева
void setleft(node*p, int x)
{p->left=newn(x);
}
void setright(node*p, int x)
{p->right=newn(x);
}
node *form()
{int n;
    node *der=NULL,*next,*tek;
    cout<<"Input integer
    numbers\nletter means that
    input is over\n";
    cin>>n;
    if(!cin.fail())
    {der=newn(n);
        cin>>n;
        while(!cin.fail())
        {next=tek=der;
            while (next!=NULL)
            {
                tek=next;
                if (n<tek->info)
                    next=tek->left;
                else next=tek->right;
            }
            if (n<tek->info) setleft(tek,n);
            else setright(tek,n);
            cin>>n;
        }
    }
    return der;
}
//вывод дерева на экран

void print_tree(node *der, int h)
{ if (der)

    {
        print_tree(der->left,h+1);
        for(int i=0; i<h;i++) cout <<" ";
        cout << der->info << endl;
        print_tree(der->right,h+1);
    }
}
int main()
{
    node *der;
    cout<<"Now we'll make tree\n";
    der=form();
    if (!der)
        cout<<"Tree is empty";
    else
        print_tree(der,0);
    return 0;
}

//N узлов

int NumEl(node *der) //прямой обход
{ if(der==NULL) return(0) ;
    return(NumEl(der->left)+NumEl(der->right)+1); }
//Вызов:
int k;
//считаем, что эта переменная везде определена
k= NumEl(der);
cout<<"number of elements is equal "<<k;

//N листьев

int NumLeaf(node *der)
{if(der==NULL)return(0);
    if(der->left==NULL&&der->right==NULL)return(1);
    return(NumLeaf(der->left)+NumLeaf(der->right));
}
//Вызов:
k=NumLeaf(der);
cout<<"number of leafs is equal "<<k;


//N однодетных отцов

int Num1(node *der)
{ int k=0;

    if(der==NULL)return(0) ;
    if((der->left==NULL && der->right!=NULL)||
       (der->left!= NULL && der->right==NULL))

        k=1;

    return(k+Num1(der-> left)+Num1(der->

            right));
}

//Вызов:
k=Num1(der);
cout<<"number of one-child fathers is equal"<<k;

//глубина дерева
/* объявление глобальных переменных, чтобы
не копировать их при каждом вызове */
int gl, gr,gmax;
int depth(node *der)
{//тривиальный случай
    if(der==NULL)return(0);
//второй случай
    if(der->left==NULL&&der->right==NULL)
        return(0);
    gl=depth(der->left);
    gr=depth(der->right) ;
    gmax=(gl>gr)?gl:gr ;
    return(gmax+1);
}

//удаление листьев

void DelLeaf(node **der) //прямой обход
{ /*указатель на указатель, т.к. корень может
меняться*/
    if (*der==NULL)return; //тривиальный случай
    if ((*der)->left==NULL&&(*der)->right==NULL)
    { //узел является листом
        cout<<"Leaf was deleted " <<
            (*der)->info)<<endl;
        delete(*der);
        *der=NULL;
        return;
    }

    DelLeaf(&((*der)->left));
    DelLeaf(&( (*der)->right) ) ;
//рекурсия для левого и правого поддерева
}
//Вызов:
DelLeaf(&der);
cout<<"the tree after deleting of the leafs\n";
if(der)print_tree(der, 0);
else cout<<"empty";

//max в дереве

int searchmax(node *der, int max)
{if(!der)
        return max;
    else
    {
        if(der->info>max)max=der->info;
        max=searchmax(der->left, max);

//можно опустить

        max=searchmax(der->right,max);
        return max;
    }
}//вызов
if(der){int max=der->info;
max=searchmax(der, max);
cout<< " max= " << max);} else cout<<“tree is
empty”;



//прототип функции удаления поддерева
void udalder(node *der);
void udalx(int x, node **ader)
//удаление чисел меньших x
{node *der=*ader; //корень исходного дерева
    if(der==NULL) return;
    if(der->info<x)
    { //оборвать правую ветвь и удалить левое поддерево

        *ader=der->right; //новый корень
        der->right=NULL;
        udalder(der); //удаление левого поддерева
        udalx(x,ader); }

//удаление узлов из правого поддерева
    else if(der->info>x)

        udalx(x,&der->left); /* передаем адрес

указателя на левого потомка в корне дерева */

    else //корень=x
    {udalder(der->left); der->left=NULL; }

}
//удаление поддерева
void udalder(node *der)
{
    if(der==NULL) return;
//удаление левого поддерева
    udalder(der->left);
//удаление правого поддерева
    udalder(der->right) ;
//удаление корня в последнюю очередь
    delete(der);
}


#define max_num 5
/*максимальное число различных марок и
цветов*/

//структурные типы для мультисписка
struct node_mult; //прототип для типа данных об автомобиле

/*тип для массива указателей на автомобиль заданной
марки или цвета*/
struct ptr
{
    char name[20]; //наименование марки или цвета
    node_mult *next; /*указатель на следующий автомобиль
этой марки или цвета*/
};

struct node_mult /*тип для автомобиля*/
{
    ptr mark, color;
    char number[12], owner[20];
};

node_mult *input_auto(void)
{ //ввод полей автомобиля
    node_mult *t=(node_mult *)malloc(sizeof(node_mult));
//выделение памяти
    printf("number :");gets(t->number);
    printf("color :");gets(t->color.name);
    printf("owner :");gets(t->owner);
    printf("mark :");gets(t->mark.name);
    t->color.next=t->mark.next=NULL;
    return t;
}
void print_auto(node_mult *t)
{ //вывод полей автомобиля
    printf("number %s\n",t->number);
    printf("color %s\n",t->color.name);
    printf("owner %s\n",t->owner);
    printf("mark %s\n\n",t->mark.name);
}

//добавление автомобиля к списку
void add_auto(node_mult* new_auto, ptr marks[], int *n_mark,
              ptr colors[], int *n_color)
{
    node_mult *t;
//указатель на текущий автомобиль
    int i; //номер в массиве цветов или марок

//формирование массива марок и списка автомобилей
    for(i=0;i<*n_mark&&strcmp(new_auto->mark.name,
                              marks[i].name)!=0;i++);
//ищем марку, совпадающую с текущей
    if(i==*n_mark) //новая марка
    {
        strcpy(marks[*n_mark].name,new_auto->mark.name);

//заносим ее в массив марок

//поле указателя настраиваем на этот (первый) автомобиль
        marks[*n_mark].next=new_auto; (*n_mark)++;
//увеличиваем число марок
    }
    else //такая марка уже была, на i-м месте
    {
//указывает на первый автомобиль этой марки
        t=marks[i].next;
        while (t->mark.next)
//ищем последний в списке автомобиль этой марки
            t=t->mark.next;
//новый автомобиль размещаем в списке за найденным
        t->mark.next=new_auto;
    }
//аналогичные действия для цветов пропущены
}

//вывод списка марок на экран
void print_mark (ptr marks[],int n_mark)
{
    node_mult *t;
    int i;
    for(i=0;i<n_mark;i++)
    {
        printf("auto %d, mark=%s\n",i,marks[i]. name);
        t=marks[i].next;
        while(t)
        {
            print_auto(t);
            t=t->mark.next;
        }
    }
    puts("");
}
// вывод списка цветов на экран аналогично

int main()
{
//структура с данными об автомобиле
    node_mult*new_auto;
//массив марок и указателей на первый
    ptr marks[max_num]; //автомобиль этой марки
    ptr colors[max_num]; //аналогично для цветов
//количество различных марок и цветов, инициализация
    int n_mark=0, n_color=0; char ans; //ответ пользователя
//формирование списка
    do
    {
//вводим данные об очередном автомобиле
        new_auto=input_auto();
//и добавляем его в список
        add_auto(new_auto, marks, &n_mark,colors, &n_color);

        printf("continue ? (y/n) ");
/* продолжаем ввод пока пользователь отвечает на
вопрос 'Y' или 'y' */
        ans=getchar();
        while(getchar()!='\n');
    }
//пропуск символов до конца строки
    while (ans=='y' || ans==‘Y');
//вывод списка марок и автомобилей этой марки
    puts("list of marks");
    print_mark (marks,n_mark);
//аналогично для цветов
    return 0;
}

