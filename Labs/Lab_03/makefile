# Makefile for Lab 03
# 02/10/2024
# Jason Lin 
# CPSC 2121 - 005

# Compilers and flags
CXX := g++
CXXFLAGS := -Wall 

# This will be the executable's name
EXECUTABLE := my_program

# This will make the object file needed for the executable
OBJECTS := Grouping.o $(patsubst %.cpp, %.o, $(wildcard T*.cpp))  

# This will be all the test files that will be ran 
TEST_FILES := T1.cpp T2.cpp T3.cpp T4.cpp T5.cpp T6.cpp T7.cpp T8.cpp T9.cpp

# Rule to compile each source file to an object file 
%o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to link all object files into the executable
$(EXECUTABLE): $(OBJECTS) 
	$(CXX) $(OBJECTS) -o $@

# Test target to run each TEST_FILES
test: $(EXECUTABLE)
	@$(foreach driver, $(TEST_FILES), \
		echo "\033[92;1mrunning $(driver)\033[0m"; \
		$(CXX) $(CXXFLAGS) -o $(EXECUTABLE)_$(driver:.cpp=) Grouping.o  $(driver); \
		./$(EXECUTABLE)_$(driver:.cpp=); \
		echo ""; \
		)

# Remove executable and object files
clean:
	rm -f $(EXECUTABLE) $(OBJECTS)
