#ifndef VG_ALGORITHM_HPP
#define VG_ALGORITHM_HPP
namespace vg {

    template <typename InputIt, typename OutputIt>
    OutputIt copy (InputIt input_first, InputIt input_last, const OutputIt output) {
        auto tmp_out = output;
        while (input_first != input_last ) {
            *tmp_out++ = *input_first++;
        }
        return tmp_out;
    }

    template <typename T>
    void swap (T * first, T * second)
    {
        auto tmp = first;
        first = second;
        second = tmp;
    }

    template <typename T>
    void swap (T & first, T & second)
    {
        auto tmp = first;
        first = second;
        second = tmp;
    }

    template <typename FirstIt, typename SecondIt>
    bool lexicographical_compare(FirstIt first_begin, FirstIt first_end,
                                 SecondIt second_begin, SecondIt second_end) {
        while (first_begin != first_end && second_begin != second_end) {
            if(*first_begin != *second_begin) return false;

            ++first_begin;
            ++second_begin;
        }

        return true;
    }
    
}

#endif // !VG_ALGORITHM_HPP