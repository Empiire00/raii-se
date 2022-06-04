#include <iostream>
int main() {
    int* p = new int();
    *p = 26;
    char* q = new char();
    *q = 'A';
    delete(q);
    delete(p);
    std::cout << "p out of scope" << std::endl;
    std::cout << "q out of scope" << std::endl;

    return 0;
}