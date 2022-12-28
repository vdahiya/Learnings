#include <iostream>
#include <new>

class X
{
public:
    X() { std::cout << "X Constructor" << std::endl; }
    ~X() { std::cout << "X Destructor" << std::endl; }

    static void* operator new(std::size_t size, std::new_handler p = 0)
    {
        std::cout << "X Class Overloaded 'new' operator called" << std::endl;

        // Set the new-handling function
        std::set_new_handler(p);

        // Allocate the requested memory
        void* ptr = ::operator new(size);

        // Reset the new-handling function to the default
        std::set_new_handler(nullptr);

        return ptr;
    }
};

void specialErrorHandler()
{
    std::cout << "specialErrorHandler called" << std::endl;
}

int main()
{
    try
    {
        // Allocate memory for an X object using the overloaded new operator
        // with the specialErrorHandler function as an argument
        X* xPtr = new (specialErrorHandler) X;

        // Deallocate the memory using the default delete operator
        delete xPtr;
    }
    catch (const std::bad_alloc& ex)
    {
        // Handle a std::bad_alloc exception thrown by the default new operator
        std::cout << "std::bad_alloc exception: " << ex.what() << std::endl;
    }

    try
    {
        // Allocate memory for an X object using the overloaded new operator
        // with the specialErrorHandler function as an argument
        X* xPtr = new  X;

        // Deallocate the memory using the default delete operator
        delete xPtr;
    }
    catch (const std::bad_alloc& ex)
    {
        // Handle a std::bad_alloc exception thrown by the default new operator
        std::cout << "std::bad_alloc exception: " << ex.what() << std::endl;
    }

    return 0;
}
