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

GCC = g++ -std=c++11
MPI = mpic++

all : $(OUTPUT)

$(OUTPUT) : $(OBJECTS) $(TEMP)/Main.o
	$(MPI) -g $(INCLUDES) -o $(BIN)/$@ $^ $(LIBS)

$(TEMP)/%.o: $(SRC)/%.cpp
	$(MPI) -g -c $< -o $@

.PHONY: clean

clean :
	rm -f $(BIN)/$(OUTPUT)
	rm -f $(TEMP)/*.o $(TEMP)/*.out
