## 1 - Basic RAII Example 
- [Basic RAII](/Demo/example_1_basic_raii.cpp)  
  
This example demonstrates the idea of RAII. A wrapper class `IntArray` is used to wrap an int array (resource).
In the `main` method an object is created with 
```cpp
IntArray arr(5);
```
This statement calls the constructor of IntArray, which initializes the resource.
As soon as the variable looses its scope (which is after the block is exited), the variable `arr` is out of scope, thus, 
its deconstructor is called. In the deconstructor, the memory is released using
```cpp
delete[] data;
```

## 2 - Pointers
- [Smart Pointers - Bad](/Demo/example_2_1_smart_pointer_bad.cpp)
- [Smart Pointers - RAII](/Demo/example_2_2_smart_pointer.cpp)
  
The first example code snippet shows the lack of RAII:  
A new `int` and `char` variable is initialized on heap using the `new` keyword.
However, every acquired memory is to be released after use in order to prevent [memory leaks](https://en.wikipedia.org/wiki/Memory_leak).
In this example, this is done using the `delete` statement for **every** pointer **manually**.
In this small code snippet, it might be easy to remember to free up memory, but if the complexity increases, it gets harder to keep track of.  
The second example shows a RAII implementation:  
A `SmartPointer` template class takes care of managing memory. 
In `SmartPointer`'s constructor, the memory is allocated.
In its deconstructor, the memory is freed.
That is why you can instantiate a wrapped pointer by using the wrapper class like 
```cpp
SmartPointer<int> p(new int());
```
and whenever the SmartPointer instance moves out of scope, the memory is freed automatically.

## 3 - Writing to Files
- [Writing to Files - Bad](/Demo/example_3_1_write_to_file_bad.cpp)
- [Writing to Files - RAII](/Demo/example_3_2_write_to_file.cpp)
  
This example shows another possible use case for RAII:  
Similar to [this example](#2---Pointers), the use case of writing to a resource (e.g. a file) is shown to 
demonstrate a more complex example:  
A file is opened using `std::fopen(path.c_str(), "w+")`, thus needs to be closed after the process is done.
Though, there are some possible exceptions that can occur while trying to write/read files, that have to be handled by the program.
In this case, there are several times, when `std::fclose(file_handle)` is called.  
However, if one forgets to call this function, the file (or resource in general) is never released, which may cause problems.  
  
In other words: RAII ensures proper release of a resource, if there are several possible paths for a program (exceptions,control structures, etc.).

## 4 - Exceptions in Constructor
- [Exceptions in Constructor](/Demo/example_4_exception_in_constructor.cpp)
  
In _C++_, it is ensured, that a deconstructor is called even if the problem throws exceptions.  
`ResourceWrapper` wraps an RAII like resource called `Resource`. We deliberately throw an exception in `ResourceWrapper`'s constructor after having initialized the resource with
```cpp
data = Resource();
```
If you look at the program's output, you can see, that the deconstructor of `Resource` is called even though the program crashes.
That would not be possible, if `Resource` was not handled RAII-like.


## 5 - Threads and Mutex
- [Threads](/Demo/example_5_threads_mutex.cpp)
  
In this example, we use RAII to handle a lock object resource (mutex).
We create a `Guard` instance with 
```cpp
Guard g = Guard(mutex);
```
and while g is in scope, the mutex object will be locked. This ensures, that each individual thread will only be able to write its character
(see `printBlock`) while no other thread is doing so.
Using RAII, we do not have to take care of acquiring and releasing the lock object, since the `Guard` class takes care of that task.  
