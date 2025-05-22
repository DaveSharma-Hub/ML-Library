#include <iostream>
#include "../src/NeuralNet/NeuralNet.cpp"
using namespace std;

int main(){
    std::vector<int> layerCount = {2,1};
    NeuralNet<int>* n1 = new NeuralNet<int>(layerCount, (uint)10, 0.1, (uint32_t)100);
    // n1->setInputOutput(nullptr, nullptr)->start();

    cout<<"Testing"<<endl;
    return 0;
}