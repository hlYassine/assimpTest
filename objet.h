#ifndef _OBJ_
#define _OBJ_

#include<assimp/mesh.h>
#include<assimp/scene.h>
#include<assimp/Importer.hpp>

#define GL3_PROTOTYPES 1
#include<GL/gl3.h>

#include<iostream>
#include<vector>
#include<string>

#include"matrix4f.h"
#include"vector3f.h"
#include"Shader.h"

#define INVALID 0xFFFFFFFF

using namespace std;

//Vertex
struct Vertex{
	Vector3f pos;
	Vector3f normal;

	Vertex(){}

	Vertex(Vector3f pPos, Vector3f pNormal){
		pos = pPos;
		normal = pNormal;
	}
};

class Objet{
	
	private:
		Shader shaderCouleur;

		struct Maillage{
			Maillage();
			~Maillage();
			bool init(const vector<Vertex>& vertices, const vector<unsigned int>& indices);
			GLuint VB;
			GLuint VI;

			unsigned int nbreIndices;
			unsigned int materialIndex;
		};

	
		struct Materiau{
			Materiau();

			Vector3f diffuseColor;
			Vector3f ambientColor;
			Vector3f specularColor;
			Vector3f emissive;
			float shininess;
			float refractIndex;
		};	

		Maillage mesh;
		vector<unsigned int> materiau;

	public:
		Objet();
		~Objet();
		bool chargerModele(const string& fichierObj);
		void initFromScene(const aiScene* scene);
		void initObjet(const aiMesh* objet);
		void initMateriau(const aiScene* scene,const aiMesh* objet);
		void afficher(const Matrix4f* transformation);
};

#endif
