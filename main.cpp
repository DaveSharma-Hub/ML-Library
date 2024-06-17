#include "./src/operations/matrixMultiplication/matrixMultiplication.cpp"
#include "./src/tensor/Tensor.cpp"
#include <iostream>
#include <chrono>
#include <time.h> 
#include <assert.h>
#include <vector>
#include <math.h>

using namespace operations;
using namespace std;

void correctness(){
    vector<vector<double>> a = createMatrix(30,15000);
    vector<vector<double>> b = createMatrix(15000,20);
    vector<vector<double>> transposedB = transpose(b);
    vector<vector<double>> output = createOutput(a,b);
    vector<vector<double>> output3 = createOutput(a,b);
    
    auto t_start = std::chrono::high_resolution_clock::now();
    matrixMult(a,b,output);
    auto t_end = std::chrono::high_resolution_clock::now();
    
    auto t_start3 = std::chrono::high_resolution_clock::now();
    wrongMatrixMult(a, transposedB, output3);
    auto t_end3 = std::chrono::high_resolution_clock::now();

    int diff = 0;
    for(int i=0;i<output.size();i++){
        for(int j=0;j<output[i].size();j++){
            diff += abs(output[i][j] - output3[i][j]);
        }
    }
    cout<<"diff:"<<diff<<endl;
}

void test(double* sum1, double* sum2, double* sum3){
    vector<vector<double>> a = createMatrix(30,1500000);
    vector<vector<double>> b = createMatrix(1500000,20);
    vector<vector<double>> transposedB = transpose(b);
    vector<vector<double>> output = createOutput(a,b);
    vector<vector<double>> output2 = createOutput(a,b);
    vector<vector<double>> output3 = createOutput(a,b);
    
    auto t_start = std::chrono::high_resolution_clock::now();
    matrixMult(a,b,output);
    auto t_end = std::chrono::high_resolution_clock::now();
    auto t_start2 = std::chrono::high_resolution_clock::now();
    transposeMatrixMult(a,transposedB, output2);
    auto t_end2 = std::chrono::high_resolution_clock::now();
    
    auto t_start3 = std::chrono::high_resolution_clock::now();
    wrongMatrixMult(a, transposedB, output3);
    auto t_end3 = std::chrono::high_resolution_clock::now();
    for(int i=0;i<output.size();i++){
        for(int j=0;j<output[i].size();j++){
            assert(output[i][j] == output2[i][j]);
        }
    }
    
    double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end-t_start).count();
    double elapsed_time2_ms = std::chrono::duration<double, std::milli>(t_end2-t_start2).count();
    double elapsed_time3_ms = std::chrono::duration<double, std::milli>(t_end3-t_start3).count();
    // cout<<"Naive:"<<elapsed_time_ms<<endl;
    // cout<<"Transposed Naive:"<<elapsed_time2_ms<<endl;
    // cout<<"Wrong Mult:"<<elapsed_time3_ms<<endl;
    // cout<<"COMPLETED"<<endl;
    *sum1 +=  elapsed_time_ms;
    *sum2 +=  elapsed_time2_ms;
    *sum3 +=  elapsed_time3_ms;
}

Tensor::TensorDataStructure<double> createTensorMatrix(int height, int width, bool insertRandomNumbers = false){
    std::vector<unsigned int> layout = {1, (unsigned int)height, (unsigned int)width, 8};
    std::vector<unsigned int> strides;
    unsigned int tmp = layout[0];
    for(int i=0;i<layout.size()-1;i++){
        strides.push_back(tmp);
        tmp *= layout[i+1];
    }
    strides.push_back(tmp);

    Tensor::TensorFormat tensorFormat = Tensor::TensorFormat{strides:strides, rank:4, layout:layout};
    double* data = (double*)malloc(sizeof(double) * height * width);
    for(int i=0;i<height * width;i++){
        if(insertRandomNumbers){
            data[i] = (double)i;
        }else{
            data[i] = 0;
        }
    }
    Tensor::TensorDataStructure<double> tensor(tensorFormat);
    tensor.setData(data);
    return tensor;
}


int main() {
    // srand(time(0)); 
    // double* first = new double(0);
    // double* second = new double(0);
    // double* third = new double(0);
    // int count = 50;
    // for(int i=0;i<count;i++){
    //     test(first, second, third);
    // }
    // cout<<"Naive:"<<*first/count<<endl;
    // cout<<"Transposed:"<<*second/count<<endl;
    // cout<<"Wrong:"<<*third/count<<endl;

    // int count = 20;
    // int* data = (int*)malloc(sizeof(int) * count);
    // for(int i=0;i<count;i++){
    //     data[i] = i;
    // }
    // std::vector<unsigned int> layout{2,5,2,8};
    // std::vector<unsigned int> strides{2,10,20,160};
    // unsigned int rank = 4;
    // Tensor::TensorFormat tensorFormat = Tensor::TensorFormat{strides:strides, rank:rank, layout:layout};
    // Tensor::TensorDataStructure<int> tensor(tensorFormat);
    // tensor.setData(data);

    // tensor.print();
    // std::cout<<std::endl;
    // std::cout<<tensor.getValue({0,3,1})<<endl;

    // correctness();
    std::vector<std::vector<double>> a2;
    std::vector<std::vector<double>> b2;
    std::vector<std::vector<double>> output2;
    int count = 0;
    for(int i=0;i<3;i++){
        std::vector<double> tmp;
        for(int j=0;j<3;j++){
            tmp.push_back(count++);
        }
        a2.push_back(tmp);
    }
    count = 0;

    for(int i=0;i<3;i++){
        std::vector<double> tmp;
        for(int j=0;j<2;j++){
            tmp.push_back(count++);
        }
        b2.push_back(tmp);
    }
    for(int i=0;i<3;i++){
        std::vector<double> tmp;
        for(int j=0;j<2;j++){
            tmp.push_back(0);
        }
        output2.push_back(tmp);
    }
    

    Tensor::TensorDataStructure<double> a = createTensorMatrix(3,3,true);
    Tensor::TensorDataStructure<double> b = createTensorMatrix(3,2,true);
    Tensor::TensorDataStructure<double> output = createTensorMatrix(3,2,false);

    matrixMult(a,b, output);
    matrixMult(a2, b2, output2);

    for(unsigned int i=0;i<3;i++){
        for(unsigned int j=0;j<2;j++){
            std::vector<unsigned int> index{0,i,j};
            if(output2[i][j] != output.getValue(index)){
                std::cout<<output2[i][j]<<" "<<output.getValue(index)<<std::endl;
            }
        }
    }

    return 0;
}