CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Icore -Icore/ARM -Icore/audio -Icore/fs -Icore/gpu/emu -Icore/gpu/vk -Icore/JIT

SRC := \
    ui/main.cpp \
    core/audio/audio.cpp \
    core/fs/romfs.cpp \
    core/gpu/emu/emugpu.cpp \
    core/gpu/vk/emugpuvk.cpp \
    core/JIT/jit.cpp

OBJ := $(SRC:.cpp=.o)
TARGET := app

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean
