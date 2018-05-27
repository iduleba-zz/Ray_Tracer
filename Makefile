CAMERA = Camera
LIGHT = Light
RAY = Ray
SCENE = Scene
SPHERE = Sphere
VECTOR = Vector
OUTPUT = rt

HFILES=$(wildcard *.hpp)
OBJECTS = Camera.o Light.o Ray.o Scene.o Sphere.o Vector.o

GCC = gcc

all : $(OUTPUT)

$(OUTPUT) : $(OBJECTS)
	$(GCC) $(INCLUDES) -o $@ $^ $(LIBS)

%o: %.cpp
	$(GCC) -c $< -o $@

.PHONY: clean

clean :
	rm -f $(OUTPUT)
	rm -f *.o *.out
