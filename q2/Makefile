CC=g++

OPENGLLIB= -lGL
GLEWLIB= -lGLEW
GLFWLIB = -lglfw3
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB) -lGL -lm -lGLU -lGLEW `pkg-config glfw3 --static --libs`
LDFLAGS=-L/usr/local/lib 
CPPFLAGS=-I/usr/local/include

BIN4=gradTriangle
BIN=02_colorcube
BIN2=chess

SRCS=02_colorcube.cpp gl_framework.cpp shader_util.cpp 
SRCS4=gradTriangle.cpp gl_framework.cpp shader_util.cpp
SRCS2=chess.cpp gl_framework.cpp shader_util.cpp
INCLUDES=gl_framework.hpp shader_util.hpp 02_colorcube.hpp

all: $(BIN) $(BIN4) $(BIN2)

$(BIN): $(SRCS) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS) -o $(BIN) $(LDFLAGS) $(LIBS)

$(BIN4): $(SRCS4) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS4) -o $(BIN4) $(LDFLAGS) $(LIBS)

$(BIN2): $(SRCS2) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS2) -o $(BIN2) $(LDFLAGS) $(LIBS)

clean:
	rm -f *~ *.o $(BIN) $(BIN4) $(BIN2) 
