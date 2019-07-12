CXX = g++-5
CXXFLAGS = -g -std=c++14 -Wall -O -MMD
EXEC = TheRoom
SOURCEDIR = src
TESTDIR = test

TESTEXEC = TestRunner

SOURCES := ${shell find ${SOURCEDIR} -name '*.cc'}
TESTERS := ${shell find ${TESTDIR} -name '*.cc'}

OBJECTS = ${SOURCES:.cc=.o}
DEPENDS = ${OBJECTS:.o=.d}

TESTOBJS = ${TESTERS:.cc=.o}
TESTEDOBJS = ${TESTERS:Tests.cc=.o}
TESTDEPS = ${TESTOBJS:.o=.d}
TESTEDDEPS = ${TESTEDOBJS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -lX11 -o ${EXEC}

-include ${DEPENDS}

.PHONY: all

all: ${OBJECTS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}

${TESTEXEC}: ${TESTOBJS} ${TESTEDOBJS}
	${CXX} ${CXXFLAGS} ${TESTOBJS} ${TESTEDOBJS} -o ${TESTEXEC}

-include ${TESTDEPS}

-include ${TESTEDDEPS}

.PHONY: cleanTest

cleanTest:
	rm ${TESTOBJS} ${TESTEXEC} ${TESTDEPS}