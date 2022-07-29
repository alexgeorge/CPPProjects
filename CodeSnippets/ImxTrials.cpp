// ImxTrials.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <iostream>

void CheckConst(const int *var1, int *const var2, const int *const var3)
{
    int test = 100;
    var1 = &test; //you can change the address of var1 but not value *var1 (same as int const*)
    *var2 = test; //you can change the value *var2 but not the address
    //*var3 = &test; //you cant change value or address
    printf("Value [%d- at %d]  [%d- at %d]\n", *var1, var1, *var2, var2);
}

void CheckLambdaExpr()
{
    char s[] = "This is a test!";
    int uc = 0; //modified by lambda
    std::string strTest = "Another test!";
}

//functor example
class CAddFunctor
{
public:
    CAddFunctor(int x) : x(x) { printf("Ctor [%d]\n", x); }
    int operator() (int y) const { printf("Functor [%d]\n", x);  return x + y; }
private:
    int x = 0; //c++ 11 allows this
};

class CUpperFunctor
{
public:
    CUpperFunctor(char c)  { C = std::toupper(c); printf("Ctor [%c]\n", C); }
    char operator() (char y) const { char Y = std::toupper(y); printf("Functor [%c]\n", Y);  return Y; }
private:
    char C; //c++ 11 allows this
};


void CheckFunctor()
{
    CAddFunctor add100(100);
    int funRet = add100(200);
    printf("Functor output %d \n", funRet);

    //elaborate example
    std::vector <char> in = { "a","l" };// , 'e', 'x', 'v', 'g', 'e', 'o', 'r', 'g', 'e'
    int nSize = in.size();
    std::vector <char> out(nSize);
    std::vector <char> store(nSize);

    //pass the functor to std::transform, which calls functor for every element
    //in the input sequence and stores the result to the output sequence
    std::transform(in.begin(), in.end(), out.begin(),store,CAddFunctor(2));
    printf("Output from functor [%d] ", out[2]);
}


int main()
{
    const int a1 = 10;
    int a2 = 20;
    const int a3 = 30;
    CheckConst(&a1, &a2, &a3);
    printf("After [%d- at %d] [%d- at %d]\n", a1,&a1,a2,&a2);
    CheckFunctor();
    return 0;
}

