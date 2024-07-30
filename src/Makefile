CXX = clang++
CXXFLAGS = -Wall -Werror -std=c++17 -g
#-fsanitize=address
TEST_FLAG = -lgtest

# Paths and file lists
SOURCES = s21_model.cc s21_token.cc s21_parser.cc s21_map.cc s21_validator.cc s21_calculation.cc s21_polish_notation.cc s21_helpers.cc s21_main.cc
TESTS = $(wildcard tests/*.cc)
OBJECTS = $(SOURCES:.cc=.o)
TEST_OBJS = $(TESTS:.cc=.o)
EXECUTABLE = s21_calc

# Main targets
all: run

# Compilation and linking
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXECUTABLE)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Test compilation and execution
test: $(OBJECTS) $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) $(TEST_FLAG) -o $@ $^
	./test

# Project management
install:
	@cd Calc && cmake -S . -B ../CPP3_SmartCalc_v2.0
	@cd CPP3_SmartCalc_v2.0 && cmake --build .

run: install
	-@open ./CPP3_SmartCalc_v2.0/Calc.app

uninstall:
	@rm -rf ./CPP3_SmartCalc_v2.0

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE) html Doxyfile.bak latex build report *.gcda *.gcno CPP3_SmartCalc_v2.0/ SmartCalc_v2_0.tar.gz

# Documentation
dvi:
	doxygen Doxyfile
	open html/index.html

# Code formatting
linter:
	cp ../materials/linters/.clang-format ./
	find ./ -iname '*.h' -o -iname '*.cc' | xargs clang-format -i
	rm -rf .clang-format

# Archive distribution
dist:
	mkdir -p "SmartCalc_v2_0"
	cp -r *.cc *.h Makefile SmartCalc_v2_0/
	tar -zcf SmartCalc_v2_0.tar.gz SmartCalc_v2_0
	rm -rf SmartCalc_v2_0

# Coverage report
add_coverage:
	$(eval CXXFLAGS += --coverage -fprofile-arcs -ftest-coverage)

gcov_report: clean add_coverage test
	mkdir report
	lcov --no-external -t "test" -o test.info -c -d . 
	genhtml -o report test.info
	open report/index.html


# 	mkdir -p coverage-html
# gcovr --gcov-executable "/opt/goinfre/ardellen/homebrew/opt/llvm/bin/llvm-cov gcov" \
# 	--decisions \
# 	--html-theme github.dark-blue \
# 	--html-details coverage-html/index.html

# gcov_report: clean
# 	mkdir -p build
# 	$(CXX) $(CXXFLAGS) --coverage ${TESTS} ${SOURCES} -o ./build/test $(TEST_FLAGS)
# 	./build/test
# 	gcovr --gcov-executable "/usr/local/bin/ gcov" \
# 	--decisions \
# 	--html-details build/gcov_report.html
# 	open build/gcov_report.html

