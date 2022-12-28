#include <iostream>
#include <vector>

template<class T>
class Array {
public:
    Array (int lowBound, int highBound);
    std::vector<T>& getData();

private:
    std::vector<T> data;
    size_t size;
    int lBound, hBound;
};

template<class T>
Array<T>::Array (int lowBound, int highBound)
: size (highBound - lowBound + 1), lBound (lowBound), hBound (highBound) , data (size)
{}

template<class T>
std::vector<T>& Array<T>::getData() {
    return data;
}

int main() {
    Array<int> arr(0, 9);
    std::vector<int>& data = arr.getData();
    std::cout << "Number of elements in data: " << data.size() << std::endl;
    return 0;
}
