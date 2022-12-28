Vaibhav Dahiya
write a custom c++ comparator for hash table of pairs
Sure! Here is a sample comparator function for a hash table of pairs in C++:

Copy code
template <typename T1, typename T2>
struct PairComparator {
  bool operator()(const std::pair<T1, T2> &p1, const std::pair<T1, T2> &p2) const {
    if (p1.first != p2.first) {
      return p1.first < p2.first;
    }
    return p1.second < p2.second;
  }
};
This comparator compares pairs based on their first elements first, and if the first elements are equal, it compares the second elements. You can use this comparator to define a hash table of pairs like this:

Copy code
#include <unordered_map>

std::unordered_map<std::pair<int, int>, int, PairComparator<int, int>> hash_table;
You can also use this comparator with other STL containers that require a comparator, such as std::set or std::map.

I hope this helps! Let me know if you have any questions.




Vaibhav Dahiya
write a custom c++ comparator using static functor for pairs in hash table
Sure! Here is a sample comparator using a static functor for a hash table of pairs in C++:

Copy code
template <typename T1, typename T2>
struct PairComparator {
  static bool compare(const std::pair<T1, T2> &p1, const std::pair<T1, T2> &p2) {
    if (p1.first != p2.first) {
      return p1.first < p2.first;
    }
    return p1.second < p2.second;
  }
};
You can use this comparator to define a hash table of pairs like this:

Copy code
#include <unordered_map>

std::unordered_map<std::pair<int, int>, int, PairComparator<int, int>::compare> hash_table;
You can also use this comparator with other STL containers that require a comparator, such as std::set or std::map.

I hope this helps! Let me know if you have any questions.




Vaibhav Dahiya
remove the template and just use a static function
Sure! Here is a sample comparator using a static function for a hash table of pairs in C++:

Copy code
struct PairComparator {
  static bool compare(const std::pair<int, int> &p1, const std::pair<int, int> &p2) {
    if (p1.first != p2.first) {
      return p1.first < p2.first;
    }
    return p1.second < p2.second;
  }
};
You can use this comparator to define a hash table of pairs like this:

Copy code
#include <unordered_map>

std::unordered_map<std::pair<int, int>, int, PairComparator::compare> hash_table;
You can also use this comparator with other STL containers that require a comparator, such as std::set or std::map.

I hope this helps! Let me know if you have any questions.




Vaibhav Dahiya
can the comparison be avaioded for a better hashing algorithm 
Yes, you can use a hashing function to avoid the need for comparison in a hash table. In C++, you can use a hash function by providing a function object as the third template parameter of std::unordered_map.

Here is an example of using a hash function with std::unordered_map:

Copy code
#include <functional>
#include <unordered_map>

struct PairHash {
  std::size_t operator()(const std::pair<int, int> &p) const {
    // Custom hash function for pairs of ints
    return std::hash<int>()(p.first) ^ std::hash<int>()(p.second);
  }
};

std::unordered_map<std::pair<int, int>, int, PairHash> hash_table;
In this example, the PairHash function object provides a custom hash function for pairs of integers. The hash function computes the hash value by xor-ing the hash values of the pair's first and second elements.

I hope this helps! Let me know if you have any questions.




Vaibhav Dahiya
  can you write how to implement a shared ptr in c++
Sure! Here is an example of how to implement a simple shared pointer in C++:

Copy code
template <typename T>
class SharedPtr {
 public:
  explicit SharedPtr(T *ptr = nullptr) : ptr_(ptr), ref_count_(new std::size_t(1)) {
  }

  SharedPtr(const SharedPtr &other) : ptr_(other.ptr_), ref_count_(other.ref_count_) {
    ++*ref_count_;
  }

  SharedPtr(SharedPtr &&other) : ptr_(other.ptr_), ref_count_(other.ref_count_) {
    other.ptr_ = nullptr;
    other.ref_count_ = nullptr;
  }

  SharedPtr &operator=(const SharedPtr &other) {
    if (this != &other) {
      this->~SharedPtr();
      ptr_ = other.ptr_;
      ref_count_ = other.ref_count_;
      ++*ref_count_;
    }
    return *this;
  }

  SharedPtr &operator=(SharedPtr &&other) {
    if (this != &other) {
      this->~SharedPtr();
      ptr_ = other.ptr_;
      ref_count_ = other.ref_count_;
      other.ptr_ = nullptr;
      other.ref_count_ = nullptr;
    }
    return *this;
  }

