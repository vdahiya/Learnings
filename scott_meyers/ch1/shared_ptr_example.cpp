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
  } else {
     std::cout << "p1 no value " << std::endl;
  }
 
  SharedPtr<int> p4 = std::move(p2);

  if (p2) {
    std::cout << "p2 value: " << *p2 << std::endl;
  } else {
     std::cout << "p2 no value " << std::endl;
  }
  
  std::cout << "p3 use count: " << p3.use_count() << std::endl;
  std::cout << "p4 use count: " << p4.use_count() << std::endl;

  SharedPtr<int> p5 = p3;

  SharedPtr<int> p6(p4);

  std::cout << "p5 use count: " << p5.use_count() << std::endl;
  std::cout << "p6 use count: " << p6.use_count() << std::endl;


  return 0;
  }
