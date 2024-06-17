#pragma once
#include <iostream>
#include <vector>

namespace Tensor{

    struct TensorFormat{
       std::vector<unsigned int> strides;
       unsigned int rank;
       std::vector<unsigned int> layout;

       unsigned int totalLength();
    }typedef TensorFormat;

    template <class T>
    class TensorDataStructure{
        private:
            std::vector<T> data;
            TensorFormat format;
            int getFinalIndex(std::vector<unsigned int>& index);

        public:
            TensorDataStructure(TensorFormat& format);
            void setData(T* d);
            std::vector<unsigned int> getStrides();
            unsigned int getRank();
            std::vector<unsigned int> getLayout();
            T* getRawData();
            void print();
            T getValue(std::vector<unsigned int>& index);
            void setValue(std::vector<unsigned int>& index, T value);
    };
}