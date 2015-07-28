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

	float determinant()
	{
		float ret = 0;

		Element **matrix = toArray();

		ret = determinant(matrix, rangeX);

		for (int i = 0; i < rangeX; i++)
			free(matrix[i]);
		free(matrix);

		return ret;
	}

	Matrix inverse()
	{
		Matrix<rangeX, rangeY, Element>  ret;
		float det = determinant();
		if (det == 0)
		{
			ret.initNull();
		}
		else
		{
			Element **matrix = toArray();
			unsigned int n = _rangeX;

			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					Element **minor = preMinor(matrix, n, i, j);

					ret._matrix[i][j] = determinant(minor, n-1) * ((i + j) % 2 ? -1 : 1);

					for (int i = 0; i < n - 1; i++)
						free(minor[i]);
					free(minor);
				}
			}

			for (int i = 0; i < n; i++)
				free(matrix[i]);
			free(matrix);

			ret = ret.transpose() * (1/det);
		}
		
		return ret;
	}

	Element** toArray()
	{
		Element **ret = (Element **)malloc(rangeX*sizeof(Element *));
		for (unsigned int i = 0; i < rangeX; i++)
		{
			ret[i] = (Element *)malloc(rangeY*sizeof(Element));
			for (unsigned int j = 0; j < rangeY; j++)
				ret[i][j] = _matrix[i][j];
		}

		return ret;
	}

private:

	Element **preMinor(Element **matrix, unsigned int n, unsigned int x, unsigned int y)
	{
		Element **ret = (Element **)malloc((n - 1)*sizeof(Element *));
		for (int i = 0; i < n - 1; i++)
			ret[i] = (Element *)malloc((n - 1)*sizeof(Element));

		for (int i = 0, in = 0; i < n; i++) {
			if (i != x){
				for (int j = 0, jn = 0; j < n; j++) {
					if (j != y) {
						ret[in][jn++] = matrix[i][j];
					}
				}
				in++;
			}
		}

		return ret;
	}

	float determinant(Element **matrix, int n)
	{
		float ret = 0;

		if (n == 1) {
			ret = matrix[0][0];
		}
		else if (n == 2) {
			ret = matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
		}
		else
		{
			for (int y = 0; y < n; y++)
			{
				Element **minor = preMinor(matrix, n, 0, y);
				ret += (y % 2 ? -1 : 1) * matrix[0][y] * determinant(minor, n - 1);

				for (int i = 0; i < n - 1; i++)
					free(minor[i]);
				free(minor);
			}
		}
		return(ret);
	}
};

NS_SIT_END

#endif // MATRIX_H_

