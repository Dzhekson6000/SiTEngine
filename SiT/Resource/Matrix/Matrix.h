#ifndef MATRIX_H_
#define MATRIX_H_

#include "Macros.h"
#include "Geometry/Geometry.h"

NS_SIT_BEGIN

template<const size_t rangeX, const size_t rangeY, class Element>
class SIT_DLL Matrix
{
public:
	Element _matrix[rangeX][rangeY];
	const size_t _rangeX = rangeX;
	const size_t _rangeY = rangeY;

	Matrix()
	{

	}

	~Matrix()
	{

	}

	void initNull()
	{
		for (unsigned int i = 0; i < _rangeX; i++)
		{
			for (unsigned int j = 0; j < _rangeY; j++)
			{
				_matrix[i][j] = 0.0f;
			}
		}
	}

	void initIdentity()
	{
		for (unsigned int i = 0; i < _rangeX; i++)
		{
			for (unsigned int j = 0; j < _rangeY; j++)
			{
				if (i == j)
				{
					_matrix[i][j] = 1.0f;
				}
				else
				{
					_matrix[i][j] = 0.0f;
				}
			}
		}
	}

	template<const size_t TrangeX, const size_t TrangeY, class TElement>
	Matrix operator*(const Matrix<TrangeX, TrangeY, TElement>& other) const
	{
		if (_rangeX != other._rangeY)
		{
			Matrix<rangeY, rangeY, Element>  ret;
			ret.initNull();
			return ret;
		}

		Matrix<TrangeY, rangeY, Element>  ret;

		for (unsigned int i = 0; i < ret._rangeX; i++) {
			for (unsigned int j = 0; j < ret._rangeY; j++)
			{
				ret._matrix[i][j] = 0;
				for (unsigned int k = 0; k < _rangeX; k++)
				{
					ret._matrix[i][j] += _matrix[k][j] * other._matrix[i][k];
				}
			}
		}

		return ret;
	}

	Matrix operator*(const int other) const
	{
		return operator*((float)other);
	}

	Matrix operator*(const float other) const
	{
		Matrix<rangeX, rangeY, Element> ret;

		for (unsigned int i = 0; i < ret._rangeX; i++) {
			for (unsigned int j = 0; j < ret._rangeY; j++) {
				ret._matrix[i][j] = _matrix[i][j] * other;
			}
		}

		return ret;
	}
	
	Matrix operator+(const Matrix& other) const
	{
		if (_rangeX != other._rangeX || _rangeY != other._rangeY)
		{
			Matrix<rangeY, rangeY, Element>  ret;
			ret.initNull();
			return ret;
		}

		Matrix<rangeX, rangeY, Element> ret;

		for (unsigned int i = 0; i < ret._rangeX; i++) {
			for (unsigned int j = 0; j < ret._rangeY; j++) {
				ret._matrix[i][j] = _matrix[i][j] + other._matrix[i][j];
			}
		}

		return ret;
	}

	Matrix operator-(const Matrix& other) const
	{
		if (_rangeX != other._rangeX || _rangeY != other._rangeY)
		{
			Matrix<rangeY, rangeY, Element>  ret;
			ret.initNull();
			return ret;
		}

		Matrix<rangeX, rangeY, Element> ret;

		for (unsigned int i = 0; i < ret._rangeX; i++) {
			for (unsigned int j = 0; j < ret._rangeY; j++) {
				ret._matrix[i][j] = _matrix[i][j] - other._matrix[i][j];
			}
		}

		return ret;
	}

	Matrix transpose()
	{
		Matrix<rangeX, rangeY, Element> ret;;

		for (unsigned int i = 0; i < ret._rangeX; i++) {
			for (unsigned int j = 0; j < ret._rangeY; j++) {
				ret._matrix[i][j] = _matrix[j][i];
			}
		}

		return ret;
	}

	Matrix& operator= (const Matrix& other)
	{
		Matrix < rangeY, rangeY, Element > ret;
		memcpy(&_matrix, &other._matrix, sizeof(other._matrix));
		return  ret;
	}
};

NS_SIT_END

#endif // MATRIX_H_

