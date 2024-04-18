CC = g++
FLAGS = -Wall -Werror -Wextra -std=c++17
LIBS = -lgtest
OS = $(shell uname -s)

BACKEND = model
TARGET = $(BACKEND).a
SOURCES = $(wildcard $(BACKEND)/*.cc)
OBJECTS = $(patsubst %.cc, %.o, $(SOURCES))

FRONTEND = view
ENDPATH = build
EXECUTE = SmartCalcV2
EXECUTEMAC = $(EXECUTE).app
ARCNAME=$(EXECUTE)
ARCHDST=$(ARCNAME)/src
ARCHIVE=$(ARCNAME).tgz
ARCHSRC=$(BACKEND) $(FRONTEND) $(TESTDIR) Makefile readme.md ../materials/linters/.clang-format

TESTDIR = tests
TESTEXE = $(TESTDIR)/$(TESTDIR).out
TESTSRC = $(wildcard $(TESTDIR)/*.cc)
TESTOBJ = $(patsubst %.cc, %.o, $(TESTSRC))
TESTCOV = gcov_test
TESTREP = report

MANTEST = backend_manual_test.cc
TSTEXE = a.out

VGFLAGS=--trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all

# ---------------------------------------------------------------------------------------------------- #

all: clean install
	make run

install: uninstall
	mkdir $(ENDPATH)
	cd $(FRONTEND) && cmake CMakeLists.txt && make #&& make clean && rm Makefile
ifeq ($(OS), Linux)
	mv $(FRONTEND)/$(EXECUTE) $(ENDPATH)
else
	mv $(FRONTEND)/$(EXECUTEMAC) $(ENDPATH)
endif
	cd $(FRONTEND) make clean && rm Makefile

uninstall: clean_cmake
ifeq ($(OS), Linux)
	rm -rf $(ENDPATH) $(FRONTEND)/$(EXECUTE)
else
	rm -rf $(ENDPATH) $(FRONTEND)/$(EXECUTEMAC)
endif

run:
ifeq ($(OS), Linux)
	./$(ENDPATH)/$(EXECUTE)
else
	open $(ENDPATH)/$(EXECUTEMAC)
endif

dvi:
	open readme.md

dist: undist
	mkdir -p $(ARCHDST)
	cp -r $(ARCHSRC) $(ARCHDST)
	tar -cvzf $(ARCHIVE) $(ARCNAME)/
	rm -rf $(ARCNAME)

undist:
	rm -rf $(ARCNAME) $(ARCHIVE)

backend: clean
	$(CC) $(FLAGS) $(SOURCES) $(MANTEST) -g
	./$(TSTEXE)

$(TARGET): clean $(OBJECTS)
	$(CC) -c $(FLAGS) $(SOURCES)
	ar rcs $(TARGET) $(OBJECTS)

test: clean $(TARGET)
	$(CC) $(FLAGS) $(TESTSRC) $(SOURCES) -o $(TESTEXE) $(LIBS) -lgcov
	./$(TESTEXE)

memtest: test
ifeq ($(OS), Linux)
	CK_FORK=no valgrind -s $(VGFLAGS) ./$(TESTEXE)
else
#	CK_FORK=no leaks --atExit -- ./$(TESTEXE)
	./valgrind_ubuntu.sh
endif

style:
	cp ../materials/linters/.clang-format .
	clang-format -n $(BACKEND)/*.* $(TESTDIR)/*.* $(FRONTEND)/*.h $(FRONTEND)/*.cpp
	rm .clang-format

gcov_report: test
	$(CC) $(FLAGS) --coverage $(TESTSRC) $(SOURCES) $(TARGET) $(LIBS) -o $(TESTCOV)
	chmod +x *
	./$(TESTCOV)
	lcov -t "gcov_test" -o $(TESTCOV).info --no-external -c -d .
	genhtml -o $(TESTREP) $(TESTCOV).info
	open ./$(TESTREP)/index.html
	make clean_coverage_objects

clean: clean_objects clean_other clean_coverage clean_cmake

clean_objects:
	rm -rf *.o $(BACKEND)/*.o $(TESTDIR)/*.o $(FRONTEND)/*.o

clean_other:
	rm -rf *.out *.a *.dSYM
	rm -rf .clang-format $(TESTEXE) $(TESTCOV) $(TESTREP)

clean_coverage:
	rm -rf *.gcno *.gcda *.info

clean_cmake:
	rm -rf $(FRONTEND)/build-*
	rm -rf $(FRONTEND)/.qmake.stash $(FRONTEND)/Makefile
	rm -rf $(FRONTEND)/*.user $(FRONTEND)/*.cmake $(FRONTEND)/CMakeCache.txt $(FRONTEND)/CMakeFiles $(FRONTEND)/*_autogen
	rm -rf $(FRONTEND)/resources/*.user $(FRONTEND)/resources/*.cmake $(FRONTEND)/resources/CMakeCache.txt $(FRONTEND)/resources/CMakeFiles $(FRONTEND)/resources/*_autogen $(FRONTEND)/resources/Makefile $(FRONTEND)/resources/libqcustomplot.*

#ubuntu
install_gtest:
	sudo apt install libgtest-dev cmake -y
	cd /usr/src/gtest && sudo cmake CMakeLists.txt && sudo make
	cd lib && sudo cp *.a /usr/lib