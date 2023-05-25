TARGET = a.out
OBJECT_DIR = bin
SOURCE_DIR = ./src

CXX = g++
LD = g++
CXXFLAGS = -Wall -pedantic -g
LDFLAGS = -lSDL2 -lSDL2_image

HEADERS := $(wildcard $(SOURCE_DIR)/*.hpp)
SOURCES := $(wildcard $(SOURCE_DIR)/*.cpp)
OBJECTS := $(patsubst $(SOURCE_DIR)/%.cpp, $(OBJECT_DIR)/%.o,$(SOURCES))
DEPENDENCIES := $(OBJECTS:%.o=%.d)


all: $(TARGET)

$(OBJECT_DIR)/%.o : $(SOURCE_DIR)/%.cpp
	mkdir -p bin
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(LDFLAGS)

$(TARGET): $(OBJECTS)
	$(LD) $^ $(LDFLAGS) -o $@

clean:
	rm -rf $(OBJECT_DIR); rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: clean all run

-include $(DEPENDENCIES)
