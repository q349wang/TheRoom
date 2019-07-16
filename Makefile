CXX = g++-5
CXXFLAGS = -g -std=c++14 -Wall -O -MMD
EXEC = TheRoom
SOURCEDIR = src
SOURCES := ${shell find ${SOURCEDIR} -name '*.cc'}
OBJECTS = ${SOURCES:.cc=.o}
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -lX11 -o ${EXEC}

-include ${DEPENDS}

.PHONY: all

all: ${OBJECTS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}

myprogram: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o myprogram

.PHONY: cleanTest

cleanTest:
	rm ${OBJECTS} myprogram ${DEPENDS}

.PHONY: cleanAll

cleanAll:
	rm ${OBJECTS} ${DEPENDS}