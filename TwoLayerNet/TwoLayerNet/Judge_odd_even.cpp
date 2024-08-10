#include<iostream>
#include<random>
#include "TwoLayerNet.h"

void Learn(TwoLayerNet& network, double learning_rate = 0.01, int iter_num = 10000);
DLMat ToBin(int n);

int main()
{
	TwoLayerNet net(8, 10, 2);
	if (!net.LoadNet("Judge_odd_even.p"))
		Learn(net);
	net.StoreNet("Judge_odd_even.p");
	while (true)
	{
		int n;
		printf("请输入一个整数，我会告诉你它是奇还是偶:\n");
		std::cin >> n;
		DLMat x = ToBin(n);
		DLMat y = net.Predict(x);

		if (y.data[0][0] > y.data[0][1])
			printf("%f %的概率为奇\n", y.data[0][0] * 100);
		else
			printf("%f %的概率为偶\n", y.data[0][1] * 100);
	}
	return 0;
}

void Learn(TwoLayerNet& network, double learning_rate, int iter_num)
{
	for (int i = 0; i < iter_num; i++)
	{
		DLMat x(1, 8);
		for (int j = 0; j < 8; j++)
		{
			// 创建随机数引擎  
			std::random_device rd;
			std::mt19937 gen(rd());
			// 定义随机数分布  
			std::uniform_int_distribution<> d(0, 100);
			x.data[0][j] = d(gen)%2;
		}
		DLMat t(1, 2);
		if (x.data[0][7] == 1)
			t.data[0][0] = 1;
		else
			t.data[0][1] = 1;
		unordered_map<string, DLMat> grad = network.NumericalGradient(x, t);
		for (std::unordered_map<string, DLMat>::const_iterator it = grad.begin(); it != grad.end(); ++it)
		{
			network.params[it->first] = network.params[it->first] - learning_rate * (it->second);
		}

		double loss = network.Loss(x, t);
		printf("%f\n", loss);
	}
}

DLMat ToBin(int n)
{
	double temp[8]{};
	int i = 0;
	while (i < 8)
	{
		if (n >= 1)
		{
			temp[i] = n % 2;
			n /= 2;
			i++;
		}
		else
		{
			temp[i] = 0;
			i++;
		}
	}

	DLMat ret(1, 8);
	for (int j = 0; j < 8; j++)
		ret.data[0][j] = temp[7 - j];
	return ret;
}
