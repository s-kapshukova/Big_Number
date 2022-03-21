#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cstring>
#include "big_num.cpp"
using namespace std;

int main ()
{   
    BN num1, num2 (8, 2), num3 (8, 3);
    BN num4;
    cout << "num 3: " << num3 << endl;
    num3.output_16();

    cout << "------------------" << endl;
    char *str = new char [100];  
    gets(str);
    num4.input_16(str);
    cout << "num 4: " << num4 << endl;
    num4.output_16();
    
    cout << "------------------" << endl;
    cout << "> : " << (num3 > num4) << endl;
    cout << "< : " << (num3 < num4) << endl;
    cout << "== : " << (num3 == num4) << endl;
    cout << "!= : " << (num3 != num4) << endl;
    cout << ">= : " << (num3 >= num4) << endl;
    cout << "<= : " << (num3 <= num4) << endl;
    
    delete []str;
    return 0;
}