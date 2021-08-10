#define STB_IMAGE_IMPLEMENTATION

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <shader/shader_s.h>

#include <iostream>
#include <math.h>

#include "stb_image/stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

//settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
   //glfw: initialize and configure
   glfwInit();
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

   //glfw window creation
   GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr,nullptr);
   if(window == nullptr)
   {
      std::cout << "Failed to create GLFW window" << std::endl;
      glfwTerminate();
      return -1;
   }
   glfwMakeContextCurrent(window);
   glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

   //glad: load all OpenGL function pointers
   if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
   {
      std::cout << "Failed to initialize GLAD" << std::endl;
      return -1;
   }

   // build and compile our shader program
   // ---------------------------------------
   Shader ourShader("../shaders/learnopengl/texture_shader.vs", "../shaders/learnopengl/texture_shader.fs");

   //set up vertex data (and buffer(s)) and configure vertex attributes
   //-----------------------------------------------------------------
   float vertices[]{
      // positions       // colors        //texture coords
      0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
      0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
     -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, // bottom left
     -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
   };

   unsigned indices[]{ // starting at 0 !
      0, 1, 3,// first triangle
      1, 2, 3 // second triangle 
   };

   unsigned int VBO, VAO, EBO;
   glGenVertexArrays(1, &VAO);
   glGenBuffers(1, &VBO);
   glGenBuffers(1, &EBO);
   //bind the Vertes Arrays Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
   glBindVertexArray(VAO);

   glBindBuffer(GL_ARRAY_BUFFER, VBO);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

   // position attribute
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
   glEnableVertexAttribArray(0);
   // color attribute
   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
   glEnableVertexAttribArray(1);
   // texture attribute
   glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (6 * sizeof(float)));
   glEnableVertexAttribArray(2);

    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

   // texture 1
   unsigned int texture1;
   glGenTextures(1, &texture1);
   glBindTexture(GL_TEXTURE_2D, texture1);
   // set the texture wrapping parameters
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   // set texture filturing parameters
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   // load image, create texture and generate mipmaps
   int width, height, nrChannels;
   stbi_set_flip_vertically_on_load(true);
   unsigned char *data = stbi_load("../res/textures/container.jpg", &width, &height, &nrChannels, 0);

   if(data)
   {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
   }
   else
   {
      std::cout << "Failed to load texture" << std::endl;
   }

   stbi_image_free(data);

   // texture 2
   unsigned int texture2;
   glGenTextures(1, &texture2);
   glBindTexture(GL_TEXTURE_2D, texture2);
   // set the texture wrapping parameters
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   // set texture filturing parameters
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   // load image, create texture and generate mipmaps
   data = stbi_load("../res/textures/awesomeface.png", &width, &height, &nrChannels, 0);
   if(data)
   {
      // as awesomeface.png has transparency and thus an alpha channel the data type ahs to be GL_RGBA
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
   }
   else
   {
      std::cout << "Failed to load texture" << std::endl;
   }

   stbi_image_free(data);

   // tell OpenGL for each sampler which texture unit it belongs to (only has to be done once)
   ourShader.use();
   // either set it manually
   glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
   // or set it via the texture class
   ourShader.setInt("texture2", 1); 

   /*glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
   glm::mat4 trans = glm::mat4(1.0f);
   trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
   vec = trans * vec;
   std::cout << vec.x << vec.y << vec.z << std::endl;*/

   /*glm::mat4 trans = glm::mat4(1.0f);
   trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
   trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));*/

   //render loop
   //----------------------------------------
   while(!glfwWindowShouldClose(window))
   {
      // input
      processInput(window);
      
      //render
      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      //bind textures on corresponding texture units
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, texture1);
      glActiveTexture(GL_TEXTURE1);
      glBindTexture(GL_TEXTURE_2D, texture2);

      glm::mat4 transform = glm::mat4(1.0f);
      transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
      transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

      unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
      glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

      // render container
      glBindVertexArray(VAO); //not necessary here because we only have a single VAO but doing it anyway to keep things more organized
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

      transform = glm::mat4(1.0f);
      transform = glm::translate(transform, glm::vec3(-0.5f, 0.5f, 0.0f));
      float scaleAmount = sin(glfwGetTime());
      transform = glm::scale(transform, glm::vec3(scaleAmount, scaleAmount, scaleAmount));
      glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &transform[0][0]);

      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
      //glBindVertexArray(0); //no need to unbind it every time
      

      //glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
      //------------------------------------------
      glfwSwapBuffers(window);
      glfwPollEvents();
   }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

   //glfw: terminate, clearing all previously allocated GLFW resources
   //---------------------------------------------------
   glfwTerminate();

   return 0;
}

//called every loop to check whether ESC is pressed. If that's the case the window closes
void processInput(GLFWwindow *window)
{
   if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(window,true);
}

//checks whether the window has changed size to adjust the viewport too
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
   glViewport(0,0, width, height);
}
