#include <QCoreApplication>
#include <QDebug>
#include <windows.h>
#include <iostream>
#include <cstdio>

using namespace std;
//origin, grapher, gnuplot, excel, ....
//100\t1\t1\t1\t1\t1\n
//299\t4\t


void sort1(int* a, int _size) //Пузырьковая
{
    for(int i = 0; i < _size; i++)
    {
        for(int j = 0; j < _size - 1; j++)
        {
            if(a[j] > a[j+1])
            {
                int korobka = a[j];
                a[j] = a[j+1];
                a[j+1] = korobka;
            }
        }
    }
}
void sort2(int* a, int _size) //Вставками
{
    for (int i = 1; i < _size; i++)
    {
        for (int z = 0; z < i; z++)
        {
            if (a[z] > a[i])
            {
                for (int d = z; d < i; d++)
                {
                    int temp = a[d];
                    a[d] = a[i];
                    a[i] = temp;
                }
                break;
            }
        }
    }
}
void sort3(int* a, int _size) //Выбором
{
    for (int i = 0; i < _size; i++)
    {
        int tek_min;
        tek_min = i;
        for (int t = i; t < _size; t++)
        {
            if (a[t] < a[tek_min])
            {
                tek_min = t;
            }
        }
        int temp = a[tek_min];
        a[tek_min] = a[i];
        a[i] = temp;
    }
}

void sort4(int* mas, int size) //Быстрая
{
    //Указатели в начало и в конец массива
    int i = 0;
    int j = size - 1;

    //Центральный элемент массива
    int mid = mas[size / 2];

    //Делим массив
    do {
        //Пробегаем элементы, ищем те, которые нужно перекинуть в другую часть
        //В левой части массива пропускаем(оставляем на месте) элементы, которые меньше центрального
        while (mas[i] < mid) {
            i++;
        }
        //В правой части пропускаем элементы, которые больше центрального
        while (mas[j] > mid) {
            j--;
        }

        //Меняем элементы местами
        if (i <= j) {
            int tmp = mas[i];
            mas[i] = mas[j];
            mas[j] = tmp;

            i++;
            j--;
        }
    } while (i <= j);


    //Рекурсивные вызовы, если осталось, что сортировать
    if (j > 0) {
        //"Левый кусок"
        sort4(mas, j + 1);
    }
    if (i < size) {
        //"Правый кусок"
        sort4(&mas[i], size - i);
    }
}

//Слиянием
void merge(int* mas, int l, int r) // ФУНКЦИЯ СЛИЯНИЯ!
{                                  // l - левая часть(начало). r - правая(конеЦ).
    int i = l;
    int mid = l + (r - l) / 2;
    int j = mid + 1;
    int pos = 0;
    int* new_mass;
    new_mass = new int[r-l+1];
    while (i <= mid && j <= r)
    {
        if (mas[i] < mas[j])
        {
            new_mass[pos++] = mas[i++];
        }
        else
        {
            new_mass[pos++] = mas[j++];
        }
    }
    while (i <= mid)
    {
        new_mass[pos++] = mas[i++];
    }
    while (j <= r)
    {
        new_mass[pos++] = mas[j++];
    }
    for (int i = l; i <= r; i++)
    {
        mas[i] = new_mass[i - l];
    }
    delete[] new_mass;
}

void sort5(int* mas, int l, int r)
{
    if (r <= l) //Если конец = начало, то в массиве 1 эл-т. Если конец < начала - нельзя сортировать.
    {
        return;
    }
    int mid = l + (r - l) / 2;
    sort5(mas, l, mid);
    sort5(mas, mid + 1, r);
    merge(mas, l, r);
}


void sort6(int* mas, int size) //Сортировка гномиком.
{
    for (int i = 1; i < size; )
    {
        if (mas[i] < mas[i - 1])
        {
            int temp;
            temp = mas[i];
            mas[i] = mas[i - 1];
            mas[i - 1] = temp;
            if (i - 1 > 0)
            {
                i--;
            }
            else
            {
                    i++;
            }
        }
        else
        {
            i++;
        }

    }
}

