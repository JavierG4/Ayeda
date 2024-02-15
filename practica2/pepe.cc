#include <iostream>
#include <termios.h>
#include <unistd.h>

int getch() {
    struct termios oldattr, newattr;
    int ch;
    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
    return ch;
}

int main() {
    char input;
    while (true) {
        std::cout << "Press any key to quit, Space to continue: ";
        input = getch();
        if (input != ' ') {
            break;
        }
    }
    return 0;
}