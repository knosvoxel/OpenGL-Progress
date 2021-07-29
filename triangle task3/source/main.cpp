#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

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

//vertex shader code to compile later in the code
const char *vertexShaderSource = "#version 330 core\n"
   "layout (location = 0) in vec3 aPos;\n"
   "void main()\n"
   "{\n"
   " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
   "}\0";

//fragment shader code to compile later in the code
const char *fragmentShaderSource = "#version 330 core\n"
   "out vec4 FragColor;\n"
   "void main()\n"
   "{\n"
   " FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
   "}\0";

const char *fragmentShaderYellowSource = "#version 330 core\n"
   "out vec4 FragColor;\n"
   "void main()\n"
   "{\n"
   " FragColor = vec4(1.0f, 1.0f, 0.2f, 1.0f);\n"
   "}\0";

int main()
{
   //glfw: initialize and configure
   glfwInit();
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

   //glfw window creation
   GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr,nullptr);
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

   // building and compiling the shader program
   //------------------------------------------
   // vertexShader compilation
   unsigned int vertexShader;
   vertexShader = glCreateShader(GL_VERTEX_SHADER);
   glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
   glCompileShader(vertexShader);
   // check for shader compile errors
   int success;
   char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

   // fragment shader compilation
   unsigned int fragmentShader;
   fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
   glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
   glCompileShader(fragmentShader);
   // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

   // fragment shader yellow compilation
   unsigned int fragmentShaderYellow;
   fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
   glShaderSource(fragmentShaderYellow, 1, &fragmentShaderYellowSource, NULL);
   glCompileShader(fragmentShaderYellow);
   // check for shader compile errors
    glGetShaderiv(fragmentShaderYellow, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShaderYellow, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

   //link shaders
   unsigned int shaderProgram{glCreateProgram()};
   unsigned int shaderProgramYellow{glCreateProgram()};
   glAttachShader(shaderProgram, vertexShader);
   glAttachShader(shaderProgram, fragmentShader);
   glLinkProgram(shaderProgram);
   glAttachShader(shaderProgramYellow, vertexShader);
   glAttachShader(shaderProgramYellow, fragmentShaderYellow);
   glLinkProgram(shaderProgramYellow);
   //check for linking errors
   glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
   if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
   }
   glDeleteShader(vertexShader);
   glDeleteShader(fragmentShader);
   glDeleteShader(fragmentShaderYellow);

   //set up vertex data (and buffer(s)) and configure vertex attributes
   //-----------------------------------------------------------------
         float firstTriangle[] = {
        -0.9f, -0.5f, 0.0f,  // left 
        -0.0f, -0.5f, 0.0f,  // right
        -0.45f, 0.5f, 0.0f,  // top 
    };
    float secondTriangle[] = {
        0.0f, -0.5f, 0.0f,  // left
        0.9f, -0.5f, 0.0f,  // right
        0.45f, 0.5f, 0.0f   // top 
    };

   unsigned int VBOs[2], VAOs[2];
   glGenVertexArrays(2, VAOs);
   glGenBuffers(2, VBOs);
   //bind the Vertes Arrays Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
   glBindVertexArray(VAOs[0]);

   glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
   glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);

   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
   glEnableVertexAttribArray(0);

    glBindVertexArray(VAOs[1]);

   glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
   glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);

   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
   glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer
    // registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
   glBindBuffer(GL_ARRAY_BUFFER, 0);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
   glBindVertexArray(0);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

   //render loop
   //----------------------------------------
   while(!glfwWindowShouldClose(window))
   {
      // input
      processInput(window);
      
      //render
      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      //draws the triangle
      glUseProgram(shaderProgram);
      glBindVertexArray(VAOs[0]); //not necessary here because we only have a single VAO but doing it anyway to keep things more organized
      glDrawArrays(GL_TRIANGLES, 0, 3);
      //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
      //glBindVertexArray(0); //no need to unbind it every time
      
      glUseProgram(shaderProgramYellow);
      glBindVertexArray(VAOs[1]); //not necessary here because we only have a single VAO but doing it anyway to keep things more organized
      glDrawArrays(GL_TRIANGLES, 0, 3);


      //glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
      //------------------------------------------
      glfwSwapBuffers(window);
      glfwPollEvents();
   }

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
