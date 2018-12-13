#include "VG_Vector.hpp"
#include <cassert>
#include <iostream>
#include <vector>
#include <limits>
#include <type_traits>

template <typename V>
class TestVector {
public:
    static V * VectorCreateTest() {
        auto pV = new V;
        assert(pV);
        return pV;
    }

    static void SizeTest(const V * const pV, const typename V::size_type size) {
        assert(pV->size() == size);
    }

    
    static void SizeZeroTest() {
        const typename V::size_type null_size = 0;
        const V test_vector;
        assert(test_vector.size() == null_size);
    }

    static void DeleteVectorTest(V * pV) {
        delete pV;
    }

    static void PushBackTest() {
        typename V::value_type value = 5;
        V test_vector;
        typename V::size_type old_size = test_vector.size();

        test_vector.push_back(value);

        assert(test_vector.size() == old_size + 1);
        //assert(test_vector.back() == value);
    }

    static void ReadAtIndexTest() {
        V test_vector;
        typename V::value_type value = 42;
        test_vector.push_back(value);


        typename V::size_type index = 0;
        auto value_in_vector = test_vector[index];
        std::cout << value_in_vector;
        assert(value_in_vector == value);
    }

    static void ResizeUpTest() {
        V test_vector;
        test_vector.resize(2);
        assert(test_vector.size() == 2);
    }

    static void MaxSizeTest(const V * const pV) {
        assert(pV->max_size() == std::numeric_limits<typename V::size_type>::max());
    }

    static void EmptyTest(const V * const pV) {
        assert(pV->empty() == true);
    }
    
    static void NotEmptyTest() {
        V test_vector;
        typename V::value_type value = 42;
        test_vector.push_back(value);
        assert(test_vector.empty() == false);
    }

    static void SwapTest(V * const pV) {
        
        auto pV1 = VectorCreateTest();
        

        assert(*pV != *pV1);
        
        V copy_pV = *pV;
        V copy_pV1 = *pV1;

        pV->swap(*pV1);

        assert(copy_pV  == *pV1 && copy_pV1 == *pV);
        
        delete pV1;
    }

    static void NotEqTest() {

        V v1, v2;

        v1.push_back(1);

        v2.push_back(1);
        v2.push_back(2);

        assert(v1 != v2);
    }

    static void EqTest(const V * const pV) {
        V copy_V = *pV;
        assert(*pV == copy_V);
    }

    static void BeginReadTest() {
        V test_vector;
        test_vector.push_back(5);
        assert(*(test_vector.begin()) == 5);
    }

    static void VectorIteratorReadValue() {
        V test_vector;
        test_vector.push_back(5);
        typename V::iterator it = test_vector.begin();

        assert(*it == 5);
    }

    static void RunAllTests() {

        auto pV = VectorCreateTest();
        EmptyTest(pV);
        MaxSizeTest(pV);
        SizeZeroTest();
        PushBackTest();
        NotEmptyTest();
        ReadAtIndexTest();
        VectorIteratorReadValue();
        BeginReadTest();
        EqTest(pV);
        NotEqTest();
        // Дописать фабрику
        SwapTest(pV);
        ResizeUpTest();
        DeleteVectorTest(pV);
    }
    
};

void LexicographicalComareTest() {
    char str1[13] = "Test String1";
    char str2[13] = "Test String2";
    char copy_str1[13] = "Test String1";

    bool expectFalse = vg::lexicographical_compare(str1, str1 + 13, str2, str2 + 13);
    bool expectTrue = vg::lexicographical_compare(str1, str1 + 13, copy_str1, copy_str1 + 13);

    assert(expectFalse == false && expectTrue == true);
}

void AlgorithmsTest() {
    LexicographicalComareTest();
}
int main() {
    AlgorithmsTest();
    TestVector<vg::Vector<int>> vector_tests;
    vector_tests.RunAllTests();
    return 0;
}
