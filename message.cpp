#include "stdafx.h"
#include <stdio.h>
#include <conio.h>
#include <math.h>

char** inputlist(int*, int*);
char** alloclist(int, int);
void transform(char**, char*, int, int);
void surnames(char**, int, int);
void outputlist(char**, int, int);
int strlen(char*);
char* strstr(char*, char*);
int checksurnames(char*, char*);
char* strchr(char*, char*, char);
void delstring(char*, int);
void insstring(char*, char*);

int main()
{
    int n, m;
    char** list = inputlist(&n, &m); 
    surnames(list, n, m);
    outputlist(list, n, m);
    getch();
}

void surnames(char** list, int n, int m) // функция поиска и изменения фамилий
{
    char change[] = "ov ";  // окончание которое нужно изменить
    char insert[] = "idze "; // окончание на которое нужно изменить
    for (int i = 0; i <= n; i++) 
    {
        char* p = strstr(*list + i * m, change);
        while (p != NULL) // проверяем, пока есть окончания, которые нужно изменить
            {
                if ( strchr(*list + i * m, p, ' ') == NULL ) // проверка на фамилию ( если нет пробелов, то фигачим )
                {
                    delstring(p, strlen(change));
                    insstring(p, insert);
                }
                p = strstr(p + 1, change);
            }
    }
}

char** inputlist(int* n, int* m)  // ввод списка ( массива строк )
{ 
    printf("enter a number of persons\n");
    scanf("%i", n);
    printf("enter maximum length of one name\n");
    scanf("%i", m);
    (*m)++;
    printf("enter names\n");
    char** list = alloclist(*n, *m);
    for (int i = 0; i <= *n; i++)
        gets_s(*(list + i), *m);
    return list;
}

char** alloclist(int n, int m)
{
    char** list = new char* [n];
    char* string = new char [n * m];
    transform(list, string, n, m);
    return list;
}

void transform(char** list, char* string, int n, int m)
{
    for (int i = 0; i <= n; i++)
        *(list + i) = string + i * m;
}

void outputlist(char** list, int count, int m)  // вывод списка ( массива строк )
{
    for (int i = 0; i <= count; i++)
        puts(*list + i * m);
} 

char* strchr(char* start, char* end, char ch)  // поиск символа в строке на интервале от start до end
{
    char* p;
    for (p = start; p <= end && *p != ch; p++);
    return *p == ch ? p : NULL;
}

void delstring(char* start, int len)  // удаление подстроки длины len из строки
{
    for (char* p = start; p < start + strlen(start) - len; p++)
        *p = *(p + len);
    *(start + strlen(start) - len) = '\0';
}

void insstring(char* start, char* insert) // вставка подстроки в строку
{
    for (char* p = start + strlen(start) + strlen(insert); p >= start ; p--)  // раздвигаем
        *p = *(p - strlen(insert));
    int counter = 0;
    for (char* p = start; p < start + strlen(insert); p++) // вставляем
    {
        *p = *(insert + counter);
        counter++;
    }
}

int strlen(char* string)  // длина строки
{
    int k = 0;
    for (char* i = string; *i != '\0'; i++)
        k++;
    return k;
}

char* strstr(char* s, char* subs) // поиск подстроки в строке
{
    int key = 0;
    char* p;
    for (p = s; *p && !key;)
    {
        unsigned i;
        for (i = 0; subs[i] && p[i] == subs[i]; i++);
            if (!subs[i])
                key = 1;
            else
                p++;
    }
    return key ? p : 0;
}