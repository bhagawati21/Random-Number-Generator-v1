#include "randnum.h"
#include <ctime>
#include <cstdlib>

RANDNUM::RANDNUM()
{
    char_str = "0123456789""!@#$%&*/\?""abcdefghijklmnopqrstuvwxyz""ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    num_str = "0123456789";
    schar_str = "!@#$%&*/\?";
    alpha_str = "abcdefghijklmnopqrstuvwxyz""ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    alpha_num = "0123456789""abcdefghijklmnopqrstuvwxyz""ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    alpha_schar = "!@#$%&*/\?""abcdefghijklmnopqrstuvwxyz""ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    num_schar = "0123456789""!@#$%&*/\?";
    srand(time(NULL));
}

string RANDNUM::GenerateRandNum(bool Schar, bool Num, bool Alpha, int length)
{
    string RandNumber;
    if(Schar && !Num && !Alpha)
        for (int i=1; i<=length; i++)
        RandNumber.push_back(schar_str[rand() % schar_str.length()]);

    else if(Num && !Alpha && !Schar)
        for (int i=1; i<=length; i++)
        RandNumber.push_back(num_str[rand() % num_str.length()]);

    else if(Alpha && !Num && ! Schar)
        for (int i=1; i<=length; i++)
        RandNumber.push_back(alpha_str[rand() % alpha_str.length()]);

    else if(Alpha && Num && !Schar)
        for (int i=1; i<=length; i++)
        RandNumber.push_back(alpha_num[rand() % alpha_num.length()]);

    else if(Alpha && Schar && ! Num)
        for (int i=1; i<=length; i++)
        RandNumber.push_back(alpha_schar[rand() % alpha_schar.length()]);

    else if(Num && Schar && !Alpha)
        for (int i=1; i<=length; i++)
        RandNumber.push_back(num_schar[rand() % num_schar.length()]);

    else
        for (int i=1; i<=length; i++)
        RandNumber.push_back(char_str[rand() % char_str.length()]);

    return RandNumber;
}
