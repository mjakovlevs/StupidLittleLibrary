#include <iostream>


void printInt(const int& integer)
{
    std::cout << integer << std::endl;
}

int main()
{
    int x = 12;

    printInt(x);

    return 0;
}