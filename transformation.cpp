#include"transformation.h"

#include<cmath>

#define ToRadian(x) ((x) * M_PI / 180.0f)
#define ToDegree(x) ((x) * 180.0f / M_PI)


Transformation::Transformation(){

	m_modelview.initIdentity();

	//scale
	m_scale.x = 1.0f;
	m_scale.y = 1.0f;
	m_scale.z = 1.0f;

	//translate
	m_translate.x = 0.0f;
	m_translate.y = 0.0f;
	m_translate.z = 0.0f;

	//rotate
	m_angleRot = 0.0f;

	m_axeRot.x = 0.0f;
	m_axeRot.y = 0.0f;
	m_axeRot.z = 1.0f;
}

void Transformation::setPersProj(float fov,float l,float h,float near,float far){
	
	m_persProj.fov = fov;
	m_persProj.L = l;
	m_persProj.H = h;
	m_persProj.near = near;
	m_persProj.far = far;
}

Matrix4f Transformation::scale(){
	
	Matrix4f scale;
	
	scale.m_matrix[0][0] = m_scale.x;
	scale.m_matrix[1][1] = m_scale.y;
	scale.m_matrix[2][2] = m_scale.z;
	scale.m_matrix[3][3] = 1.0f;

	return scale;
}

Matrix4f Transformation::translate(){

	Matrix4f translate;

	translate.initIdentity();
	translate.m_matrix[0][3] = m_translate.x;
	translate.m_matrix[1][3] = m_translate.y;
	translate.m_matrix[2][3] = m_translate.z;

	return translate;
}

Matrix4f Transformation::rotate(){

    Matrix4f rotation;
    m_axeRot.Normalize();

    m_angleRot = ToRadian(m_angleRot);

    rotation.m_matrix[0][0] = m_axeRot.x*m_axeRot.x * (1 - cos(m_angleRot)) + cos(m_angleRot);
    rotation.m_matrix[0][1] = m_axeRot.x*m_axeRot.y * (1 - cos(m_angleRot)) - m_axeRot.z*sin(m_angleRot);
    rotation.m_matrix[0][2] = m_axeRot.x*m_axeRot.z * (1 - cos(m_angleRot)) + m_axeRot.y*sin(m_angleRot);

    rotation.m_matrix[1][0] = m_axeRot.x*m_axeRot.y * (1 - cos(m_angleRot)) + m_axeRot.z*sin(m_angleRot);
    rotation.m_matrix[1][1] = m_axeRot.y*m_axeRot.y * (1 - cos(m_angleRot)) + cos(m_angleRot);
    rotation.m_matrix[1][2] = m_axeRot.y*m_axeRot.z * (1 - cos(m_angleRot)) - m_axeRot.x*sin(m_angleRot);

    rotation.m_matrix[2][0] = m_axeRot.x*m_axeRot.z * (1 - cos(m_angleRot)) - m_axeRot.y*sin(m_angleRot);
    rotation.m_matrix[2][1] = m_axeRot.y*m_axeRot.z * (1 - cos(m_angleRot)) + m_axeRot.x*sin(m_angleRot);
    rotation.m_matrix[2][2] = m_axeRot.z*m_axeRot.z * (1 - cos(m_angleRot)) + cos(m_angleRot);

    rotation.m_matrix[3][3] = 1.0;

    return rotation;
}

Matrix4f Transformation::perspectiveProj(){

	Matrix4f projection;
	const float ar         = m_persProj.L / m_persProj.H;
	const float zRange     = m_persProj.near - m_persProj.far;
	const float tanHalfFOV = tanf(ToRadian(m_persProj.fov / 2.0f));

	projection.m_matrix[0][0] = tanHalfFOV/ar;
        projection.m_matrix[1][1] = tanHalfFOV;
        projection.m_matrix[2][2] = (m_persProj.near + m_persProj.far)/zRange ;
        projection.m_matrix[2][3] = 2.0f * m_persProj.far*m_persProj.near/zRange;
        projection.m_matrix[3][2] = -1.0f;

	return projection;
}

const Matrix4f* Transformation::transformation(){
	m_modelview = m_modelview * perspectiveProj()  * translate() * rotate() * scale();
	return &m_modelview;	
}

const Matrix4f* Transformation::transformation(const Matrix4f& camTranslate,const Matrix4f& camTransform){
	m_modelview = m_modelview * perspectiveProj()  * camTransform * camTranslate * translate() * rotate() * scale();
	return &m_modelview;	
}

void Transformation::setScale(const Vector3f& scale){

	m_scale = scale;
}

void Transformation::setTranslate(const Vector3f& translate){

	m_translate = translate;
}

void Transformation::setRotate(const float& angleRot,const Vector3f& axeRot){

	m_angleRot = angleRot;
	m_axeRot = axeRot;
}

void Transformation::initModelview(){
	m_modelview.initIdentity();
}
