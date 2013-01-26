#include"matrix4f.h"

Matrix4f::Matrix4f(){

	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			m_matrix[i][j] = 0.0f;

}
