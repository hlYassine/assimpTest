#include"objet.h"
#include<assimp/postprocess.h>

//Maillage
Objet::Maillage::Maillage(){
	VB = INVALID;
	VI = INVALID;
	
	materialIndex = INVALID;
	nbreIndices = 0;

}

Objet::Maillage::~Maillage(){

	if(VB != INVALID)
		glDeleteBuffers(1,&VB);

	if(VI != INVALID)
		glDeleteBuffers(1,&VI);
}

bool Objet::Maillage::init(const vector<Vertex>& vertices, const vector<unsigned int>& indices){
	nbreIndices = indices.size();
	
	//verices
	glGenBuffers(1,&VB);
	glBindBuffer(GL_ARRAY_BUFFER,VB);
	glBufferData(GL_ARRAY_BUFFER,sizeof(Vertex)*vertices.size(),&vertices[0],GL_STATIC_DRAW);
	
	//indices
	glGenBuffers(1,&VI);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,VI);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int)*nbreIndices,&indices[0],GL_STATIC_DRAW);
}

//Materiau
Objet::Materiau::Materiau(){
	shininess = 0.0f;
	refractIndex = 0.0f;
}
bool Objet::chargerModele(const string& fichierObj){
	
	bool ret = false;
	Assimp::Importer Importer;
	
	const aiScene* lScene = Importer.ReadFile(fichierObj.c_str(),aiProcess_Triangulate|aiProcess_GenSmoothNormals|aiProcess_FlipUVs);

	if(lScene){
		ret = true;
		cout<<"chargement effectué avec succés..."<<endl;
		initFromScene(lScene);
	}
	else
		cout<<"erreur de chargement..."<<endl;

	return ret;
}

void Objet::initFromScene(const aiScene* pScene){
	
	const aiMesh* lMesh = NULL;

	if(pScene->HasMaterials()){
		materiau.resize(pScene->mNumMaterials);
		cout<<"Matériau ..... ok"<<endl;
	}
	else
		cout<<"Pas de matériau!!"<<endl;
	
	
	if(pScene->HasMeshes()){
		lMesh = pScene->mMeshes[0];
		cout<<"Maillage ..... ok"<<endl;
	}
	else
		cout<<"Pas de maillage!"<<endl;
			
	initObjet(lMesh);
	cout<<"initObjet ..... ok"<<endl;
			
	initMateriau(pScene,lMesh);
	cout<<"initMateriau ..... ok"<<endl;
	
}

void Objet::initObjet(const aiMesh* pMesh){
	mesh.materialIndex = pMesh->mMaterialIndex;

	vector<Vertex> lVertices;
	vector<unsigned int> lIndices;

	const aiVector3D zero3D(0.0f,0.0f,0.0f);

	//lVertices
	for(unsigned int i=0;i<pMesh->mNumVertices;i++){
		const aiVector3D* position = &(pMesh->mVertices[i]);
		const aiVector3D* normal = &(pMesh->mNormals[i]);

		Vertex v(Vector3f(position->x,position->y,position->z),
			Vector3f(normal->x,normal->y,normal->z)
		);

		lVertices.push_back(v);
	}

	//lIndices
	for(unsigned int i=0;i<pMesh->mNumFaces;i++){
		
		const aiFace& lFace = pMesh->mFaces[i];
		lIndices.push_back(lFace.mIndices[0]);
		lIndices.push_back(lFace.mIndices[1]);
		lIndices.push_back(lFace.mIndices[2]);
	}

	mesh.init(lVertices,lIndices);
}

void Objet::initMateriau(const aiScene* scene,const aiMesh* pMesh){
	
	Materiau materiau;

	aiMaterial *mat = scene->mMaterials[pMesh->mMaterialIndex];

	//couleur diffuse
	aiColor3D colorD = aiColor3D(0.0f,0.0f,0.0f);
	mat->Get(AI_MATKEY_COLOR_DIFFUSE,colorD);
	materiau.diffuseColor = Vector3f(colorD.r,colorD.g,colorD.b);

	//couleur specular
	aiColor3D colorS = aiColor3D(0.0f,0.0f,0.0f);
	mat->Get(AI_MATKEY_COLOR_SPECULAR,colorS);
	materiau.specularColor = Vector3f(colorS.r,colorS.g,colorS.b);

	//couleur ambient
	aiColor3D colorA = aiColor3D(0.0f,0.0f,0.0f);
	mat->Get(AI_MATKEY_COLOR_AMBIENT,colorA);
	materiau.ambientColor = Vector3f(colorA.r,colorA.g,colorA.b);

	//refraction
	float indiceRef;
	mat->Get(AI_MATKEY_REFRACTI,indiceRef);
	materiau.refractIndex = indiceRef;
	
	//specular exponent
	float spExp;
	mat->Get(AI_MATKEY_SHININESS,spExp);
	materiau.shininess = spExp;

	//emissive
	aiColor3D colorE = aiColor3D(0.0f,0.0f,0.0f);
	mat->Get(AI_MATKEY_COLOR_EMISSIVE,colorE);
	materiau.emissive = Vector3f(colorE.r,colorE.g,colorE.b);
}

void Objet::afficher(const Matrix4f* transformation){
	//activation du shader
	glUseProgram(shaderCouleur.getProgramID());

	//tableaux indices,vertices et couleurs
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	//lier les matrices avec le shader
	glUniformMatrix4fv(glGetUniformLocation(shaderCouleur.getProgramID(),"transformation"),1,GL_TRUE,(const GLfloat*)transformation);

	//dessin
	glBindBuffer(GL_ARRAY_BUFFER,mesh.VB);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),0);
	glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(const GLvoid*)12);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,mesh.VI);


	glDrawElements(GL_TRIANGLES,mesh.nbreIndices,GL_UNSIGNED_INT,0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	//désactivation shader
	glUseProgram(0);
}

Objet::Objet():shaderCouleur("Shaders/couleurs.vert","Shaders/couleurs.frag"){
	shaderCouleur.initialiser();
}

Objet::~Objet(){

}
