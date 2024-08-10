#pragma once
#include<math.h>
#include<iostream>
class Matrix
{
public:
	Matrix() = default;
	Matrix(int r, int c);
	Matrix(const Matrix& m);//拷贝构造函数
	Matrix(Matrix&& m) noexcept;//移动构造函数
	Matrix& operator=(const Matrix& m);
	Matrix& operator=(Matrix&& m) noexcept;
	~Matrix();

	int GetNumOfCol() const { return col; }
	int GetNumOfRow() const { return row; }
	double** GetData() { return data; }

	bool SetValue(int numr, int numc, double value);
	double GetValue(int numr, int numc) const;

	double SumOfElem() const;
	double MaxElem() const;

	void ChangeElem(double (*f)(double));

	void Print();

	Matrix operator*(const Matrix& m) const;
	Matrix InverseMatrix(bool&) const;//矩阵的逆
	Matrix TransposeMatrix() const;//转置
	double Determinant(bool &) const;
	friend Matrix operator+(const Matrix& m1, const Matrix& m2);
	friend Matrix operator-(const Matrix& m1, const Matrix& m2);
	friend Matrix operator+(const Matrix& m, double c);
	friend Matrix operator-(const Matrix& m, double c);
	friend Matrix operator*(double c, const Matrix& m);//数乘

	

	int col = 0;//列数
	int row = 0;//行数
	double** data = nullptr;//数据
};

