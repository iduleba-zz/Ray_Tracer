CAMERA = Camera
LIGHT = Light
RAY = Ray
SCENE = Scene
SPHERE = Sphere
VECTOR = Vector
COLOR = Color
IMAGE = Image
OUTPUT = rt

BIN = bin
SRC = src
TEMP = temp

FILES = $(COLOR).cpp $(VECTOR).cpp $(LIGHT).cpp $(SPHERE).cpp $(RAY).cpp $(IMAGE).cpp $(SCENE).cpp $(CAMERA).cpp
OBJECTS = $(patsubst %.cpp,$(TEMP)/%.o,$(FILES))

GCC = g++

all : $(OUTPUT)

$(OUTPUT) : $(OBJECTS) $(TEMP)/Main.o
	$(GCC) -g $(INCLUDES) -o $(BIN)/$@ $^ $(LIBS)

$(TEMP)/%.o: $(SRC)/%.cpp
	$(GCC) -c $< -o $@

.PHONY: clean

clean :
	rm -f $(BIN)/$(OUTPUT)
	rm -f $(TEMP)/*.o $(TEMP)/*.out
