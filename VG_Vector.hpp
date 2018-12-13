#ifndef VG_VECTOR_HPP
#define VG_VECTOR_HPP
#include "VG.hpp"
#include "VG_Algorithm.hpp"

//DEBUG
//#include <iostream>


namespace vg {

    template <typename T>
    class Vector {
    public: 
        using size_type = vg::size_type;
        using value_type = T;
        using iterator =  T*;
        
    public:
        iterator begin() const {
            return m_pData;
        }

        iterator end() const{
            return m_pData + m_size;
        }
    public:
        Vector(): m_size(), m_pData(nullptr) {}

        size_type size() const {
            return m_size;
        }

        void resize(size_type count, const T & value = T()) {
            
            auto pNewData = new T [count];

            copy(m_pData, m_pData + m_size, pNewData);

            // change to foo: fill
            for(size_type i = 0; i != (count - m_size); ++i) {
                pNewData[m_size + i] = value;
            }

            vg::swap(m_pData, pNewData);
            ++m_size;
            delete [] pNewData;
        }

        static constexpr size_type max_size () {
            return 0xFFFFFFFFFFFFFFFF; 
        }

        void push_back (const T & value) {
            resize(m_size + 1, value);
        }

        const T & back() const {
            return m_pData[m_size - 1];
        }

        const T & operator[](size_type index) const {
            return m_pData[index];
        }

        bool empty() const {
            return !m_size;
        }
        
        void swap(Vector<T> &another) {
            vg::swap(this->m_pData, another.m_pData);
            vg::swap(this->m_size, another.m_size);
        }

        ~Vector() {
            delete [] m_pData;
        }
        //const T & operator [] (Vector::size_type) const;
    private:
        size_type m_size;
        T * m_pData;
    };
    
    template <typename T>
    bool operator == (const Vector<T> & first, const Vector<T> & second) {
            return (first.size() == second.size() 
                    && vg::lexicographical_compare( first.begin(), first.end(), 
                                                second.begin(), second.end())
                    );
    }

    template <typename T>
    bool operator != (const Vector<T> & first, const Vector<T> & second ) {
            return !(first == second);
    }

    
}

#endif // !VG_VECTOR_HPP


