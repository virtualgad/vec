#ifndef VECTOR_TESTS_HPP
#define VECTOR_TESTS_HPP

#include <type_traits>
#include <iterator>
#include <limits>
#include <cassert>
#include <memory>
#include <algorithm>
#include <utility>
#include <functional>
#include <vector>

#include "VG_Vector.hpp"

template <typename T>
class VectorTests {
public:
    using X = VG::Vector<T>;
   
public:
    int operator () ();

private:
    void DefaultConstructorTest();
    void CopyConstructorTest();
    void MoveConstructorTest();
    void ConstructorFromContainerSizeTest();
    void AssignTest();
    void MoveAssignTest();
    void SizeTest();
    void MaxSizeTest();
    void EmptyTest();
    void PushBackTest();
    void ReserveTest();
    void CapacityTest();
    void PopBackTest();
private:
    static void StaticTest();
};


template <typename T>
void VectorTests<T>::StaticTest() {
    static_assert(std::is_same<typename X::value_type, T>::value, "Error: X::value_type must be T");
    static_assert(std::is_destructible<T>::value, "T must be erasable from X");
    static_assert(std::is_same<typename X::reference, T&>::value, "Error: X::reference must be T&");
    static_assert(std::is_same<typename X::const_reference, const T&>::value, "Error: X::const_reference must be const T&");
    static_assert(std::is_same<typename X::iterator, T*>::value, "Error: X::iterator must be const forward it from T");
    static_assert(std::is_convertible<typename X::iterator, typename X::const_iterator>::value, "Error: X::iterator must be convertible to X::const_iterator");
    // TODO: Check const
    //static_assert(std::is_const<typename std::iterator_traits<typename X::const_iterator>::value_type>::value, "Error: X::const_iterator must be const");

    static_assert(std::is_same<typename std::iterator_traits<typename X::const_iterator>::difference_type, 
                               typename std::iterator_traits<typename X::iterator>::difference_type>
                               ::value, "Error: X::iterator::d_t must be  equal to the X::const_iterator::d_t");

    static_assert(std::is_same<typename X::difference_type, 
                               typename std::iterator_traits<typename X::iterator>::difference_type>
                               ::value, "Error must be equal to the X::iterator::d_t");

    static_assert(std::is_signed<typename X::difference_type>::value && 
                  std::is_integral<typename X::difference_type>::value, 
                  "Error: X::difference_type must be signed integer ");

    static_assert(std::is_unsigned<typename X::size_type>::value && std::is_integral<typename X::size_type>::value, 
                  "X::size must be integer and unsigned");

    static_assert(std::numeric_limits<typename X::size_type>::max() >= std::numeric_limits<typename X::difference_type>::max(),
                  "Error: size_type can represent any non-negative value of X::difference_type");
    
}

template <typename T>
void VectorTests<T>::ReserveTest() {
    X a;
    a.reserve(42);
    assert(a.capacity() >= 42);
}

template <typename T>
void VectorTests<T>::CapacityTest() {
    X a;
    auto t = T();
    a.push_back(t);
    assert(a.capacity() >= a.size());
}

template <typename T>
void VectorTests<T>::PushBackTest() {
    X a;
    auto t = T();
    a.push_back(t);
    assert(a.back() == t);
}

template <typename T>
void VectorTests<T>::PopBackTest() {
    X a;
    auto t = T();
    a.push_back(t);
    a.pop_back();
    assert(a.empty());
    assert(a.capacity() > a.size());
}

template <typename T>
void VectorTests<T>::SizeTest() {
    auto t = T();
    X a(42, t);
    assert(std::distance(a.begin(), a.end()) == 42);
}

template <typename T>
void VectorTests<T>::MaxSizeTest() {
    X a;
    assert(a.max_size() == std::numeric_limits<typename X::size_type>::max());
}

template <typename T>
void VectorTests<T>::EmptyTest() {
    X a;
    assert(a.begin() == a.end());
    X b(42);
    assert(b.begin() != b.end());
}


template <typename T>
void VectorTests<T>::AssignTest() {
    auto t = T();
    X a;
    X b(24, t);
    a = b;
    assert(a == b);
    a = X(420, t);
    assert(a.size() == 420);
}


template <typename T>
void VectorTests<T>::MoveAssignTest() {
    auto t = T();
    X a(42, t);
    X b;
    b = std::move(a);
    assert(a == X());
}


template <typename T>
void VectorTests<T>::DefaultConstructorTest() {
    X u;
    assert(u.empty());
    auto res = X().empty();
    assert(res);
    assert(u == X(u));
}
template <typename T>
void VectorTests<T>::MoveConstructorTest() {
}

template <typename T>
void VectorTests<T>::CopyConstructorTest() {
    X vo(42);
    X vc(vo);
    assert(vc == vo);
    X va = vo;
    assert(va == vo);
    X vn;    
    vn = vo;
    assert(vn == vo);
}

template <typename T>
void VectorTests<T>::ConstructorFromContainerSizeTest() {
    auto t = T();
    X v(42, t);
    assert(v.size() == 42);
    std::for_each(v.begin(), v.end(), [t] (const T &x){assert(x == t);});
}

template <typename T>
int VectorTests<T>::operator() () {
    StaticTest();
    DefaultConstructorTest();
    CopyConstructorTest();
    ConstructorFromContainerSizeTest();
    MoveConstructorTest();
    AssignTest();
    MoveAssignTest();
    SizeTest();
    MaxSizeTest();
    EmptyTest();
    PushBackTest();
    ReserveTest();
    PopBackTest();
    return true;
}
#endif // !VECTOR_TESTS_HPP

