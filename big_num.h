#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cstring>
using namespace std;

typedef unsigned short BASE;
#define BASE_SIZE (sizeof(BASE)*8)

class BN
{
    BASE *coef;
    int len;
    int maxlen;
    public:
    //Конструктор с параметром t:
    //t = 1 - по умолчанию
    //t = 2 - maxlen передаем через параметр, и все цифры числа заполняем нулями
    //t = 3 - maxlen передаем через параметр и цифры заполняем случайными числами
    BN (int ml = 1, int t = 1); //Конструктор
    BN (BN &); //Конструктор копирования
    ~ BN () //Деструктор
    {
        delete []coef;
        len = 0;
        maxlen = 0;
    }
    BN & operator = (BN &);
    BASE & operator [] (int i);
    
    void output_16 ();
    void input_16 (const char *s);
    
    int cmp (BN &);
    bool operator > (BN &);
    bool operator < (BN &);
    bool operator == (BN &);
    bool operator != (BN &);
    bool operator >= (BN &);
    bool operator <= (BN &);
    
    friend ostream & operator << (ostream &res, BN &c);
};