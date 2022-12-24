struct Base {
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
    Base* b = new Derived;
    delete b;  // Output: "Deleting object of size: 4"
    return 0;
}
