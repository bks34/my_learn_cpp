#include "TwoLayerNet.h"
#include <fstream>

using std::fstream;

static DLMat numerical_gradient(function<double(const DLMat&)>, const DLMat& x);

TwoLayerNet::TwoLayerNet(int input_size, int hidden_size, int output_size, double weight_init_std)
{
	DLMat W1(input_size, hidden_size);
	W1.RandomValue();
	DLMat b1(1, hidden_size);
	DLMat W2(hidden_size, output_size);
	W2.RandomValue();
	DLMat b2(1, output_size);

	params["W1"] = weight_init_std * W1;
	params["b1"] = b1;
	params["W2"] = weight_init_std * W2;
	params["b2"] = b2;
}

DLMat TwoLayerNet::Predict(const DLMat& x)
{
	DLMat W1 = params["W1"];
	DLMat b1 = params["b1"];
	DLMat W2 = params["W2"];
	DLMat b2 = params["b2"];

	DLMat a1 = x * W1 + b1;
	DLMat z1 = Sigmoid(a1);
	DLMat a2 = z1 * W2 + b2;
	DLMat y = SoftMax(a2);

	return y;
}

double TwoLayerNet::Loss(const DLMat& x, const DLMat& t)
{
	DLMat y = Predict(x);
	return CrossEntropyError(y, t);
}

unordered_map<string, DLMat> TwoLayerNet::NumericalGradient(const DLMat& x, const DLMat& t)
{
	auto  loss_W = [this, x, t](const DLMat&) ->double {return Loss(x, t); };
	unordered_map<string, DLMat> grads;
	grads["W1"] = numerical_gradient(loss_W, params["W1"]);
	grads["b1"] = numerical_gradient(loss_W, params["b1"]);
	grads["W2"] = numerical_gradient(loss_W, params["W2"]);
	grads["b2"] = numerical_gradient(loss_W, params["b2"]);

	return grads;
}

bool TwoLayerNet::LoadNet(string filename)
{
	fstream f;
	f.open(filename, std::ios::in);
	if (!f.is_open())
		return false;
	for (int i = 0; i < params.size(); i++)
	{
		string key;
		f >> key;
		f.get();
		DLMat* m = &params[key];
		for (int i = 0; i < m->row; i++)
			for (int j = 0; j < m->col; j++)
				f >> m->data[i][j];
		f.get();
	}
	return true;
}

bool TwoLayerNet::StoreNet(string filename)
{
	fstream f;
	f.open(filename, std::ios::out);
	if (!f.is_open())
		return false;
	for (auto it = params.begin(); it != params.end(); ++it)
	{
		DLMat m = it->second;
		f << it->first << '\n';
		for (int i = 0; i < m.row; i++)
			for (int j = 0; j < m.col; j++)
				f << m.data[i][j];
		f << '\n';
	}
	f.close();
	return true;
}

DLMat numerical_gradient(function<double(const DLMat&)> f, const DLMat& x)
{
	double h = 1e-4;
	DLMat grad = DLMat(x.row, x.col);

	for(int i=0;i<x.row;i++)
		for (int j = 0; j < x.col; j++)
		{
			double tmp_val = x.data[i][j];
			x.data[i][j] = tmp_val + h;
			double fxh1 = f(x);
			x.data[i][j] = tmp_val - h;
			double fxh2 = f(x);

			grad.data[i][j] = (fxh1 - fxh2) / (2 * h);
			x.data[i][j] = tmp_val;
		}
	return grad;
}
