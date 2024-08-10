#include "DLMat.h"
#include <random>

static double d_sigmoid(double x)
{
    return 1 / (1 + exp(-x));
}
static double d_step_function(double x)
{
    if (x > 0)
        return 1.0;
    else
        return 0.0;
}

DLMat SoftMax(const DLMat& m)
{
    double c = m.MaxElem();
    DLMat exp_m = m - c;
    exp_m.ChangeElem(exp);
    double exp_m_sum = exp_m.SumOfElem();

    exp_m = 1 / exp_m_sum * exp_m;
    
    return exp_m;
}

double CrossEntropyError(const DLMat& y, const DLMat& t)
{
    if ((y.GetNumOfCol() != t.GetNumOfCol()) || (y.GetNumOfRow() != t.GetNumOfRow()))
    {
        fputs("CrossEntropyError 维数不匹配!", stderr);
        return 0.0;
    }
    double delta = 1e-7;
    double sum = 0.0;
    for (int j = 0; j < y.GetNumOfCol(); j++)
        sum += t.GetValue(0, j) * log(y.GetValue(0, j) + delta);
    return -sum;
}

double MeanSquaredError(const DLMat& y, const DLMat& t)
{
    if ((y.GetNumOfCol() != t.GetNumOfCol()) || (y.GetNumOfRow() != t.GetNumOfRow()))
    {
        fputs("MeanSquaredError 维数不匹配!", stderr);
        return 0.0;
    }

    double sum = 0.0;
    for (int j = 0; j < y.GetNumOfCol(); j++)
        sum += pow(y.GetValue(0, j) - t.GetValue(0, j), 2);
    return 0.5*sum;
}

DLMat Sigmoid(const DLMat& m)
{
    DLMat z = m;
    z.ChangeElem(d_sigmoid);
    return z;
}

DLMat StepFunction(const DLMat& m)
{
    DLMat z = m;
    z.ChangeElem(d_step_function);
    return z;
}

DLMat operator+(const DLMat& m, double c)
{
    DLMat ret = m;
    for (int i = 0; i < m.GetNumOfRow(); i++)
        for (int j = 0; j < m.GetNumOfCol(); j++)
            ret.SetValue(i, j, ret.GetValue(i, j) + c);
    return ret;
}

DLMat operator-(const DLMat& m, double c)
{
    DLMat ret = m;
    for (int i = 0; i < m.GetNumOfRow(); i++)
        for (int j = 0; j < m.GetNumOfCol(); j++)
            ret.SetValue(i, j, ret.GetValue(i, j) - c);
    return ret;
}

DLMat operator+(const DLMat& m1, const DLMat& m2)
{
    if ((m1.col != m2.col) || (m1.row != m2.row))
        return DLMat();
    else if ((m1.data == NULL) || (m2.data == NULL))
        return DLMat();
    DLMat retm(m1.row, m1.col);
    for (int i = 0; i < m1.row; ++i)
    {
        for (int j = 0; j < m1.col; ++j)
            retm.data[i][j] = m1.data[i][j] + m2.data[i][j];
    }
    return retm;
}

DLMat operator-(const DLMat& m1, const DLMat& m2)
{
    if ((m1.col != m2.col) || (m1.row != m2.row))
        return DLMat();
    else if ((m1.data == NULL) || (m2.data == NULL))
        return DLMat();
    DLMat retm(m1.row, m1.col);
    for (int i = 0; i < m1.row; ++i)
    {
        for (int j = 0; j < m1.col; ++j)
            retm.data[i][j] = m1.data[i][j] - m2.data[i][j];
    }
    return retm;
}

DLMat operator*(double c, const DLMat& m)
{
    DLMat ret = m;
    for (int i = 0; i < m.GetNumOfRow(); i++)
        for (int j = 0; j < m.GetNumOfCol(); j++)
            ret.SetValue(i, j, ret.GetValue(i, j) * c);
    return ret;
}

void DLMat::RandomValue()
{
    // 创建随机数引擎  
    std::random_device rd;
    std::mt19937 gen(rd());
    // 定义随机数分布  
    std::normal_distribution<> d(0.0, 1.0);

    for (int i = 0; i < GetNumOfRow(); i++)
        for (int j = 0; j < GetNumOfCol(); j++)
            SetValue(i, j, d(gen));
}

DLMat DLMat::operator*(const DLMat& m) const
{
    if (this->data == nullptr || m.data == nullptr)
        return DLMat();
    if (this->col != m.row)
        return DLMat();
    DLMat retm(row, m.col);
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
