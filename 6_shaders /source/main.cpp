#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <learnopengl/shader_s.h>

#include <iostream>
#include <math.h>

//VBO: vertex buffer object. Can store a large number of vertices in the GPU's memory.
/*
The advantage of using those buffer objects is that we can send large batches of data 
all at once to the graphics card, and keep it there if there's enough memory left, 
without having to send data one vertex at a time. Sending data to the graphics card from 
the CPU is relatively slow, so wherever we can we try to send as much data as possible at 
once. Once the data is in the graphics card's memory the vertex shader has almost instant 
access to the vertices making it extremely fast
*/


//VAO: 
/*
A vertex array object (also known as VAO) can be bound just like a vertex buffer object and any subsequent vertex 
attribute calls from that point on will be stored inside the VAO. This has the advantage that when configuring 
vertex attribute pointers you only have to make those calls once and whenever we want to draw the object, 
we can just bind the corresponding VAO. This makes switching between different vertex data and attribute 
configurations as easy as binding a different VAO. All the state we just set is stored inside the VAO.
*/

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
   Shader ourShader("../shaders/learnopengl/3.3.shader.vs", "../shaders/learnopengl/3.3.shader.fs");

   //set up vertex data (and buffer(s)) and configure vertex attributes
   //-----------------------------------------------------------------
   float vertices[]{
      // positions       // colors
      0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,// bottom right
     -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,// bottom left
      0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,// top
   };

   unsigned int VBO, VAO;
   glGenVertexArrays(1, &VAO);
   glGenBuffers(1, &VBO);
   //bind the Vertes Arrays Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
   glBindVertexArray(VAO);

   glBindBuffer(GL_ARRAY_BUFFER, VBO);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

   // position attribute
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
   glEnableVertexAttribArray(0);

   // color atribute
   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
   glEnableVertexAttribArray(1);

    // note that this is allowed, the call to glVertexAttribPointer
    // registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

   /*int nrAttributes;
   glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
   std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
   */

   //render loop
   //----------------------------------------
   while(!glfwWindowShouldClose(window))
   {
      // input
      processInput(window);
      
      //render
      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      ourShader.use();

      //draws the triangle
      glBindVertexArray(VAO); //not necessary here because we only have a single VAO but doing it anyway to keep things more organized
      glDrawArrays(GL_TRIANGLES, 0, 3);
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
