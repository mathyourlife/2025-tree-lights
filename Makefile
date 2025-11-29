CXX = g++
CXXFLAGS = -I tests -Wall -Wextra -std=c++11

TEST_TARGET = tests/test_clock

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): tests/test_clock.cpp tree/Clock.h tests/Arduino.h
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f $(TEST_TARGET)

.PHONY: test clean
