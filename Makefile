# --------------------------------------------------------------------------
CXX = /Library/Developer/CommandLineTools/usr/bin/clang++
CXXFLAGS = -std=c++20 -g -w -isysroot $(shell xcrun --show-sdk-path)
TARGET = google
# --------------------------------------------------------------------------

$(TARGET): $(TARGET).cpp
	@echo "Compiling..."
	@$(CXX) $(CXXFLAGS) $< -o $@
	@echo "Done!! ✅"

clean:
	rm -f $(TARGET) *.o
# --------------------------------------------------------------------------
