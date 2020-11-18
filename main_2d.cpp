#include <cstddef>
#include <stdio.h>
#include <math.h>

template<typename T>
struct matrix_traits;

template<typename T, std::size_t rows, std::size_t columns>
struct matrix_traits<T[columns][rows]>
{
	typedef std::size_t index_type;
	typedef typename T value_type;

	static const std::size_t j = columns;
	static const std::size_t k = rows;
};

template<typename MatrixType,
		 typename MatrixTraits = matrix_traits<MatrixType>,
		 typename Ret = MatrixTraits::value_type (&) [MatrixTraits::j] [MatrixTraits::j + 1]>
Ret toPoints(MatrixType& M)
{
	typedef MatrixTraits::index_type iType;

	MatrixTraits::value_type P[MatrixTraits::j][MatrixTraits::j + 1] = { 0 };

	for (iType j = 0; j < MatrixTraits::j; j++)
	{
		for (iType i = 0; i < MatrixTraits::j; i++)
			P[j][i] = pow(M[j][0], MatrixTraits::j - i - 1);
		P[j][MatrixTraits::j] = M[j][1];
	}

	return P;
}

template<typename MatrixType,
		 typename MatrixTraits = matrix_traits<MatrixType>>
void toReducedRowEchelonForm(MatrixType& M)
{
	typedef MatrixTraits::value_type vType;
	typedef MatrixTraits::index_type iType;

	for (iType j = 0; j < MatrixTraits::j; j++)
	{
		vType lead = M[j][j];

		for (iType k = 0; k < MatrixTraits::k; k++)
			M[j][k] /= lead;

		for (iType i = 0; i < MatrixTraits::j; i++)
		{
			if (i == j) continue;

			vType coefficient = M[i][j] / M[j][j];

			for (iType k = j; k < MatrixTraits::k; k++)
				M[i][k] = M[i][k] - M[j][k] * coefficient;
		}
	}
}

template<typename T, typename iType = std::size_t, iType N>
void toReducedRowEchelonForm(T (*M) [N], iType columns, iType rows)
{
	for (iType j = 0; j < columns; j++)
	{
		T lead = M[j][j];

		for (iType k = 0; k < rows; k++)
			M[j][k] /= lead;

		for (iType i = 0; i < columns; i++)
		{
			if (i == j) continue;

			T coefficient = M[i][j] / M[j][j];

			for (iType k = j; k < rows; k++)
				M[i][k] = M[i][k] - M[j][k] * coefficient;
		}
	}
}

template<typename MatrixType,
		 typename MatrixTraits = matrix_traits<MatrixType>>
void printSize(MatrixType& M)
{
	printf("%d %d\n", MatrixTraits::j, MatrixTraits::k);
}

int main(int argc, char** argv)
{
	double P[5][2] = { { -1.5, -1.2 },
					   { -0.2, 0 },
					   { 1, 0.5 },
					   { 5, 1 },
					   { 10, 1.2 } };

	auto C = toPoints(P);
	toReducedRowEchelonForm(C, 5, 6);

	for (std::size_t j = 0; j < 5; j++) {
		for (std::size_t k = 0; k < 6; k++)
			printf("%.7f, ", C[j][k]);
		printf("\n");
	}

	return 0;
}
