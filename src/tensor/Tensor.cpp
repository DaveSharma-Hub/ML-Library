#include "Tensor.hpp"
#include "./util/util.hpp"
#include <iostream>

unsigned int Tensor::TensorFormat::totalLength(){
    if(this->strides.size()>0){
        return this->strides[this->strides.size()-2];
    }
    return 0;
    // Throw error
}

template<class T>
Tensor::TensorDataStructure<T>::TensorDataStructure(Tensor::TensorFormat& format){
    validateTensorFormat(format);
    this->format = format;
}

template<class T>
void Tensor::TensorDataStructure<T>::setData(T* d){
    std::copy(d, d + this->format.totalLength(), std::back_inserter(this->data));
}

template<class T>
std::vector<unsigned int> Tensor::TensorDataStructure<T>::getStrides(){
    return this->format.strides;
}

template<class T>
unsigned int Tensor::TensorDataStructure<T>::getRank(){
    return this->format.rank;
}

template<class T>
std::vector<unsigned int> Tensor::TensorDataStructure<T>::getLayout(){
    return this->format.layout;
}

template<class T>
T* Tensor::TensorDataStructure<T>::getRawData(){
    return this->data.data();
}


template<class T>
void Tensor::TensorDataStructure<T>::print(){
    for(int i=0;i<this->data.size();i++){
        std::cout<<data[i]<<std::endl;
    }
}

template<class T>
T Tensor::TensorDataStructure<T>::getValue(std::vector<T> index){
    if(index.size()+1!=format.layout.size()){
        // do better checks here
        //throw error
    }
    int finalIndex = 0;
    for(int i=0;i<index.size()-1;i++){
        finalIndex += index[i] * format.layout[i+1];
    }
    finalIndex += index[index.size()-1];
    return this->data[finalIndex];
}