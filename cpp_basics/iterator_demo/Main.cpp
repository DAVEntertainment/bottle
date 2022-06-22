#include <iostream>
#include <vector>

#include "Demo.h"


class DataSet
{
public:
    std::vector<int> myData;

    void Add(int v) { myData.push_back(v); }
    std::vector<int>::iterator begin() {
        return myData.begin();
    }
    std::vector<int>::iterator end() {
        return myData.end();
    }
};

int main()
{
    DataSet data;
    for (int i = 0; i < 10; ++i) {
        data.Add(i);
    }
    int counter = 0;
    for (auto& i : data) {
        std::cout << i << std::endl;
    }

    return 0;
}
