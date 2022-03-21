#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cstring>
#include "big_num.h"
using namespace std;
BN :: BN (int ml, int t)
{
    if (t == 1)
    {
        len = 1;
        maxlen = 1;
        coef = new BASE [maxlen];
        coef[0] = 0;
    }
    else if (t == 2)
    {
        len = 1;
        maxlen = ml;
        coef = new BASE [maxlen];
        for (int i = 0; i < len; coef[i] = 0, i++);
    }
    else
    {
        len = ml;
        maxlen = ml;
        coef = new BASE [maxlen];
        srand(time(0));
        
        for (int i = 0; i < len; i++)
        {
            coef[i] = rand();
            if (BASE_SIZE > 16)
            {
            // от 0 до 2^16  #1
            coef[i] << 16;
            coef[i] = rand();
            }  
        }
        int i;
        for(i = len - 1; coef[i] == 0; i--);
        len = i + 1;
    }
}
BN :: BN (BN &c)
{
    coef = new BASE [c.maxlen];
    for (len = 0; len < c.len; len++)
    {
        c[len] = c.coef[len];
    }
}

BN & BN :: operator = (BN & arr)
{
    if (this != &arr)
    {
        delete []coef;
        coef = new BASE [maxlen = arr.maxlen];
        len = arr. len;
        for (int i = 0; i < len; i++)
        {
            coef[i] = arr. coef[i];
        }
    }
    return *this;
}

BASE & BN :: operator [] (int i)
{
    if ((i < 0) || (i >= len))
    {
        cout << "Index outside" << endl;
        exit (1);
    }
    return coef[i];
}

void BN :: output_16 ()
{
    char *s = new char [len*BASE_SIZE/4];
    int i = 0, k = BASE_SIZE - 4;
    int tmp;
    for (int j = len-1; j >= 0; )
    {
        tmp = (coef[j] >> k)&(0xf);
        if ((tmp <= 9) && (tmp >= 0))
        {
            s[i] = (char)(tmp + '0');
        }

        if ((tmp <= 15) && (tmp >= 10))
        {
            s[i] = (char)(tmp - 10 + 'a');
        }

        i++; k -= 4;
        if (k < 0)
        {
            k = BASE_SIZE - 4;
            j--;
        }
    }
    s[i] = '\0';
    fputs (s, stdout);
    cout << endl;
    return;
}

void BN :: input_16 (const char *s)
{ // char, short, int
    len = (strlen(s) - 1)/(BASE_SIZE/4) + 1;
    maxlen = len;
    delete []coef;
    coef = new BASE [maxlen];
    int j = 0, k = 0, tmp = 0;
    for (int i = strlen(s) - 1; i >= 0; i--)
    {
        if ((s[i] <= '9')&&(s[i] >= '0'))
        {
            tmp = s[i] - '0';
        }

        if ((s[i] <= 'f')&&(s[i] >= 'a'))
        {
            tmp = s[i] - 'a' + 10;
        }

        if ((s[i] <= 'F')&&(s[i] >= 'A'))
        {
            tmp = s[i] - 'A' + 10;
        }

        if (!((s[i] <= '9')&&(s[i] >= '0')))
        {
            if (!((s[i] <= 'f')&&(s[i] >= 'a')))
            {
                if (!((s[i] <= 'F')&&(s[i] >= 'A')))
                {
                    cout << "Invalid character" << endl;
                    exit(1);
                }
            }
        }

        coef[j] |= tmp << (k*4);
        k++;
        if (k >= BASE_SIZE/4)
        {
            k = 0;
            j++;
        }
    }

    int i;
    for(i = len - 1; coef[i] == 0; i--);
    len = i + 1;
    return;    
}

bool BN :: operator > (BN & number)
{
    int t = this -> cmp (number);
    if (t == 1)
    {
        return true;
    }
    return false;
}

bool BN :: operator < (BN & number)
{
    int t = this -> cmp (number);
    if (t == -1)
    {
        return true;
    }
    return false;
}

bool BN :: operator == (BN & number)
{
    int t = this -> cmp (number);
    if (t == 0)
    {
        return true;
    }
    return false;
}

bool BN :: operator != (BN & number)
{
    int t = this -> cmp (number);
    if (t != 0)
    {
        return true;
    }
    return false;
}

bool BN :: operator >= (BN & number)
{
    int t = this -> cmp (number);
    if ((t == 0) || (t == 1))
    {
        return true;
    }
    return false;
}

bool BN :: operator <= (BN & number)
{
    int t = this -> cmp (number);
    if ((t == 0) || (t == -1))
    {
        return true;
    }
    return false;
}

int BN :: cmp (BN & number) // < -1; == 0; > 1;
{
    if (len > number.len)
    {
        return 1; 
    }
    if (len < number.len)
    {
        return -1;
    }

    for (int j = len - 1; j >=0; j--)
    {
        if (coef[j] > number.coef[j])
        {
            return 1;
        }
        if (coef[j] < number.coef[j])
        {
            return -1;
        }
    }
    return 0;
}

ostream & operator << (ostream &res, BN &c)
{
    for (int i = 0; i < c.len; i++)
    {
        res << c[i] << " ";
    }
    return res;
}
