#include"scene.h"


int main(){

	Scene scene("test");

	if(!scene.initFenetre())
		return -1;
	
	if(!scene.initGL())
		return -1;

	scene.mainLoop();
	
	return 0;
}
