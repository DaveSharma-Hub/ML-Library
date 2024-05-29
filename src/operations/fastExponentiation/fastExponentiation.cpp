#pragma unroll
#include "fastExponentiation.hpp"
#include <iostream>

std::vector<int> toBinary(int exponent){
    std::vector<int> bin;
    while(exponent != 0){
        bin.push_back(exponent%2);
        exponent /= 2;
    }
    return bin;
}

long fastExponentiation(int num, int exponent){
    std::vector<int> binary = toBinary(exponent);
    long finalExp = 1;
    long prev = num;
    for(int i=0;i<binary.size();i++){
        if(binary[i] == 1){
            finalExp *= (prev);
        }
        prev = prev*prev;
    }
    return finalExp;
}

double power(int num, int exponent){
    if(num>=2 && exponent > 62){
        int size = 62;
        int times = exponent / size;
        int count = times * size == exponent ? times : times +1;
        double final = 1;
        for(int i=0;i<count;i++){
            if((i+1)*size < exponent){
                final *= (double)fastExponentiation(num, size);
            }else{
                final *= (double)fastExponentiation(num, exponent-i*size);
            }
        }
        return final;
    }else{
        return fastExponentiation(num, exponent);
    }
}

// int main() {
//     int n =6>>1;
//     cout<<n<<endl;
//     int num = 2;
//     int ex = 62;
//     auto t_start = std::chrono::high_resolution_clock::now();
//     cout<<power(num,ex)<<endl;
//     auto t_end = std::chrono::high_resolution_clock::now();

//     double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end-t_start).count();
    
//     auto t_start2 = std::chrono::high_resolution_clock::now();
//     cout<<pow(num, ex)<<endl;
//     auto t_end2 = std::chrono::high_resolution_clock::now();
//     double elapsed_time_ms2 = std::chrono::duration<double, std::milli>(t_end2-t_start2).count();
    
//     cout<<"Fast:"<<elapsed_time_ms<<endl;
//     cout<<"Pow:"<<elapsed_time_ms2<<endl;
//     return 0;
// }