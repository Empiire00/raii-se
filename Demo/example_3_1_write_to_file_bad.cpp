#include <cstdio>
#include <iostream>
#include <string>
 // exceptions
 class file_error { } ;
 class open_error : public file_error { } ;
 class close_error : public file_error { } ;
 class write_error : public file_error { } ;

void write_to_file_bad(const std::string path, const std::string content)
{
  // open file
  std::FILE* file_handle = std::fopen(path.c_str(), "w+") ;
  if( file_handle == NULL )
  {
    throw open_error() ;
  } 
  try
  {
    if( std::fputs(content.c_str(), file_handle) == EOF )
    {
      throw write_error() ;
    }
  }
  // catch errors
  catch(...)
  {
    // manually close file
    std::fclose(file_handle) ;
    // re-throw the exception we just caught
    throw ;
  }
  // manually close file
  std::fclose(file_handle) ;
}
int main(){
  try{
    write_to_file_bad("test.txt", "Hello world!");
  }
  catch(file_error& e){
    std::cout << "Error" << std::endl;
  }
  return 0;

}