
#include <vector>

template <class DataType>
class TensorMetaData{
    public:
        TensorMetaData(){

        }
    private:
        std::vector<DataType> strides;
};