#include "gl_framework.hpp"
#include "shader_util.hpp"
#include<iostream>
#include<math.h>
#include "stb_image.h"
using namespace std;

float points[303];
int ind[300];
int num_vert = 100;

GLuint shaderProgram;
GLuint vbo, vao, EBO;
//texture
unsigned int texture;

void genCoord(float r = 0.75f)
{
  const float pi_2 = 2*3.14159265359, increment = pi_2/100;
  float theta = 0.0;
  points[0] = points[1] = points[2] = 0;
  for(int i = 1; i <= 100; i++, theta+=increment)
  {
    points[3*i]=(r*cos(theta));
    points[3*i+1]=(r*sin(theta));
    points[3*i+2] = (0);
  }
  for(int i = 0; i<100; i++)
  {
    ind[3*i]=0; //origin
    ind[3*i+1]=(2*i +1)%200;
    ind[3*i+2]=(2*i +2)%200;
  }
}

void initShadersGL(void)
{
  std::string vertex_shader_file("simple_vs.glsl");
  std::string fragment_shader_file("simple_fs.glsl");

  std::vector<GLuint> shaderList;
  shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
  shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

  shaderProgram = csX75::CreateProgramGL(shaderList);
  
}

void initVertexBufferGL(void)
{
  glGenVertexArrays (1, &vao);  
  glBindVertexArray (vao);  
  glGenBuffers (1, &vbo); 
  glGenBuffers (1, &EBO); 
  glBindBuffer (GL_ARRAY_BUFFER, vbo);  
  glBufferData (GL_ARRAY_BUFFER,  sizeof (points), points, GL_STATIC_DRAW); 
  
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); 
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ind), ind, GL_STATIC_DRAW);  
  
  
  glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL); 
  glEnableVertexAttribArray (0);   
  glVertexAttribPointer (2, 2, GL_FLOAT, GL_FALSE, 1 * sizeof(float), (void*)(0*sizeof(float)));  
  glEnableVertexAttribArray (2);

  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  // set the texture wrapping/filtering options (on the currently bound texture object)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // load and generate the texture
  int width, height, nrChannels;
  unsigned char *data = stbi_load("texture.jpg", &width, &height, &nrChannels, 0);
  if (data)
  {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
  }
  else
  {
      std::cout << "Failed to load texture" << std::endl;
  }
  stbi_image_free(data);
}

void renderGL(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glUseProgram(shaderProgram);
  glBindTexture(GL_TEXTURE_2D, texture);
  glBindVertexArray (vao);

  glDrawElements(GL_TRIANGLES, num_vert*3, GL_UNSIGNED_INT,0);
}

int main(int argc, char** argv)
{
  cout<<"HI";
  //! The pointer to the GLFW window
  GLFWwindow* window;

  //! Setting up the GLFW Error callback
  glfwSetErrorCallback(csX75::error_callback);

  //! Initialize GLFW
  if (!glfwInit())
    return -1;

  //We want OpenGL 4.0
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); 
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  //This is for MacOSX - can be omitted otherwise
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
  //We don't want the old OpenGL 
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

  //! Create a windowed mode window and its OpenGL context
  window = glfwCreateWindow(1200, 1200, "textured ring", NULL, NULL);
  if (!window)
    {
      glfwTerminate();
      return -1;
    }
  
  //! Make the window's context current 
  glfwMakeContextCurrent(window);

  //Initialize GLEW
  //Turn this on to get Shader based OpenGL
  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (GLEW_OK != err)
    {
      //Problem: glewInit failed, something is seriously wrong.
      std::cerr<<"GLEW Init Failed : %s"<<std::endl;
    }

  //Print and see what context got enabled
  std::cout<<"Vendor: "<<glGetString (GL_VENDOR)<<std::endl;
  std::cout<<"Renderer: "<<glGetString (GL_RENDERER)<<std::endl;
  std::cout<<"Version: "<<glGetString (GL_VERSION)<<std::endl;
  std::cout<<"GLSL Version: "<<glGetString (GL_SHADING_LANGUAGE_VERSION)<<std::endl;

  //Keyboard Callback
  glfwSetKeyCallback(window, csX75::key_callback);
  //Framebuffer resize callback
  glfwSetFramebufferSizeCallback(window, csX75::framebuffer_size_callback);

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  //Initialize GL state
  genCoord();
  csX75::initGL();
  initShadersGL();
  initVertexBufferGL();

  // Loop until the user closes the window
  while (glfwWindowShouldClose(window) == 0)
    {
       
      // Render here
      renderGL();

      // Swap front and back buffers
      glfwSwapBuffers(window);
      
      // Poll for and process events
      glfwPollEvents();
    }
  
  glfwTerminate();
  return 0;
}

