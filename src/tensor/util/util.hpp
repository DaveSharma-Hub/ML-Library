#pragma once
#include "../Tensor.hpp"
#include <vector>
#include <assert.h>

bool checkStridesFromLayout(std::vector<unsigned int>& strides, std::vector<unsigned int>& layout){
    if(layout.size()==0){
        return false;
    }
    if(layout[0] != strides[0]){
        return false;
    }
    int intermediary = layout[0];
    for(int i=1;i<layout.size();i++){
        intermediary *= layout[i];
        if(intermediary != strides[i]){
            return false;
        }
    }
    return true;
}

void validateTensorFormat(Tensor::TensorFormat& format){
    int valid = -1;
    if(!(format.strides.size()>0)){
        valid += 1;
    }
    if(format.rank <= 0 ){
        valid += 1;
    }
    if(!(format.layout.size()>0)){
        valid += 1;
    }

    if(!checkStridesFromLayout(format.strides, format.layout)){
        valid += 1;
    }
    assert(valid == -1);
}

