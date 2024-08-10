#pragma once
#include "DLMat.h"
#include <unordered_map>
#include <functional>
using std::unordered_map;
using std::string;
using std::function;

class TwoLayerNet
{
public:
	TwoLayerNet(int input_size, int hidden_size, int output_size, double weight_init_std = 0.01);

	DLMat Predict(const DLMat& x);//使用神经网络
	double Loss(const DLMat& x, const DLMat& t);//计算误差
	unordered_map<string, DLMat> NumericalGradient(const DLMat& x, const DLMat& t);//数值梯度

	bool LoadNet(string filename);//从文件中加载参数
	bool StoreNet(string filename);//保存参数

	unordered_map<string, DLMat> params;

};

