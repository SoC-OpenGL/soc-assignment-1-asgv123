OPENGLLIB= -lGL
GLEWLIB= -lGLEW
GLFWLIB = -lglfw3
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB) -lGL -lm -lGLU -lGLEW `pkg-config glfw3 --static --libs`
LDFLAGS=-L/usr/local/lib 
CPPFLAGS=-I/usr/local/include

#BIN1=01_triangle
BIN1=ring
BIN2=disk
BIN3=mine
BIN4=gradTriangle
#SRCS1=01_triangle.cpp gl_framework.cpp shader_util.cpp 
SRCS1=ring.cpp gl_framework.cpp shader_util.cpp 
SRCS2=disk.cpp gl_framework.cpp shader_util.cpp
SRCS3=mine.cpp gl_framework.cpp shader_util.cpp
SRCS4=gradTriangle.cpp gl_framework.cpp shader_util.cpp
INCLUDES=gl_framework.hpp shader_util.hpp

all: $(BIN1) $(BIN2) $(BIN3) $(BIN4)

$(BIN1): $(SRCS1) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS1) -o $(BIN1) $(LDFLAGS) $(LIBS)

$(BIN2): $(SRCS2) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS2) -o $(BIN2) $(LDFLAGS) $(LIBS)

$(BIN3): $(SRCS3) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS3) -o $(BIN3) $(LDFLAGS) $(LIBS)

$(BIN4): $(SRCS4) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS4) -o $(BIN4) $(LDFLAGS) $(LIBS)

clean:
	rm -f *~ *.o $(BIN1) $(BIN2) $(BIN3) $(BIN4)
