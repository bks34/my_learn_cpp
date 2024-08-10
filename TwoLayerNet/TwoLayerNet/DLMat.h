#pragma once
#include "Matrix.h"

/*
* 用于构造神经网络的矩阵类
* 添加了一些神经网络中经常用到的功能
*/
class DLMat :
    public Matrix
{
public:
    using Matrix::Matrix;

    void RandomValue();

    friend DLMat SoftMax(const DLMat& m);

    friend double CrossEntropyError(const DLMat& y, const DLMat& t); //交叉熵误差
    friend double MeanSquaredError(const DLMat& y, const DLMat& t);  //求均方误差

    //常用激活函数
    friend DLMat Sigmoid(const DLMat& m);
    friend DLMat StepFunction(const DLMat& m);

    friend DLMat operator+(const DLMat& m, double c);
    friend DLMat operator-(const DLMat& m, double c);
    friend DLMat operator+(const DLMat& m1, const DLMat& m2);
    friend DLMat operator-(const DLMat& m1, const DLMat& m2);
    friend DLMat operator*(double c, const DLMat& m);//数乘
    DLMat operator*(const DLMat& m) const;
};

