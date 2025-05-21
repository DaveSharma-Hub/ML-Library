#include <cmath>

namespace Utils {
    template <class DataType>
    double sigmoid(DataType value){
        return 1 / ( 1 + exp(-1 * (double)value));
    }
    
    template <class DataType>
    double sigmoid_derivative(DataType value){
        double sig = sigmoid(value);
        return sig * (1 - sig);
    }
}
