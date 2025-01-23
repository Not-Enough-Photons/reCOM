#include "zmath.h"
#include "glm/ext/matrix_transform.hpp"

const float* CMatrix::operator[](const int row)
{
	return m_matrix[row];
}

const float* CMatrix::GetTranslate() const
{
	return m_matrix[3];
}

/// Transform a matrix by a point.
void CMatrix::Transform(CPnt3D* point, s32 count) const
{
	glm::mat4x4 mat(1.0f);
	
	mat[0][0] = m_matrix[0][0];
	mat[0][1] = m_matrix[1][0];
	mat[0][2] = m_matrix[2][0];
	mat[0][3] = m_matrix[3][0];

	mat[1][0] = m_matrix[0][1];
	mat[1][1] = m_matrix[1][1];
	mat[1][2] = m_matrix[2][1];
	mat[1][3] = m_matrix[3][1];

	mat[2][0] = m_matrix[0][2];
	mat[2][1] = m_matrix[1][2];
	mat[2][2] = m_matrix[2][2];
	mat[2][3] = m_matrix[3][2];

	mat[3][0] = m_matrix[0][3];
	mat[3][1] = m_matrix[1][3];
	mat[3][2] = m_matrix[2][3];
	mat[3][3] = m_matrix[3][3];

	mat = glm::translate(mat, glm::vec3(point->x, point->y, point->z));

	point->x = mat[3][0];
	point->y = mat[3][1];
	point->z = mat[3][2];
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

void CMatrix::ToEuler(CPnt3D* p)
{

}