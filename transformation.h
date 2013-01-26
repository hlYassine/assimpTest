#ifndef _TRANSF_
#define _TRANSF_

#include"matrix4f.h"
#include"vector3f.h"

class Transformation{
private:
		Matrix4f m_modelview;

		Vector3f m_scale;
		Vector3f m_translate;
		float m_angleRot; //angle de rotation
		Vector3f m_axeRot; //axe de rotation

		//perpective et projection
		struct PersProj{
			float fov;
			float L;
			float H;
			float near;
			float far;
		};
	
		struct PersProj m_persProj;

	public:
		Transformation();
		Matrix4f scale();
		Matrix4f rotate();
		Matrix4f translate();
		Matrix4f perspectiveProj();
		const Matrix4f* transformation();
		const Matrix4f* transformation(const Matrix4f& camTranslate,const Matrix4f& camTransform);

		void setScale(const Vector3f& scale);
		void setTranslate(const Vector3f& translate);
		void setRotate(const float& angleRot,const Vector3f& axeRote);
		void setPersProj(float fov,float l,float h,float near,float far);
		void initModelview();
};

#endif
