#include <iostream>
#include "math.h"


int add(int a, int b) {
    return a+b;
}

SceneOperator::SceneOperator() {
    std::cout << "@@@ Create SceneOperator " << this << std::endl;
}

SceneOperator::~SceneOperator() {
    std::cout << "@@@ Desctroy SceneOperator " << this << std::endl;
}

void SceneOperator::Start() {
    std::cout << "@@@ SceneOperator::Start " << this << std::endl;
}

void SceneOperator::Stop() {
    std::cout << "@@@ SceneOperator::Stop " << this << std::endl;
}
