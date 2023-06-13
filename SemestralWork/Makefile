TARGET = beckaand
OBJECT_DIR = bin
SOURCE_DIR = src/
DOC_DIR = doc/

CXX = g++
LD = g++
CXXFLAGS = -Wall -pedantic -g -I/usr/include/libxml2

LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lxml2

HEADERS := $(wildcard $(SOURCE_DIR)/*.hpp)
SOURCES := $(wildcard $(SOURCE_DIR)/*.cpp)
OBJECTS := $(patsubst $(SOURCE_DIR)/%.cpp, $(OBJECT_DIR)/%.o,$(SOURCES))
DEPENDENCIES := $(OBJECTS:%.o=%.d)


all: $(TARGET) doc

$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	@mkdir -p $(OBJECT_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
$(TARGET): $(OBJECTS)
	$(LD) $(OBJECTS) $(LDFLAGS) -o $(TARGET)

compile: $(TARGET)

run: compile
	./$(TARGET)

clean:
	rm -rf $(OBJECT_DIR) $(TARGET) $(DOC_DIR)

doc:
	doxygen Doxyfile

.PHONY: clean all run

-include $(DEPENDENCIES)

