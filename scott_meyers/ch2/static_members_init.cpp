#include <iostream>

class MyClass
{
public:
    static int s_member;

    MyClass()
    {
        // Don't initialize static members here!
        std::cout << "MyClass constructor called\n";
    }
};

int MyClass::s_member = 42;  // Define and initialize static member

int main()
{
    std::cout << "MyClass::s_member = " << MyClass::s_member << '\n';

    MyClass obj1;
    std::cout << "MyClass::s_member = " << MyClass::s_member << '\n';

    MyClass obj2;
    std::cout << "MyClass::s_member = " << MyClass::s_member << '\n';

    return 0;
}
/*In this example, the static member s_member is defined and initialized outside of the class definition, with a value of 42. The main function creates two objects of type MyClass, but the static member is only initialized once when the program starts. This is because static members are shared by all objects of the class, and are only initialized once when the program starts.

If you tried to initialize s_member in the class's constructor, like this:

Copy code*/
class MyClass
{
public:
    static int s_member;

    MyClass()
    {
        s_member = 42;  // Don't do this!
        std::cout << "MyClass constructor called\n";
    }
};
/*Then s_member would be initialized every time an object of type MyClass is created, which is not what you want. The output of the program would be:

Copy code
MyClass::s_member = 42
MyClass constructor called
MyClass::s_member = 42
MyClass constructor called
MyClass::s_member = 42
As you can see, s_member is initialized twice, which is not only inefficient, but also not what you want.
*/