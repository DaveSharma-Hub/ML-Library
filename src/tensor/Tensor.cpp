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

template <class T>
Tensor::TensorDataStructure<T>::TensorDataStructure(){};

template <class T>
Tensor::TensorDataStructure<T>::TensorDataStructure(Tensor::TensorFormat &format)
{
    validateTensorFormat(format);
    this->format = format;
}

template <class T>
void Tensor::TensorDataStructure<T>::setTensorFormat(TensorFormat &format)
{
    validateTensorFormat(format);
    this->format = format;
}

template<class T>
void Tensor::TensorDataStructure<T>::setData(T* d){
    std::copy(d, d + this->format.totalLength(), std::back_inserter(this->data));
    this->isEmpty = false;
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
int Tensor::TensorDataStructure<T>::getFinalIndex(std::vector<unsigned int>& index){
    if(index.size()+1!=format.layout.size()){
        // do better checks here
        //throw error
    }
    int finalIndex = 0;
    for(int i=0;i<index.size()-1;i++){
        finalIndex += index[i] * format.layout[i+1];
    }
    finalIndex += index[index.size()-1];
    return finalIndex;
}

template<class T>
T Tensor::TensorDataStructure<T>::getValue(std::vector<unsigned int>& index){
    int finalIndex = this->getFinalIndex(index);
    return this->data[finalIndex];
}

template<class T>
void Tensor::TensorDataStructure<T>::setValue(std::vector<unsigned int>& index, T value){
    int finalIndex = this->getFinalIndex(index);
    this->data[finalIndex] = value;
}

template <class T>
void Tensor::TensorDataStructure<T>::allocateData(){
    // assert(this->format);
    
    unsigned int size = 0;
    for(int i=0;i<this->format.layout.size()-1;i++){
        size += this->format.layout[i];
    }
    this->data.reserve(size);
    this->isEmpty = false;
}

template <class T>
Tensor::TensorFormat &Tensor::TensorDataStructure<T>::getFormat()
{
    return this->format;
}
