#include "Matrix.h"

static void Delete_P_to_P(double** p,int r);

Matrix::Matrix(int r, int c)
{
	if (r == 0 || c == 0)
	{
		col = row = 0;
		data = nullptr;
		return;
	}
	col = c;
	row = r;
	data = new double* [row];
	for (int i = 0; i < row; i++)
		data[i] = new double[col]();
}

Matrix::Matrix(const Matrix& m)
{
	col = m.col;
	row = m.row;
	data = new double* [row];
	for (int i = 0; i < row; i++)
	{
		data[i] = new double[col];
		for (int j = 0; j < col; j++)
			data[i][j] = m.data[i][j];
	}
}

Matrix::Matrix(Matrix&& m) noexcept
{
	col = m.col;
	row = m.row;
	data = m.data;
	m.data = nullptr;
}

Matrix& Matrix::operator=(const Matrix& m)
{
	if (this == &m)
		return *this;

	Delete_P_to_P(data, row);//删除原有的资源
	col = m.col;
	row = m.row;

	data = new double* [row];
	
	for (int i = 0; i < row; i++)
	{
		data[i] = new double[col];
		for (int j = 0; j < col; j++)
			data[i][j] = m.data[i][j];
	}
	return *this;
}

Matrix& Matrix::operator=(Matrix&& m) noexcept
{
	if (this == &m)
		return *this;
	Delete_P_to_P(data, row);//删除原有的资源
	col = m.col;
	row = m.row;
	data = m.data;
	m.data = nullptr;
	return *this;
}

Matrix::~Matrix()
{
	Delete_P_to_P(data, row);
}

bool Matrix::SetValue(int numr, int numc, double value)
{
	if (numr<0 || numr>=row || numc<0 || numc>=col)
		return false;
	data[numr][numc] = value;
	return true;
}

double Matrix::GetValue(int numr, int numc) const
{
	if (numr<0 || numr>=row || numc<0 || numc>=col)
	{
		return 0.0;
	}
	return data[numr][numc];
}

double Matrix::SumOfElem() const
{
	double ret = 0.0;
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			ret += data[i][j];
	return ret;
}

double Matrix::MaxElem() const
{
	double ret = 0.0;
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			ret = (data[i][j] > ret) ? data[i][j] : ret;
	return ret;
}


void Matrix::ChangeElem(double(*f)(double))
{
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			data[i][j] = f(data[i][j]);
}

void Matrix::Print()
{
	if (data == nullptr)
	{
		std::puts("This is a empty Matrix.");
		return;
	}
	std::putchar('\n');
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			std::printf("%12.8f ", data[i][j]);
		}
		std::putchar('\n');
	}
}

Matrix Matrix::operator*(const Matrix& m) const
{
	if (this->data == nullptr || m.data == nullptr)
		return Matrix();
	if (this->col != m.row)
		return Matrix();
	Matrix retm(row, m.col);
	for (int i = 0; i < retm.row; i++)
	{
		for (int j = 0; j < retm.col; j++)
		{
			retm.data[i][j] = 0.0;
			for (int k = 0; k < col; k++)
				retm.data[i][j] += data[i][k] * m.data[k][j];
		}
	}
	return retm;
}

Matrix Matrix::InverseMatrix(bool& state) const
{
	if ((row != col) || (!data))
		return Matrix();
	int n = row;
	Matrix retm(n, n);
	Matrix tempm(*this);

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			if (i == j)
				retm.data[i][j] = 1;//将retm设置为单位阵

	for (int i = 0; i < n-1; i++)
	{
		int p = i;
		while ((p < n) && (tempm.data[i][p] == 0)) p++;
		if (p == n)
		{
			state = false;
			return Matrix();
		}
		if (p != i)
		{
			double* temp = tempm.data[p];
			tempm.data[p] = tempm.data[i];
			tempm.data[i] = temp;

			temp = retm.data[p];
			retm.data[p] = retm.data[i];
			retm.data[i] = temp;
		}
		for (int j = i + 1; j < n; ++j)
		{
			double m = tempm.data[j][i] / tempm.data[i][i];
			for (int k = 0; k < n; ++k)
			{
				tempm.data[j][k] -= m * tempm.data[i][k];
				retm.data[j][k] -= m * retm.data[i][k];
			}
		}
	}//化为上三角阵

	for (int i = n - 1; i > 0; i--)
	{
		if(tempm.data[i][i]==0)
		{
			state = false;
			return Matrix();
		}
		for (int j = i - 1; j >= 0; j--)
		{
			double m = tempm.data[j][i] / tempm.data[i][i];
			for (int k = n - 1; k >= 0; --k)
			{
				tempm.data[j][k] -= m * tempm.data[i][k];
				retm.data[j][k] -= m * retm.data[i][k];
			}
		}
	}//化为对角阵
	
	for (int i = 0; i < n; i++)
	{
		double m = 1 / tempm.data[i][i];
		for (int j = 0; j < n; j++)
			retm.data[i][j] *= m;
	}//将retm化为单位阵

	state = true;
	return retm;
}

