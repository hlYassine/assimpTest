#ifndef _SCENE_
#define _SCENE_

#define GL3_PROTOTYPES 1
#include<GL/gl3.h>
#include<SDL2/SDL.h>
#include"input.h"
#include<iostream>
#include<string>

using namespace std;

#define LA 800
#define HA 600


class Scene{
	public:
		Scene(string pTitre, int pLargeur=LA, int pHauteur=HA);
		~Scene();
	
		bool initFenetre();
		bool initGL();
		void mainLoop();

	private:
		string fenetreTitre;
		int largeur;
		int hauteur;
	
		Input input;
	
		SDL_Window* fenetre;
		SDL_GLContext contexteOpenGL;
};

#endif
