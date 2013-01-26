#ifndef _MAT_
#define _MAT_

class Matrix4f{
	
	public:
		float m_matrix[4][4];
		
		// identité
		inline void initIdentity(){
			m_matrix[0][0] = 1.0f; m_matrix[0][1] = 0.0f; m_matrix[0][2] = 0.0f; m_matrix[0][3] = 0.0f;
			m_matrix[1][0] = 0.0f; m_matrix[1][1] = 1.0f; m_matrix[1][2] = 0.0f; m_matrix[1][3] = 0.0f;
			m_matrix[2][0] = 0.0f; m_matrix[2][1] = 0.0f; m_matrix[2][2] = 1.0f; m_matrix[2][3] = 0.0f;
			m_matrix[3][0] = 0.0f; m_matrix[3][1] = 0.0f; m_matrix[3][2] = 0.0f; m_matrix[3][3] = 1.0f;
		}

		// multiplication
	    	inline Matrix4f operator*(const Matrix4f& Right) const{

			Matrix4f Ret;

			for (unsigned int i = 0 ; i < 4 ; i++) {
			    for (unsigned int j = 0 ; j < 4 ; j++) {
				Ret.m_matrix[i][j] = m_matrix[i][0] * Right.m_matrix[0][j] +
				              m_matrix[i][1] * Right.m_matrix[1][j] +
				              m_matrix[i][2] * Right.m_matrix[2][j] +
				              m_matrix[i][3] * Right.m_matrix[3][j];
			    }
			}

			return Ret;
	        }

		//constructeur
		Matrix4f();

};

#endif
