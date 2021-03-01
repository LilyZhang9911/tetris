iCXX = g++
CXXFLAGS = -std=c++14 -Wall -Werror=vla -g -MMD
EXEC = biquadris
OBJECTS = main.o window.o board.o block.o I.o L.o Z.o S.o O.o J.o T.o star.o level.o level0.o level1.o level2.o level3.o level4.o cell.o special.o blind.o heavy.o force.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
