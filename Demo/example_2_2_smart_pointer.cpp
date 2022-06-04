#include <iostream>
// this template class is used to define a smart pointer of a given type
template <class T>
class SmartPointer {
   private:
    T* p;  // pointer of type T
   public:
    // Constructor - initialize resource
    SmartPointer(T* ptr = NULL) { 
        std::cout << "Allocated resources for pointer of type " << typeid(T).name() << std::endl;
        p = ptr; 
    }
    // Destructor - Free resource
    ~SmartPointer() { 
        std::cout << "Freeing resources for pointer of type " << typeid(T).name() << std::endl;
        delete (p); 
    }
    // Overload operators to allow usage of them
    // -> Dereference operator
    T& operator*() { 
        return *p; 
    }
};
int main() {
    SmartPointer<int> p(new int());
    *p = 26;
    SmartPointer<char> q(new char());
    *q = 'A';
    std::cout << "p out of scope" << std::endl;
    std::cout << "q out of scope" << std::endl;

    return 0;
}