  ~SharedPtr() {
    if (ptr_ && --*ref_count_ == 0) {
      delete ptr_;
      delete ref_count_;
    }
  }

  T &operator*() const {
    return *ptr_;
  }

  T *operator->() const {
    return ptr_;
  }

  std::size_t use_count() const {
    return *ref_count_;
  }

  operator bool() const {
    return ptr_ != nullptr;
  }

 private:
  T *ptr_;
  std::size_t *ref_count_;
};
This implementation of shared pointer has a reference count that keeps track of how many shared pointers are pointing to the same object. The reference count is increased when a new shared pointer is created from an existing one, and decreased when a shared pointer goes out of scope or is reset to point to a different object. When the reference count reaches zero, the object is deleted.

I hope this helps! Let me know if you have any questions.




Vaibhav Dahiya
can you explain the copy constructor and = operator
Sure! Here is an explanation of the copy constructor and assignment operator in C++:

Copy Constructor
A copy constructor is a special constructor that is used to create a new object as a copy of an existing object. It is called when an object is initialized from another object, or when an object is passed by value as an argument to a function.

The syntax for a copy constructor is as follows:

Copy code
ClassName(const ClassName &other);
Here, other is a reference to the object being copied. The copy constructor should create a new object that is a copy of other.

For example, consider the following class:

Copy code
class Point {
 public:
  Point(int x = 0, int y = 0) : x_(x), y_(y) {
  }

  Point(const Point &other) : x_(other.x_), y_(other.y_) {
  }

  int x_;
  int y_;
};
Here, the copy constructor Point(const Point &other) creates a new Point object that is a copy of other.

Assignment Operator
The assignment operator is used to assign the value of one object to another object. It is called when an object is assigned the value of another object using the assignment operator =.

The syntax for the assignment operator is as follows:

Copy code
ClassName &operator=(const ClassName &other);
Here, other is a reference to the object being assigned. The assignment operator should assign the value of other to the object on the left hand side of the assignment operator. It should return a reference to the object on the left hand side.

For example, consider the following class:

Copy code
class Point {
 public:
  Point(int x = 0, int y = 0) : x_(x), y_(y) {
  }

  Point &operator=(const Point &other) {
    x_ = other.x_;
    y_ = other.y_;
    return *this;
  }

  int x_;
  int y_;
};
Here, the assignment operator Point &operator=(const Point &other) assigns the value of other to the object on the left hand side of the assignment operator. It returns a reference to the object on the left hand side.

I hope this helps! Let me know if you have any questions.




Vaibhav Dahiya
can you explain the move constructor and move assignment operator in shared ptr implementation above
Sure! In the shared pointer implementation above, the move constructor and move assignment operator are used to implement move semantics in C++.

Move Constructor
The move constructor is a special constructor that is used to create a new object by moving the resources of an existing object. It is called when an object is initialized from another object using move semantics, or when an object is returned by value from a function using move semantics.

The syntax for a move constructor is as follows:

Copy code
ClassName(ClassName &&other);
Here, other is an rvalue reference to the object being moved. The move constructor should create a new object and move the resources of other to the new object. It should leave other in a valid but unspecified state.

For example, consider the following class:

Copy code
class Point {
 public:
  Point(int x = 0, int y = 0) : x_(x), y_(y) {
  }

  Point(Point &&other) : x_(other.x_), y_(other.y_) {
    other.x_ = 0;
    other.y_ = 0;
  }

  int x_;
  int y_;
};
Here, the move constructor Point(Point &&other) creates a new Point object and moves the resources of other to the new object. It sets the x_ and y_ fields of other to zero, leaving other in a valid but unspecified state.

Move Assignment Operator
The move assignment operator is used to assign the value of one object to another object using move semantics. It is called when an object is assigned the value of another object using the assignment operator = with move semantics.

The syntax for the move assignment operator is as follows:

Copy code
ClassName &operator=(ClassName &&other);
Here, other is an rvalue reference to the object being moved. The move assignment operator should move the resources of other to the object on the left hand side of the assignment operator. It should leave other in a valid but unspecified state. It should return a reference to the object on the left hand side.

For example, consider the following class:

