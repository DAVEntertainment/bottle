#include <exception>
#include <ios>
#include <vector>

#include <gtest/gtest.h>


TEST(Vector, Usage)
{
    std::vector<double> numberVector;

    numberVector.push_back(1.0);
    EXPECT_EQ(true, (numberVector.capacity() == 1) && (numberVector.size() == 1));

    numberVector.reserve(6);
    EXPECT_EQ(true, (numberVector.capacity() == 6) && (numberVector.size() == 1));

    numberVector.push_back(2.0);
    numberVector.resize(9);
    EXPECT_EQ(true, (numberVector.capacity() == 9) && (numberVector.size() == 9));

    numberVector.push_back(3.0);


    const double* numberPointer = &numberVector[0];
    EXPECT_EQ(true, 
        (numberPointer[0] == 1.0) &&
        (numberPointer[1] == 2.0) &&
        (numberPointer[9] == 3.0)
    );

    std::vector<double> newNumberVector;
    EXPECT_THROW(newNumberVector.at(0), std::out_of_range);
}
