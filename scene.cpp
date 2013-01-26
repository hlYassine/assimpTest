#include "scene.h"
#include"transformation.h"
#include"objet.h"

Scene::Scene(string pTitre, int pLargeur, int pHauteur){
	fenetreTitre = pTitre;
	largeur = pLargeur;
	hauteur = pHauteur;
}

Scene::~Scene(){
	SDL_GL_DeleteContext(contexteOpenGL);
	SDL_DestroyWindow(fenetre);
	SDL_Quit();
}

bool Scene::initFenetre(){
	
	//SDL
	if(SDL_Init(SDL_INIT_VIDEO)<0){
		cout<<"Erreur SDL"<<endl;
		SDL_Quit();
		return -1;		
	}

	//version OpenGL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,1);

	//double buffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,24);

	//fenetre
	fenetre = SDL_CreateWindow(fenetreTitre.c_str(),
					SDL_WINDOWPOS_CENTERED, 
					SDL_WINDOWPOS_CENTERED,
					largeur, hauteur,
					SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL);

	contexteOpenGL = SDL_GL_CreateContext(fenetre);	

	return 1;
}


bool Scene::initGL(){

	glEnable(GL_DEPTH_TEST);
	return 1;
}

void Scene::mainLoop(){

	
	Transformation trf;
	trf.setPersProj(70.0f, 800, 600, 1.0f, 100.0f);
	
	Objet o;
	o.chargerModele("objets/pion.obj");

	while(!input.terminer()){

		input.updateEvent();
		
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		

		trf.initModelview();

		o.afficher(trf.transformation());
		SDL_GL_SwapWindow(fenetre);

	}
}