Matrix Matrix::TransposeMatrix() const
{
	if (!data)
		return Matrix();
	Matrix retm(col, row);
	for (int i = 0; i < retm.row; i++)
		for (int j = 0; j < retm.col; j++)
			retm.data[i][j] = data[j][i];
	return retm;
}

double Matrix::Determinant(bool& b) const
{
	b = true;
	if ((row != col) || (!data))
	{
		b = false;
		return 0.0;
	}
	int n = row;
	Matrix tempm(*this);
	double change = 1.0;
	double ret = 1.0;

	for (int i = 0; i < n - 1; i++)
	{
		int p = i;
		while ((p < n) && (tempm.data[i][p] == 0)) p++;
		if (p == n)
			return 0.0;
		if (p != i)
		{
			double* temp = tempm.data[p];
			tempm.data[p] = tempm.data[i];
			tempm.data[i] = temp;
			change *= -1;
		}
		for (int j = i + 1; j < n; ++j)
		{
			double m = tempm.data[j][i] / tempm.data[i][i];
			for (int k = 0; k < n; ++k)
			{
				tempm.data[j][k] -= m * tempm.data[i][k];
			}
		}
	}//化为上三角阵
	for (int i = 0; i < n; i++)
		ret *= tempm.data[i][i];
	ret *= change;
	return ret;
}


void Delete_P_to_P(double** p,int r)
{
	if (p != NULL)
	{
		for (int i = 0; i < r; i++)
			if (p[i] != NULL)
				delete[] p[i];
	}
	delete[] p;
}

Matrix operator+(const Matrix& m1, const Matrix& m2)
{
	if ((m1.col != m2.col) || (m1.row != m2.row))
		return Matrix();
	else if ((m1.data == NULL) || (m2.data == NULL))
		return Matrix();
	Matrix retm(m1.row, m1.col);
	for (int i = 0; i < m1.row; ++i)
	{
		for (int j = 0; j < m1.col; ++j)
			retm.data[i][j] = m1.data[i][j] + m2.data[i][j];
	}
	return retm;
}

Matrix operator-(const Matrix& m1, const Matrix& m2)
{
	if ((m1.col != m2.col) || (m1.row != m2.row))
		return Matrix();
	else if ((m1.data == NULL) || (m2.data == NULL))
		return Matrix();
	Matrix retm(m1.row, m1.col);
	for (int i = 0; i < m1.row; ++i)
	{
		for (int j = 0; j < m1.col; ++j)
			retm.data[i][j] = m1.data[i][j] - m2.data[i][j];
	}
	return retm;
}

Matrix operator+(const Matrix& m, double c)
{
	Matrix ret = m;
	for (int i = 0; i < m.row; i++)
		for (int j = 0; j < m.col; j++)
			ret.data[i][j] -= c;
	return ret;
}

Matrix operator-(const Matrix& m, double c)
{
	Matrix ret = m;
	for (int i = 0; i < m.row; i++)
		for (int j = 0; j < m.col; j++)
			ret.data[i][j] += c;
	return ret;
}

Matrix operator*(double c,const Matrix& m)
{
	if (m.data == NULL)
		return Matrix();
	Matrix retm(m.row, m.col);
	for (int i = 0; i < m.row; ++i)
		for (int j = 0; j < m.col; ++j)
			retm.data[i][j] = c * m.data[i][j];
	return retm;
}

