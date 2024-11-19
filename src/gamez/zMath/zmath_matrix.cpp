#include "zmath_main.h"

const float* CMatrix::operator[](const int row)
{
	return m_matrix[row];
}

const float* CMatrix::GetTranslate() const
{
	return m_matrix[3];
}

void CMatrix::Multiply(const CMatrix* first, const CMatrix* second)
{
	// I never want to do this again.

	// First row
	m_matrix[0][0] = 
		(first->m_matrix[0][0] * second->m_matrix[0][0]) + 
		(first->m_matrix[0][1] * second->m_matrix[1][0]) + 
		(first->m_matrix[0][2] * second->m_matrix[2][0]) + 
		(first->m_matrix[0][3] * second->m_matrix[3][0]);

	m_matrix[0][1] =
		(first->m_matrix[0][0] * second->m_matrix[0][1]) +
		(first->m_matrix[0][1] * second->m_matrix[1][1]) +
		(first->m_matrix[0][2] * second->m_matrix[2][1]) +
		(first->m_matrix[0][3] * second->m_matrix[3][1]);

	m_matrix[0][2] =
		(first->m_matrix[0][0] * second->m_matrix[0][2]) +
		(first->m_matrix[0][1] * second->m_matrix[1][2]) +
		(first->m_matrix[0][2] * second->m_matrix[2][2]) +
		(first->m_matrix[0][3] * second->m_matrix[3][2]);

	m_matrix[0][3] =
		(first->m_matrix[0][0] * second->m_matrix[0][3]) +
		(first->m_matrix[0][1] * second->m_matrix[1][3]) +
		(first->m_matrix[0][2] * second->m_matrix[2][3]) +
		(first->m_matrix[0][3] * second->m_matrix[3][3]);

	// Second row
	m_matrix[1][0] =
		(first->m_matrix[1][0] * second->m_matrix[0][0]) +
		(first->m_matrix[1][1] * second->m_matrix[1][0]) +
		(first->m_matrix[1][2] * second->m_matrix[2][0]) +
		(first->m_matrix[1][3] * second->m_matrix[3][0]);

	m_matrix[1][1] =
		(first->m_matrix[1][0] * second->m_matrix[0][1]) +
		(first->m_matrix[1][1] * second->m_matrix[1][1]) +
		(first->m_matrix[1][2] * second->m_matrix[2][1]) +
		(first->m_matrix[1][3] * second->m_matrix[3][1]);

	m_matrix[1][2] =
		(first->m_matrix[1][0] * second->m_matrix[0][2]) +
		(first->m_matrix[1][1] * second->m_matrix[1][2]) +
		(first->m_matrix[1][2] * second->m_matrix[2][2]) +
		(first->m_matrix[1][3] * second->m_matrix[3][2]);

	m_matrix[1][3] =
		(first->m_matrix[1][0] * second->m_matrix[0][3]) +
		(first->m_matrix[1][1] * second->m_matrix[1][3]) +
		(first->m_matrix[1][2] * second->m_matrix[2][3]) +
		(first->m_matrix[1][3] * second->m_matrix[3][3]);

	// Third row
	m_matrix[2][0] =
		(first->m_matrix[2][0] * second->m_matrix[0][0]) +
		(first->m_matrix[2][1] * second->m_matrix[1][0]) +
		(first->m_matrix[2][2] * second->m_matrix[2][0]) +
		(first->m_matrix[2][3] * second->m_matrix[3][0]);

	m_matrix[2][1] =
		(first->m_matrix[2][0] * second->m_matrix[0][1]) +
		(first->m_matrix[2][1] * second->m_matrix[1][1]) +
		(first->m_matrix[2][2] * second->m_matrix[2][1]) +
		(first->m_matrix[2][3] * second->m_matrix[3][1]);

	m_matrix[2][2] =
		(first->m_matrix[2][0] * second->m_matrix[0][2]) +
		(first->m_matrix[2][1] * second->m_matrix[1][2]) +
		(first->m_matrix[2][2] * second->m_matrix[2][2]) +
		(first->m_matrix[2][3] * second->m_matrix[3][2]);

	m_matrix[2][3] =
		(first->m_matrix[2][0] * second->m_matrix[0][3]) +
		(first->m_matrix[2][1] * second->m_matrix[1][3]) +
		(first->m_matrix[2][2] * second->m_matrix[2][3]) +
		(first->m_matrix[2][3] * second->m_matrix[3][3]);
}