Copy code
class Point {
 public:
  Point(int x = 0, int y = 0) : x_(x), y_(y) {
  }

  Point &operator=(Point &&other) {
    x_ = other.x_;
    y_ = other.y_;
    other.x_ = 0;
    other.y_ = 0;
    return *this;
  }

  int x_;
  int y_;
};
Here, the move assignment operator Point &operator=(Point &&other) moves the resources of other to the object on the left hand side of the assignment operator. It sets the x_ and y_ fields of other to zero, leaving other in a valid but unspecified state. It returns a reference to the object on the left hand side.

I hope this helps! Let me know if you have any questions.




Vaibhav Dahiya
can you explain shared ptr implemenatation in c++ in reference to copy ctor and move constructor
Sure! In the shared pointer implementation above, the copy constructor and move constructor are used to create new shared pointers that point to the same object as an existing shared pointer.

The copy constructor is used to create a new shared pointer that shares ownership of the object with the original shared pointer. It increases the reference count of the object, indicating that there is now an additional shared pointer pointing to the object.

The move constructor is used to create a new shared pointer by moving the resources of an existing shared pointer. It takes an rvalue reference to the original shared pointer as an argument, and creates a new shared pointer that points to the same object as the original shared pointer. The original shared pointer is left in a valid but unspecified state.

Here is the implementation of the copy constructor and move constructor in the shared pointer class:

Copy code
SharedPtr(const SharedPtr &other) : ptr_(other.ptr_), ref_count_(other.ref_count_) {
  ++*ref_count_;
}

SharedPtr(SharedPtr &&other) : ptr_(other.ptr_), ref_count_(other.ref_count_) {
  other.ptr_ = nullptr;
  other.ref_count_ = nullptr;
}
In the copy constructor, the new shared pointer is created by copying the ptr_ and ref_count_ fields of the original shared pointer. The reference count is incremented to indicate that there is now an additional shared pointer pointing to the object.

In the move constructor, the new shared pointer is created by moving the ptr_ and ref_count_ fields of the original shared pointer. The original shared pointer is left in a valid but unspecified state by setting its ptr_ and ref_count_ fields to nullptr.

I hope this helps! Let me know if you have any questions.




Vaibhav Dahiya
how about the assignment operator with move semantics
Sure! In the shared pointer implementation above, the assignment operator with move semantics is used to assign the value of one shared pointer to another shared pointer using move semantics.

The move assignment operator takes an rvalue reference to the source shared pointer as an argument, and assigns the value of the source shared pointer to the target shared pointer on the left hand side of the assignment operator. It moves the resources of the source shared pointer to the target shared pointer, and leaves the source shared pointer in a valid but unspecified state.

Here is the implementation of the move assignment operator in the shared pointer class:

Copy code
SharedPtr &operator=(SharedPtr &&other) {
  if (this != &other) {
    this->~SharedPtr();
    ptr_ = other.ptr_;
    ref_count_ = other.ref_count_;
    other.ptr_ = nullptr;
    other.ref_count_ = nullptr;
  }
  return *this;
}
In this implementation, the move assignment operator first checks if the source and target shared pointers are the same. If they are not the same, it calls the destructor of the target shared pointer to release its resources, and then moves the resources of the source shared pointer to the target shared pointer. It leaves the source shared pointer in a valid but unspecified state by setting its ptr_ and ref_count_ fields to nullptr. Finally, it returns a reference to the target shared pointer.

I hope this helps! Let me know if you have any questions.




Vaibhav Dahiya
why unspecified state
In C++, an object is said to be in a valid but unspecified state when it has been moved from, and its value is no longer defined.

When an object is moved from, its resources are transferred to another object, and the original object is left in a valid but unspecified state. This means that the original object still exists and can be used, but its value is no longer defined.

The reason for leaving an object in a valid but unspecified state after it has been moved from is to allow for more efficient implementation of move semantics. By leaving the original object in a valid but unspecified state, the implementation can avoid the overhead of initializing the object to a known state, which may involve allocating and deallocating resources.

However, it is important to note that an object in a valid but unspecified state should not be used, as its value is not defined. Any use of an object in a valid but unspecified state is undefined behavior.

I hope this helps! Let me know if you have any questions.




Vaibhav Dahiya
please use examples to show all of the above
Sure! Here are some examples to illustrate the copy constructor, move constructor, and move assignment operator with move semantics in C++:

