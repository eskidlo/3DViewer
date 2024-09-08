CXX=g++
CXXFLAGS=-std=c++17 -Wall -Werror -Wextra
TEST_FGLAGS=-lgtest
GCOV_FLAGS=-fprofile-arcs -ftest-coverage
TEST_SRC=check/base.cc check/matrix_test.cc check/main.cc check/adapter_test.cc check/parser_test.cc check/facade_test.cc
LIB_SRC=model/adapter.cc model/builder.cc model/facade.cc model/matrix.cc model/parser.cc
OPEN_CMD=open

all: clean install gcov_report

test:
	@echo "\033[0;33m Preparing tests......\033[0m"
	$(CXX) $(CXXFLAGS) $(TEST_SRC) $(LIB_SRC) $(TEST_FGLAGS)
	./a.out

gcov_report:
	@echo "\033[0;33m Preparing tests...\033[0m"
	$(CXX) $(CXXFLAGS) $(TEST_SRC) $(LIB_SRC) $(TEST_FGLAGS) $(GCOV_FLAGS)
	@./a.out
	@echo "\033[0;33m Preparing report...\033[0m"
	@lcov --no-external -capture --directory . --output-file main_coverage.info
	@genhtml *.info -o ./gcov_report
	@rm -rf *.gcda *.gcno
	@$(OPEN_CMD) gcov_report/index.html

install:
	@cmake -B build && make -C build 
	@mv build 3DViewer
	@rm -rf 3DViewer/build

uninstall:
	 rm -rf 3dViewer

clean:
	@rm -rf a.out *.gcno *.a *.gcda gcov_report *.pdf *.dvi *.info