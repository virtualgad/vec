#include <iostream>
#include "VectorTests.hpp"
//#include "VG_Vector.hpp"

class TestType1 {
public:
    ~TestType1() = delete;
};

class TestType2 {
public:
    explicit TestType2(int v = 42): val(v) {}
    int Get() const {return val;}
private:
    int val;
};

bool operator == (const TestType2 &t1, const TestType2 &t2) {
    return t1.Get() == t2.Get();
}

bool operator != (const TestType2 &t1, const TestType2 &t2) {
    return !(t1 == t2);
}


int main () {
    using T = TestType2; // test with non zero data
    //using T = std::function<void(void)>;
    //using T = TestType; // Assert if type did't have desctructor
    VectorTests<T> vector_tests;
    // FAIL - because was not all functionality added
    std::cout << (vector_tests() ? "FAIL": "OK") << std::endl;
}