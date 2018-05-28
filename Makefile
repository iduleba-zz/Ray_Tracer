CAMERA = Camera
LIGHT = Light
RAY = Ray
SCENE = Scene
SPHERE = Sphere
VECTOR = Vector
COLOR = Color
OUTPUT = rt

BIN = bin
SRC = src
TEMP = temp

FILES = $(COLOR).cpp $(VECTOR).cpp $(CAMERA).cpp $(LIGHT).cpp $(SPHERE).cpp $(RAY).cpp $(SCENE).cpp
OBJECTS = $(patsubst %.cpp,$(TEMP)/%.o,$(FILES))

GCC = g++

all : $(OUTPUT)

$(OUTPUT) : $(OBJECTS) $(TEMP)/Main.o
	$(GCC) $(INCLUDES) -o $(BIN)/$@ $^ $(LIBS)

$(TEMP)/%.o: $(SRC)/%.cpp
	$(GCC) -c $< -o $@

.PHONY: clean

clean :
	rm -f $(BIN)/$(OUTPUT)
	rm -f $(TEMP)/*.o $(TEMP)/*.out
