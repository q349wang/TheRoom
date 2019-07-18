CXX = g++-5
CXXFLAGS = -g -std=c++14 -Wall -O -MMD
EXEC = TheRoom
SOURCEDIR = src
TESTDIR = test

TESTEXEC = TestRunner

SOURCES := ${shell find ${SOURCEDIR} -name '*.cc'}
TESTFILES := ${shell find ${TESTDIR} -name '*.cc'}

OBJECTS = ${SOURCES:.cc=.o}
DEPENDS = ${OBJECTS:.o=.d}

TESTOBJS = ${TESTFILES:.cc=.o}
TESTERS = ${filter %Tests.cc, ${TESTFILES}}
TESTEDOBJS = ${subst test/, src/, ${TESTERS:Tests.cc=.o}}
TESTDEPS = ${TESTOBJS:.o=.d}
TESTEDDEPS = ${TESTEDOBJS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -lX11 -o ${EXEC}

-include ${DEPENDS}

.PHONY: all

all: ${OBJECTS}

.PHONY: clean

clean:
	rm -f ${OBJECTS} ${EXEC} ${DEPENDS}

${TESTEXEC}: ${TESTOBJS} ${OBJECTS}
	${CXX} ${CXXFLAGS} ${TESTOBJS} ${OBJECTS} -o ${TESTEXEC}

-include ${TESTDEPS}
-include ${TESTEDDEPS}

.PHONY: cleanTest

cleanTest:
	rm  -f ${TESTOBJS} ${TESTEXEC} ${TESTDEPS}

print-%  : ; @echo $* = $($*)
