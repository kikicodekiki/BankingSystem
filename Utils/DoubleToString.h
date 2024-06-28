#include <iostream>
#include <cmath> // For floor and pow

char getCharFromDigit(int digit)
{
    if (digit < 0 || digit > 9)
        return '\0';
    return digit + '0';
}

unsigned getNumberLength(unsigned long long n)
{
    if (n == 0)
        return 1;
    unsigned int res = 0;

    while (n != 0)
    {
        res++;
        n /= 10;
    }
    return res;
}

void toString(unsigned long long n, char* str)
{
    unsigned int len = getNumberLength(n);

    for (int i = len - 1; i >= 0; i--)
    {
        str[i] = getCharFromDigit(n % 10);
        n /= 10;
    }
    str[len] = '\0';
}

const char* doubleToString(double num, int precision)
{
    static char str[100];
    if (precision < 0) {
        precision = 0; // Ensure precision is non-negative
    }

    // Handle negative numbers
    bool isNegative = num < 0;
    if (isNegative) {
        num = -num;
    }

    // Extract integer part
    unsigned long long integerPart = static_cast<unsigned long long>(num);

    // Extract fractional part
    double fractionalPart = num - static_cast<double>(integerPart);
    unsigned long long fractionalPartAsInt = static_cast<unsigned long long>(fractionalPart * pow(10, precision));

    // Convert integer part to string
    char integerStr[50];
    toString(integerPart, integerStr);

    // Convert fractional part to string
    char fractionalStr[50];
    toString(fractionalPartAsInt, fractionalStr);

    // Combine integer and fractional parts
    if (isNegative) {
        str[0] = '-';
        str[1] = '\0';
        strcat(str, integerStr);
    } else {
        strcpy(str, integerStr);
    }

    if (precision > 0) {
        strcat(str, ".");
        strcat(str, fractionalStr);
    }

    return str;
}



const char*  toString(unsigned int n)
{
    char str [100];
    unsigned int len = getNumberLength(n);

    for (int i = len - 1; i >= 0; i--)
    {
        str[i] = getCharFromDigit(n % 10);
        n /= 10;
    }
    str[len] = '\0';

    return str;
}

MyString parseEgn(const size_t EGN[10]) {
    char egnStr[11];
    for (size_t i = 0; i < 10; ++i) {
        if (EGN[i] > 9) {
            throw std::runtime_error("Invalid EGN number.");
        }
        egnStr[i] = '0' + EGN[i];
    }
    egnStr[10] = '\0';
    return MyString(egnStr);
}
