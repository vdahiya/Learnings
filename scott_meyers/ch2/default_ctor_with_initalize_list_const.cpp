/*const and reference members can only be initialized, and cannot be assigned to after they are initialized. This means that if you want to initialize a const or reference member, you must use an initialization list.

Here is an example of a class template Foo that has a const member and a reference member:*/


template<typename T>
class Foo {
public:
    Foo(const T& initVal, const T& initConst, T& initRef)
        : val(initVal), constVal(initConst), ref(initRef) {}

    T val;
    const T constVal;
    T& ref;
};

int main() {
    int x = 42;
    const int y = 123;
    int z = 456;

    // Initialize Foo object using an initialization list
    Foo<int> foo1(x, y, z);

    std::cout << "foo1.val: " << foo1.val << std::endl;
    std::cout << "foo1.constVal: " << foo1.constVal << std::endl;
    std::cout << "foo1.ref: " << foo1.ref << std::endl;

    return 0;
}
/*In this example, the Foo class template has a constructor that takes three arguments: a value of type T, a const value of type T, and a reference to an object of type T. The constructor initializes the member variables val, constVal, and ref using an initialization list.

The main function creates a Foo object using the Foo constructor, passing in three values of type int. The output of this program will be:

Copy code
foo1.val: 42
foo1.constVal: 123
foo1.ref: 456
If we tried to use assignment statements in the constructor body instead of an initialization list, the code would not compile, because the const and reference members cannot be assigned to. For example, the following code would not be valid:

Copy code*/
template<typename T>
class Foo {
public:
    Foo(const T& initVal, const T& initConst, T& initRef) {
        val = initVal;
        constVal = initConst;  // Error: cannot assign to const member
        ref = initRef;
    }

    T val;
    const T constVal;
    T& ref;
};
/*In this case, the line constVal = initConst; would generate a compile-time error, because the constVal member is a const member and cannot be assigned to.*/