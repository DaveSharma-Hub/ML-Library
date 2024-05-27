#include "./src/operations/matrixMultiplication/matrixMultiplication.cpp"
#include <iostream>
#include <chrono>
#include <time.h> 
#include <assert.h>

using namespace operations;
using namespace std;

void test(){
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
    cout<<"Naive:"<<elapsed_time_ms<<endl;
    cout<<"Transposed Naive:"<<elapsed_time2_ms<<endl;
    cout<<"Wrong Mult:"<<elapsed_time3_ms<<endl;
    cout<<"COMPLETED"<<endl;
}


int main() {
    srand(time(0)); 
    test();
    return 0;
}