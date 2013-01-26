# flags
ASSIMP=-lassimp
SDL=-lSDL2
GL=-lGL
LFLAGS=$(SDL) $(GL) $(ASSIMP)

# cibles principales
.PHONY : clean

# désactivation des règles implicites
.SUFFIXE :

# all

all: input.o scene.o main.o shader.o matrix4f.o vector3f.o transformation.o objet.o
	g++ $(LFLAGS) matrix4f.o vector3f.o transformation.o shader.o input.o scene.o objet.o main.o -o Main

main.o: main.cpp scene.h
	g++ $(LFLAGS) -c main.cpp -o main.o

objet.o: objet.cpp Shader.h matrix4f.h vector3f.h
	g++ $(ASSIMP) -c objet.cpp -o objet.o

scene.o: scene.cpp input.h transformation.h objet.h
	g++ $(LFLAGS) -c scene.cpp -o scene.o

input.o: input.cpp
	g++ $(SDL) -c input.cpp -o input.o

shader.o: Shader.cpp
	g++ $(GL) -c Shader.cpp -o shader.o

transformation.o: transformation.cpp matrix4f.h vector3f.h
	g++ -c transformation.cpp -o transformation.o

matrix4f: matrix4f.cpp
	g++ -c matrix4f.cpp -o matrix4f

vector3f: vector3f.cpp
	g++ -c vector3f.cpp -o vector3f
	
# clean
clean:
	rm *.o
