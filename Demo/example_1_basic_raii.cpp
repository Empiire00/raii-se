#include <iostream>
class IntArray{
    private:
        int* data;
    public:
        // Acquisition of data in constructor
        IntArray(const int size){
            std::cout << "Hi from constructor" << std::endl; 
            data = new int[size];
            std::cout << "Initialized array" << std::endl;
        }
        int* getData(){
            return data;
        }
        // Freeing resource in destructor
        ~IntArray() { 
            std::cout << "Hi from destructor" << std::endl;
            delete[] data; 
            std::cout << "Freed array resource" << std::endl;
        }
};

int main() {
    {
        IntArray arr(5);
    }
    std::cout << "arr out of scope now" << std::endl;
}