Copy code
#include <iostream>
#include <utility>

class Point {
 public:
  Point(int x = 0, int y = 0) : x_(x), y_(y) {
    std::cout << "Point constructed: (" << x_ << ", " << y_ << ")" << std::endl;
  }

  ~Point() {
    std::cout << "Point destructed: (" << x_ << ", " << y_ << ")" << std::endl;
  }

  Point(const Point &other) : x_(other.x_), y_(other.y_) {
    std::cout << "Point copied: (" << x_ << ", " << y_ << ")" << std::endl;
  }

  Point(Point &&other) : x_(other.x_), y_(other.y_) {
    other.x_ = 0;
    other.y_ = 0;
    std::cout << "Point moved: (" << x_ << ", " << y_ << ")" << std::endl;
  }

  Point &operator=(const Point &other) {
    x_ = other.x_;
    y_ = other.y_;
    std::cout << "Point assigned: (" << x_ << ", " << y_ << ")" << std::endl;
    return *this;
  }

  Point &operator=(Point &&other) {
    x_ = other.x_;
    y_ = other.y_;
    other.x_ = 0;
    other.y_ = 0;
    std::cout << "Point moved and assigned: (" << x_ << ", " << y_ << ")" << std::endl;
    return *this;
  }

  int x_;
  int y_;
};

