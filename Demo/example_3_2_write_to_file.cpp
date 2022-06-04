#include <cstdio>
#include <iostream>
//  exceptions 
class file_error {};
class open_error : public file_error {};
class close_error : public file_error {};
class write_error : public file_error {};

class File {
   public:
    File(const char* filename) : file_handle(std::fopen(filename, "w+")) {
        if (file_handle == NULL) {
            throw open_error();
        }
    }

    ~File() { 
        // close file in destructor only
        std::fclose(file_handle); 
    }

    void write(const char* str) {
        if (std::fputs(str, file_handle) == EOF) {
            throw write_error();
        }
    }

    void write(const char* buffer, std::size_t num_chars) {
        if (num_chars != 0 &&
            std::fwrite(buffer, num_chars, 1, file_handle) == 0) {
            throw write_error();
        }
    }

   private:
    std::FILE* file_handle;
    // copy and assignment operator not implemented;
    // prevent their use by declaring private.
    File(const File&);
    File& operator=(const File&);
};

void write_to_file_raii(){
    File file("myFile.txt");
    file.write("Alice says 'Hello' to Bob");
}
int main(){
    try{
        write_to_file_raii();
    }
    catch(file_error& e){
        std::cout << "Error" << std::endl;
    }
    return 0;
}
