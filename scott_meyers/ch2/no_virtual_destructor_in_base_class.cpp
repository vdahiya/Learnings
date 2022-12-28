Here is an example of how deleting a derived class object through a base class pointer with a non-virtual destructor can result in undefined behavior:

Copy code
#include <iostream>

class EnemyTarget {
public:
    EnemyTarget() { ++numTargets; }
    EnemyTarget(const EnemyTarget&) { ++numTargets; }
    ~EnemyTarget() { --numTargets; }
    static size_t numberOfTargets() { return numTargets; }

private:
    static size_t numTargets;
};
size_t EnemyTarget::numTargets = 0;

class EnemyTank: public EnemyTarget {
public:
    EnemyTank() { ++numTanks; }
    EnemyTank(const EnemyTank& rhs) : EnemyTarget(rhs) { ++numTanks; }
    ~EnemyTank() { --numTanks; }
    static size_t numberOfTanks() { return numTanks; }

private:
    static size_t numTanks;
};
size_t EnemyTank::numTanks = 0;

int main()
{
    EnemyTarget *targetPtr = new EnemyTank;
    std::cout << "Number of targets: " << EnemyTarget::numberOfTargets() << std::endl;
    std::cout << "Number of tanks: " << EnemyTank::numberOfTanks() << std::endl;

    delete targetPtr;
    std::cout << "Number of targets after delete: " << EnemyTarget::numberOfTargets() << std::endl;
    std::cout << "Number of tanks after delete: " << EnemyTank::numberOfTanks() << std::endl;

    return 0;
}
When this code is run, the output may be different depending on the specific implementation of the destructors and the memory management of the system. For example, the output could be:

Copy code
Number of targets: 1
Number of tanks: 1
Number of targets after delete: 0
Number of tanks after delete: 0
or it could be:

Copy code
Number of targets: 1
Number of tanks: 1
Number of targets after delete: -1
Number of tanks after delete: 0
or it could be any other combination of values. The problem is that the base class destructor is not virtual, so when it is called through the base class pointer, it will only invoke the base class destructor and not the derived class destructor. This means that the derived class object is not properly destroyed, which can cause memory leaks and other issues.

To fix this issue, you can make the destructor in the base class virtual, which will ensure that the derived class destructor is called when the object is deleted through a base class pointer. Here is the modified code with a virtual destructor:

Copy code
#include <iostream>

class EnemyTarget {
public:
    EnemyTarget() { ++numTargets; }
    EnemyTarget(const EnemyTarget&) { ++numTargets; }
    virtual ~EnemyTarget() { --numTargets; } // make destructor virtual
    static size_t numberOfTargets() { return numTargets; }

private:
    static size_t numTargets;