CAMERA = Camera
LIGHT = Light
RAY = Ray
SCENE = Scene
SPHERE = Sphere
VECTOR = Vector
OUTPUT = rt

BIN = bin
SRC = src
TEMP = temp

FILES = Camera.cpp Light.cpp Ray.cpp Scene.cpp Sphere.cpp Vector.cpp
OBJECTS = $(patsubst %.cpp,$(TEMP)/%.o,$(FILES))

GCC = gcc

all : $(OUTPUT)

$(OUTPUT) : $(OBJECTS) $(TEMP)/Main.o
	$(GCC) $(INCLUDES) -o $(BIN)/$@ $^ $(LIBS)

$(TEMP)/%.o: $(SRC)/%.cpp
	$(GCC) -c $< -o $@

.PHONY: clean

clean :
	rm -f $(BIN)/$(OUTPUT)
	rm -f $(TEMP)/*.o $(TEMP)/*.out
