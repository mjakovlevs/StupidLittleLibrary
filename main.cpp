#include <iostream>

#include "Log.h"
#include "Common.h"

struct Test
{
    uint8_t b1 : 2;
    uint8_t b2 : 2;
};


void printInt(const int& integer)
{
    std::cout << integer << std::endl;
}

int main()
{
    Test test = {4, 2};

    foo::llog("Hello world!");

    int x = 12;

    printInt(x);

    return 0;
}