int main() {
  // Copy constructor
  Point p1(1, 2);
  Point p2 = p1;

  // Move constructor



Vaibhav Dahiya
please use shared ptr as example
Sure! Here is an example to illustrate the copy constructor, move constructor, and move assignment operator with move semantics in the shared pointer implementation above:

Copy code
#include <iostream>

template <typename T>
class SharedPtr {
 public:
  explicit SharedPtr(T *ptr = nullptr) : ptr_(ptr), ref_count_(new std::size_t(1)) {
  }

  SharedPtr(const SharedPtr &other) : ptr_(other.ptr_), ref_count_(other.ref_count_) {
    ++*ref_count_;
  }

  SharedPtr(SharedPtr &&other) : ptr_(other.ptr_), ref_count_(other.ref_count_) {
    other.ptr_ = nullptr;
    other.ref_count_ = nullptr;
  }

  SharedPtr &operator=(const SharedPtr &other) {
    if (this != &other) {
      this->~SharedPtr();
      ptr_ = other.ptr_;
      ref_count_ = other.ref_count_;
      ++*ref_count_;
    }
    return *this;
  }

  SharedPtr &operator=(SharedPtr &&other) {
    if (this != &other) {
      this->~SharedPtr();
      ptr_ = other.ptr_;
      ref_count_ = other.ref_count_;
      other.ptr_ = nullptr;
      other.ref_count_ = nullptr;
    }
    return *this;
  }

  ~SharedPtr() {
    if (ptr_ && --*ref_count_ == 0) {
      delete ptr_;
      delete ref_count_;
    }
  }

  T &operator*() const {
    return *ptr_;
  }

  T *operator->() const {
    return ptr_;
  }

  std::size_t use_count() const {
    return *ref_count_;
  }

  operator



Vaibhav Dahiya
please complete
Sure! Here is the rest of the example:

Copy code
#include <iostream>

template <typename T>
class SharedPtr {
 public:
  explicit SharedPtr(T *ptr = nullptr) : ptr_(ptr), ref_count_(new std::size_t(1)) {
  }

  SharedPtr(const SharedPtr &other) : ptr_(other.ptr_), ref_count_(other.ref_count_) {
    ++*ref_count_;
  }

  SharedPtr(SharedPtr &&other) : ptr_(other.ptr_), ref_count_(other.ref_count_) {
    other.ptr_ = nullptr;
    other.ref_count_ = nullptr;
  }

  SharedPtr &operator=(const SharedPtr &other) {
    if (this != &other) {
      this->~SharedPtr();
      ptr_ = other.ptr_;
      ref_count_ = other.ref_count_;
      ++*ref_count_;
    }
    return *this;
  }

  SharedPtr &operator=(SharedPtr &&other) {
    if (this != &other) {
      this->~SharedPtr();
      ptr_ = other.ptr_;
      ref_count_ = other.ref_count_;
      other.ptr_ = nullptr;
      other.ref_count_ = nullptr;
    }
    return *this;
  }

  ~SharedPtr() {
    if (ptr_ && --*ref_count_ == 0) {
      delete ptr_;
      delete ref_count_;
    }
  }

  T &operator*() const {
    return *ptr_;
  }

  T *operator->() const {
    return ptr_;
  }

  std::size_t use_count() const {
    return *ref_count_;
  }

  operator bool() const {
    return ptr_ != nullptr;
  }

 private:
  T *ptr_;
  std::size_t *ref_count_;
};

int main() {
  // Copy constructor
  SharedPtr<int> p1(new int(1));
  std::cout << "p1 use count: " << p1.use_count() << std::endl;
  SharedPtr<int> p2 = p1;
  std::cout << "p1 use count: " <<



Vaibhav Dahiya
please complete
Sure! Here is the rest of the example:

Copy code
#include <iostream>

template <typename T>
class SharedPtr {
 public:
  explicit SharedPtr(T *ptr = nullptr) : ptr_(ptr), ref_count_(new std::size_t(1)) {
  }

  SharedPtr(const SharedPtr &other) : ptr_(other.ptr_), ref_count_(other.ref_count_) {
    ++*ref_count_;
  }

  SharedPtr(SharedPtr &&other) : ptr_(other.ptr_), ref_count_(other.ref_count_) {
    other.ptr_ = nullptr;
    other.ref_count_ = nullptr;
  }

  SharedPtr &operator=(const SharedPtr &other) {
    if (this != &other) {
      this->~SharedPtr();
      ptr_ = other.ptr_;
      ref_count_ = other.ref_count_;
      ++*ref_count_;
    }
    return *this;
  }

  SharedPtr &operator=(SharedPtr &&other) {
    if (this != &other) {
      this->~SharedPtr();
      ptr_ = other.ptr_;
      ref_count_ = other.ref_count_;
      other.ptr_ = nullptr;
      other.ref_count_ = nullptr;
    }
    return *this;
  }

  ~SharedPtr() {
    if (ptr_ && --*ref_count_ == 0) {
      delete ptr_;
      delete ref_count_;
    }
  }

  T &operator*() const {
    return *ptr_;
  }

  T *operator->() const {
    return ptr_;
  }

  std::size_t use_count() const {
    return *ref_count_;
  }

  operator bool() const {
    return ptr_ != nullptr;
  }

 private:
  T *ptr_;
  std::size_t *ref_count_;
};

int main() {
  // Copy constructor
  SharedPtr<int> p1(new int(1));
  std::cout << "p1 use count: " << p1.use_count() << std::endl;
  Shared



Vaibhav Dahiya
lets just start from main function to complete
Sure! Here is an example to illustrate the copy constructor, move constructor, and move assignment operator with move semantics in the shared pointer implementation above, starting from the main function:

Copy code
#include <iostream>

template <typename T>
class SharedPtr {
 public:
  explicit SharedPtr(T *ptr = nullptr) : ptr_(ptr), ref_count_(new std::size_t(1)) {
  }

  SharedPtr(const SharedPtr &other) : ptr_(other.ptr_), ref_count_(other.ref_count_) {
    ++*ref_count_;
  }

  SharedPtr(SharedPtr &&other) : ptr_(other.ptr_), ref_count_(other.ref_count_) {
    other.ptr_ = nullptr;
    other.ref_count_ = nullptr;
  }

  SharedPtr &operator=(const SharedPtr &other) {
    if (this != &other) {
      this->~SharedPtr();
      ptr_ = other.ptr_;
      ref_count_ = other.ref_count_;
      ++*ref_count_;
    }
    return *this;
  }

  SharedPtr &operator=(SharedPtr &&other) {
    if (this != &other) {
      this->~SharedPtr();
      ptr_ = other.ptr_;
      ref_count_ = other.ref_count_;
      other.ptr_ = nullptr;
      other.ref_count_ = nullptr;
    }
    return *this;
  }

  ~SharedPtr() {
    if (ptr_ && --*ref_count_ == 0) {
      delete ptr_;
      delete ref_count_;
    }
  }

  T &operator*() const {
    return *ptr_;
  }

  T *operator->() const {
    return ptr_;
  }

  std::size_t use_count() const {
    return *ref_count_;
  }

  operator bool() const {
    return ptr_ != nullptr;
  }

 private:
  T *ptr_;
  std::size_t *ref_count_;
};

int main() {
  // Copy constructor
  SharedPtr<int> p1(new int(1));
  std::cout << "p1 use count: " << p1.use_count() << std::endl;
  SharedPtr<int> p2 = p1;
  std::cout << "p1 use count: " << p1.use_count() << std::endl;

  // Move constructor
  SharedPtr<int> p3(std::move(p1));
  std::cout << "p3 use count: " << p3.use_count() << std::endl;
  if (p1) {
    std::cout << "p1 value: " << *p1 << std::endl;
  } else



Vaibhav Dahiya
please complete
Sure! Here is the rest of the example:

Copy code
#include <iostream>

template <typename T>
class SharedPtr {
 public:
  explicit SharedPtr(T *ptr = nullptr) : ptr_(ptr), ref_count_(new std::size_t(1)) {
  }

  SharedPtr(const SharedPtr &other) : ptr_(other.ptr_), ref_count_(other.ref_count_) {
    ++*ref_count_;
  }

  SharedPtr(SharedPtr &&other) : ptr_(other.ptr_), ref_count_(other.ref_count_) {
    other.ptr_ = nullptr;
    other.ref_count_ = nullptr;
  }

  SharedPtr &operator=(const SharedPtr &other) {
    if (this != &other) {
      this->~SharedPtr();
      ptr_ = other.ptr_;
      ref_count_ = other.ref_count_;
      ++*ref_count_;
    }
    return *this;
  }

  SharedPtr &operator=(SharedPtr &&other) {
    if (this != &other) {
      this->~SharedPtr();
      ptr_ = other.ptr_;
      ref_count_ = other.ref_count_;
      other.ptr_ = nullptr;
      other.ref_count_ = nullptr;
    }
    return *this;
  }

  ~SharedPtr() {
    if (ptr_ && --*ref_count_ == 0) {
      delete ptr_;
      delete ref_count_;
    }
  }

  T &operator*() const {
    return *



Vaibhav Dahiya
how to save this entire conversation
To save this entire conversation, you can simply copy and paste the text into a text editor or word processor of your choice. Alternatively, you can use the "Print" function in your web browser to save the conversation as a PDF or print it out on paper.

I hope this helps! Let me know if you have any other questions.




Vaibhav Dahiya
but how to save entire conversation when using chrome, print just selects last page
To save the entire conversation when using Google Chrome, you can try the following steps:

Right-click on any blank area of the conversation and select "Inspect" from the context menu. This will open the developer console.
In the developer console, go to the "Elements" tab.
Find the element that contains the entire conversation and click on it to highlight it in the HTML code.
Right-click on the highlighted element and select "Copy > Copy element" from the context menu.
Open a text editor or word processor of your choice and paste the copied element into it.
Alternatively, you can try the following steps:

Press "Ctrl + A" to select the entire conversation.
Press "Ctrl + C" to copy the selected text.
Open a text editor or word processor of your choice and press "Ctrl + V" to paste the copied text into it.
I hope these steps help! Let me know if you have any other questions.




Vaibhav Dahiya
but I would like to copy it with colours and like a webpage
To save the entire conversation with colors and formatting, you can try the following steps:

Right-click on any blank area of the conversation and select "Inspect" from the context menu. This will open the developer console.
In the developer console, go to the "Elements" tab.
Find the element that contains the entire conversation and click on it to highlight it in the HTML code.
Right-click on the highlighted element and select "Copy > Copy element" from the context menu.
Open a HTML editor or word processor with HTML support (such as Microsoft Word or Google Docs) and paste the copied element into it.
Alternatively, you can try the following steps:

Press "Ctrl + A" to select the entire conversation.
Press "Ctrl + C" to copy the selected text.
Open a HTML editor or word processor with HTML support (such as Microsoft Word or Google Docs) and press "Ctrl + V" to paste the copied text into it.
I hope these steps help! Let me know if you have any other questions.




ChatGPT Dec 15 Version. Free Research Preview. Our goal is to make AI systems more natural and safe to interact with. Your feedback will help us improve.
New chat
Custom C++ Comparator for Pairs


Investing 100000 In US
New Chat
New chat
New chat
New chat
New chat
New chat
Clear conversations
Dark mode
OpenAI Discord
Updates & FAQ
Log out
We're experiencing exceptionally high demand. Please hang tight as we work on scaling our systems.
