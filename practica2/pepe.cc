#include <iostream>
#include <termios.h>
#include <unistd.h>
#include "myvector.h"

int main() {

    Myvector<int> myvector;
    myvector.push_back(5);
    myvector.push_front(3);
    myvector.push_back(7);
    myvector.push_front(1);
    for (int i = 0; i < myvector.size(); i++) {
        std::cout << myvector[i] << std::endl;
    }
    return 0;
}