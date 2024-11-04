CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 `pkg-config --cflags --libs libpng tesseract lept`
TARGET = screenshot_to_text
SOURCES = main.cpp

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)

