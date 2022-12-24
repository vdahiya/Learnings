#include <iostream>

class AirplaneRep { /* ... */ };  // Forward declaration for AirplaneRep class

class Airplane {
public:
    // Custom memory management
    static void* operator new(size_t size);
    static void operator delete(void* ptr, size_t size);

private:
    union {
        AirplaneRep* rep;
        Airplane* next;
    };

    // Class-specific constant (number of objects that fit in a memory block)
    static const int BLOCK_SIZE;

    // Pointer to the head of the free list
    static Airplane* headOfFreeList;
};

const int Airplane::BLOCK_SIZE = 256;  // Initialize the constant
Airplane* Airplane::headOfFreeList = nullptr;  // Initialize the free list

// Custom operator new function for Airplane objects
void* Airplane::operator new(size_t size)
{
    // Delegate requests of the "wrong" size to ::operator new()
    if (size != sizeof(Airplane))
        return ::operator new(size);

    Airplane* p = headOfFreeList;  // p is now a pointer to the head of the free list

    // If p is valid, just move the list head to the next element in the free list
    if (p)
        headOfFreeList = p->next;
    else {
        // The free list is empty. Allocate a block of memory big enough to hold BLOCK_SIZE Airplane objects
        Airplane* newBlock = static_cast<Airplane*>(::operator new(BLOCK_SIZE * sizeof(Airplane)));

        // Form a new free list by linking the memory chunks together; skip the zeroth element, because you'll return that to the caller of operator new
        for (int i = 1; i < BLOCK_SIZE - 1; ++i)
            newBlock[i].next = &newBlock[i + 1];

        // Terminate the linked list with a null pointer
        newBlock[BLOCK_SIZE - 1].next = nullptr;

        // Set p to front of list, headOfFreeList to chunk immediately following
        p = newBlock;
        headOfFreeList = &newBlock[1];
    }
    return p;
}

// Custom operator delete function for Airplane objects
void Airplane::operator delete(void* ptr, size_t size)
{
    // Delegate requests of the "wrong" size to ::operator delete()
    if (size != sizeof(Airplane))
    {
        ::operator delete(ptr);
        return;
    }

    Airplane* p = static_cast<Airplane*>(ptr);  // Convert the void* to an Airplane*

    // Add the deleted Airplane object to the head of the free list
    p->next = headOfFreeList;
    headOfFreeList = p;
}


int main()
{
    // Create a new Airplane object using the custom operator new function
    Airplane* p1 = new Airplane;
    std::cout << "p1: " << p1 << std::endl;

    // Create another Airplane object using the custom operator new function
    Airplane* p2 = new Airplane;
    std::cout << "p2: " << p2 << std::endl;

    // Create an array of 10 Airplane objects using the custom operator new function
    Airplane* p3 = new Airplane[10];
    std::cout << "p3[0]: " << p3 << std::endl;
    std::cout << "p3[1]: " << p3 + 1 << std::endl;
    std::cout << "p3[2]: " << p3 + 2 << std::endl;
    std::cout << "p3[3]: " << p3 + 3 << std::endl;
      std::cout << "p3[3]: " << p3 + 3 << std::endl;
    std::cout << "p3[4]: " << p3 + 4 << std::endl;
    std::cout << "p3[5]: " << p3 + 5 << std::endl;
    std::cout << "p3[6]: " << p3 + 6 << std::endl;
    std::cout << "p3[7]: " << p3 + 7 << std::endl;
    std::cout << "p3[8]: " << p3 + 8 << std::endl;
    std::cout << "p3[9]: " << p3 + 9 << std::endl;

    // Delete the dynamically-allocated objects
    delete p1;
    delete p2;
    delete[] p3;
}