#include <iostream>
#include <fstream>
#include "bmp.hpp"



int main()
{

    BMP kl;
    kl.read();

    int g;
    std::cin >> g;
    char w[10];
    for (int i = 0; i < g; i++) {
        std::cin >> w[i];
    }
   
    kl.shifr(w, g);
   kl.antishifr();
    kl.create();




}