void sort7(int* mas, int l, int r) //Неправильно реализованная быстрая сортировка.
{
    if (l >= r)
    {
        return;
    }
    int mid = l+(r-l)/2;
    for (int i = l; i < mid; i++)
    {
        if (mas[i] >= mas[mid])
        {
            int temp = mas[i];
            mas[i] = mas[mid - 1];
            mas[mid - 1] = mas[mid];
            mas[mid] = temp;
            mid--;
            i--;
        }
    }
    for (int i = mid; i <= r; i++)
    {
        if (mas[i] < mas[mid])
        {
            int temp = mas[i];
            mas[i] = mas[mid + 1];
            mas[mid + 1] = mas[mid];
            mas[mid] = temp;
            mid++;
            i--;
        }
    }

        sort7(mas, l, mid);
        sort7(mas, mid + 1, r);
}

void randomFill(int* a, int _size)
{
    for(int i = 0; i < _size; i++)
    {
        // srand (time(NULL));
        int z = (rand());
        a[i] = z;
    }
}
void durSortToFile(long int time, int _size)
{
    FILE* f1;
    f1 = fopen("MySort.txt", "a");
    fprintf(f1, "%d\t%ld\t", _size, time);
    fclose(f1);
}
void durSortToFile(long int time)
{
    FILE* f1;
    f1 = fopen("MySort.txt", "a");
    fprintf(f1, "%ld\t", time);
    fclose(f1);
}

void nextSize(int *q)
{
    if(1000000 <= *q && *q <= 10000000)
    {
       *q += 200000;
    }
    if(100000 <= *q && *q <= 1000000)
    {
       *q += 20000;
    }
    if(10000 <= *q && *q <= 100000)
    {
       *q += 1000;
    }
    if(1000 <= *q && *q <= 10000)
    {
       *q += 100;
    }
 if(100 <= *q && *q <= 1000)
 {
    *q += 10;
 }
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    int *my_array;
       long int stop1;
       long int stop2;
       long int stop3;
       long int stop4;
       long int stop5;
       long int stop6;
       long int stop7;

       for (int size = 100; size < 10000000; ) {
           my_array = new int [size];
           long int time;
           if(stop1<=50000)
           {
               randomFill(my_array, size);
               time = GetTickCount();
               sort1(my_array, size);
               time = GetTickCount() - time;
               durSortToFile(time, size);
               stop1 = time;
           }
           else
           {
               durSortToFile(stop1, size);
           }

           if(stop2 < 50000)
           {
               randomFill(my_array, size);
               time = GetTickCount();
               sort2(my_array, size);
               time = GetTickCount() - time;
               durSortToFile(time);
               stop2 = time;
           }
           else
           {
               durSortToFile(stop2);
           }

           if(stop3 < 50000)
           {
               randomFill(my_array, size);
               time = GetTickCount();
               sort3(my_array, size);
               time = GetTickCount() - time;
               durSortToFile(time);
               stop3 = time;
           }
           else
           {
               durSortToFile(stop3);
           }

           if(stop4< 50000)
           {
               randomFill(my_array, size);
               time = GetTickCount();
               sort4(my_array, size);
               time = GetTickCount() - time;
               durSortToFile(time);
               stop4 = time;
           }
           else
           {
               durSortToFile(stop4);
           }

           if(stop5<50000)
           {
               randomFill(my_array, size);
               time = GetTickCount();
               sort5(my_array, 0, size-1);
               time = GetTickCount() - time;
               durSortToFile(time);
               stop5 = time;
           }
           else
           {
               durSortToFile(stop5);
           }

           if(stop6<50000)
           {
               randomFill(my_array, size);
               time = GetTickCount();
               sort6(my_array, size);
               time = GetTickCount() - time;
               durSortToFile(time);
               stop6 = time;
           }
           else
           {
               durSortToFile(stop6);
           }

           if(stop7<50000)
           {
               randomFill(my_array, size);
               time = GetTickCount();
               sort7(my_array, 0, size-1);
               time = GetTickCount() - time;
               durSortToFile(time);
               stop7 = time;
           }
           else
           {
               durSortToFile(stop7);
           }

        nextSize(&size);

        delete [] my_array;
        FILE* f1;
        f1 = fopen("MySort.txt", "a");
        fprintf(f1, "\n");
        fclose(f1);
    }

    return a.exec();
}
