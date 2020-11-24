#include <iostream>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE* file;
    file = fopen("data.txt", "w");
    int count = 100000;
    fprintf(file, "%d\n", count);
    for (int i = 0; i < count; i++)
    {
        int x = rand() % 200 - 100;
        int y = rand() % 200 - 100;
        int r = rand() % 400;
        fprintf(file, "%11d %11d %11d\n", x, y, r);
    }
    fclose(file);
    std::cout << "Done" << std::endl;
    return 0;
}
