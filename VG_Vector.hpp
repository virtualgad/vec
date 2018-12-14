#ifndef VG_VECTOR_HPP
#define VG_VECTOR_HPP
#include "VG.hpp"

namespace VG {

    template <typename T>
    class Vector {
    public:
        using value_type            = T;
        using reference             = T&;
        using const_reference       = const T&;
        using iterator              = T*;
        using const_iterator        = const T*;
        using difference_type       = signed long;
        using size_type             = size_t;
    
    public:
        explicit Vector(size_type s = 0, T t = T()) {
            if (s) {
                reserve(s);
                //m_pData = new T[s];
                for(Vector::size_type i = 0; i != s; ++i)
                    new (m_pData + i) T(t);
            }
            m_Size = s;
        }

        Vector(const Vector &another) {
            if (another.m_Size != 0) {
                reserve(another.m_Size);
                //m_pData = new T[another.m_Size];

                for(Vector::size_type i = 0; i != another.m_Size; ++i) {
                    new (m_pData + i) T(another.m_pData[i]);
                }
            }
            m_Size = another.m_Size;
        }

        Vector(const Vector &&another) {
            swap(const_cast<Vector &>(another));
        }
        
        ~Vector() {
            if (m_Size != 0) {
                for(size_type i = 0; i != m_Size; ++i)
                    m_pData[i].~T();

                delete [] m_pData;
            }
        }

        Vector & operator = (const Vector &another) {
            if(this == &another)
                return *this;

            Vector tmp(another);
            this->swap(tmp);

            return *this;
        }

        Vector & operator = (Vector &&another) {
            swap(another);
            return *this;
        }

        void swap(Vector &another) {
            if (this == &another)
                return;

            auto tmp_Data = another.m_pData;
            auto tmp_Size = another.m_Size;

            another.m_pData = m_pData;
            another.m_Size = m_Size;

            m_pData = tmp_Data;
            m_Size  = tmp_Size;
        }

        size_type size () const {return m_Size;}
        size_type max_size () const { return -1;};
        size_type capacity () const { return m_capacity;};
        bool empty () const {return m_Size == 0;}
        const_iterator begin () const {return m_pData;}
        const_iterator end () const   {return m_pData + m_Size;}
        const_iterator cbegin () const {return begin();}
        const_iterator cend () const   {return end();}
        

        const value_type & back () const {
            return m_pData[m_Size - 1];
        }

        void push_back(const value_type &t) {
            reserve(m_Size + 1);
            new (m_pData+m_Size) T(t);
            ++m_Size;
        }

        void pop_back() {
            if(empty())
                return;
            back().~T();
            --m_Size;
        }

        void reserve (size_type new_cap) {
            if (new_cap <= m_capacity) {
                return;
            }
                
            
            m_capacity = (m_capacity ? ((new_cap / m_capacity < 2? m_capacity * 2: new_cap)): new_cap);

            auto newData = new value_type[m_capacity];
            
            for(size_type i = 0; i != m_Size; ++i) {
                    new (newData + i) T(m_pData[i]);
                    m_pData[i].~T();
            }

            delete [] m_pData;
            m_pData = newData;
        }

        iterator begin () {return m_pData;}
        iterator end ()   {return m_pData + m_Size;}
    private:
        T *m_pData = nullptr;
        size_type m_Size = 0;
        size_type m_capacity = 0;
    };


    template <typename T>
    bool operator == (const Vector<T> &first, const Vector<T> &second) {
        
        if(first.size() != second.size()) 
            return false;
        if(first.size() == 0 && second.size() == 0)
            return true;

        auto f_it = first.begin();
        auto s_it = second.begin();
        

        while (f_it != first.end() || s_it != second.end()) {
            if (*f_it++ != *s_it++) {
                return false;
            }
        }

        return true;
    }
    
    template <typename T>
    bool operator != (const Vector<T> &first, const Vector<T> &second) {
        return !(first == second);
    }

     template <typename T>
     void swap(Vector<T>&first, Vector<T>&second) {
         first.swap(second);
     }
}


#endif // !VG_VECTOR_HPP

