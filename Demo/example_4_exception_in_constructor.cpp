#include <iostream>
#include <string>
class Resource{
    public:
    Resource(){
        value = new int();
        std::cout << "Allocated resources" << std::endl;
    }
    ~Resource(){
        delete(value);
        std::cout << "Freed resources" << std::endl;
    }
    private:
    int* value; 
};
class ResourceWrapper{
    public:
    ResourceWrapper(){
        data = Resource();
        // if for some reason, there is a function that throws an exception in 
        // the constructor, the
        // compiler makes sure, that the deconstructor functions of all objects are called
        throw "Some exception";
    }
    private:
        Resource data;
};
int main(){
    ResourceWrapper test = ResourceWrapper();
    return 0;
}