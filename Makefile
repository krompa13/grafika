all:
	gcc -obeadando.exe -Iinclude/ src/* -lobj -lSOIL -lopengl32 -lglu32 -lglut32 -lm -std=c99
	
linux:
	gcc -obeadando -Iinclude/ src/* -lobj -lSOIL -lGL -lGLU -lglut -lm -std=c99