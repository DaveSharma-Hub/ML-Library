#include "./src/operations/matrixMultiplication/matrixMultiplication.cpp"
#include "./src/tensor/Tensor.cpp"
#include <iostream>
#include <chrono>
#include <time.h> 
#include <assert.h>
#include <vector>

using namespace operations;
using namespace std;

void test(double* sum1, double* sum2, double* sum3){
    vector<vector<int>> a = createMatrix(30,1500000);
    vector<vector<int>> b = createMatrix(1500000,20);
    vector<vector<int>> transposedB = transpose(b);
    vector<vector<int>> output = createOutput(a,b);
    vector<vector<int>> output2 = createOutput(a,b);
    vector<vector<int>> output3 = createOutput(a,b);
    
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

    int count = 20;
    int* data = (int*)malloc(sizeof(int) * count);
    for(int i=0;i<count;i++){
        data[i] = i;
    }
    std::vector<unsigned int> layout{2,5,2,8};
    std::vector<unsigned int> strides{2,10,20,160};
    unsigned int rank = 4;
    Tensor::TensorFormat tensorFormat = Tensor::TensorFormat{strides:strides, rank:rank, layout:layout};
    Tensor::TensorDataStructure<int> tensor(tensorFormat);
    tensor.setData(data);

    tensor.print();
    std::cout<<std::endl;
    std::cout<<tensor.getValue({0,3,1})<<endl;
    return 0;
}