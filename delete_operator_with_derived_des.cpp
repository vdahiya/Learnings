#include <iostream>

struct Base {
    // virtual ~Base() {}  // Comment out virtual destructor
    int x;
};

struct Derived : public Base {
    int y;
};

void operator delete(void* p, size_t size) {
    std::cout << "Deleting object of size: " << size << std::endl;
    // Release memory here
}

int main() {
    std::cout << "Without virtual destructor:" << std::endl;
    Base* b = new Derived;
    delete b;  // Output: "Deleting object of size: 4"

    std::cout << "\nWith virtual destructor:" << std::endl;
    struct Base {
        virtual ~Base() {}  // Add virtual destructor
        int x;
    };
    b = new Derived;
    delete b;  // Output: "Deleting object of size: 8"

    return 0;
}
