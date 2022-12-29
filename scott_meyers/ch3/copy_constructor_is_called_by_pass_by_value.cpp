Copy code
class MyClass {
 public:
  // default constructor
  MyClass() {
    std::cout << "Default constructor called" << std::endl;
  }

  MyClass(int x) : x_(x) {}

  // copy constructor
  MyClass(const MyClass& other) {
    std::cout << "Copy constructor called" << std::endl;
    x_ = other.x_;
  }

  int x_;
};

void func(MyClass obj) {
  obj.x_ = 5;
}

int main() {
  MyClass obj;  // default constructor called
  func(obj);
  std::cout << obj.x_ << std::endl;  // prints 0
}
In this example, the default constructor of MyClass is called when the object obj is created using the default constructor. The message "Default constructor called" will be printed when the default constructor is called.




Vaibhav Dahiya
output of this code
The output of this code will be:

Copy code
Default constructor called
Copy constructor called
0
The first line is printed by the default constructor when it is called to create the object obj. The second line is printed by the copy constructor when the object obj is passed by value to the function func. The third line is printed by the main function after calling the func function.
