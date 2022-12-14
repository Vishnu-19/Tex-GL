#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"


#include<cmath>

using namespace glm;
using namespace std;
#include<vector>
// Function for intializing window

GLfloat lineVertices[10] ;

  unsigned int VBO1, VAO1, EBO1;  

void windowIntializeConfig(){
    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

}


vec3 temp1 = vec3(1.0f,0.0f,0.0f);
glm::mat4 view = glm::mat4(1.0f);
float x,y,z;
float theta1=0.0f;
float theta2=0.0f;
int tx=0;
float phi1=0.0f;
float phi2=0.0f;
const float radius = 3.0f;
float camX = sin(theta1) *radius ;
float camZ = cos(theta1) *radius;
float camX1= sin(theta2) *radius ;
float camZ1 = cos(theta2) *radius;
float camY =sin(theta1) *radius ;
float camY1 = sin(theta2) *radius ;
float temp=0.0f;
float tempy=0.0f;

glm::vec3 specularColor=vec3(1.0f,1.0f,1.0f);
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
  
       if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
            tx=1;
        
        if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
            tx=0;
        if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
           { specularColor= vec3(	0.992157f,0.941176f,0.807843f);
           }
        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
           { specularColor= vec3(0.393548f,0.271906f,	0.166721f);
           }
        if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
           { specularColor= vec3(0.774597f,0.774597f,0.774597f);
           }
          if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
           { specularColor= vec3(	0.256777f,	0.137622f,		0.086014f);
           }
           if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
           { specularColor= vec3(0.628281f,	0.555802f,	0.366065f);
           } 


    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            
            
           phi1+=0.01;
            camY = sin(phi1) * radius;
            camZ = cos(phi1)  * radius;
            camX=0.0f;
            
      
            
        }
       
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        
            
            phi1-=0.01;
            camY = sin(phi1) * radius;
            camZ = cos(phi1)  * radius;
            camX=0.0f;
        
         
           
        
        }    
       
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
       { 
        
      
         theta1-=0.01;
            camX = sin(theta1) * radius;
            camZ = cos(theta1)  * radius;
            camY=0.0f;
      
        
      
       }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)

         {
            
           

            theta1+=0.01;
            camX = sin(theta1) *radius;
            camZ = cos(theta1)  * radius;
            camY=0.0f;
            
         }
    
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        {
            
            
            phi2+=0.01;
            camY1 = sin(phi2) * radius;
            camZ1 = cos(phi2)  * radius;
            camX1=0.0f;
            
      
            
        }
       
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        
            
            phi2-=0.01;
            camY1 = sin(phi2) * radius;
            camZ1 = cos(phi2)  * radius;
            camX1=0.0f;
        
         
           
        
        }    
       
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
       { 
        
      
         theta2-=0.01;
            camX1 = sin(theta2) * radius;
            camZ1 = cos(theta2)  * radius;
            camY1=0.0f;
      
        
      
       }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)

         {
            
           

            theta2+=0.01;
            camX1 = sin(theta2) *radius;
            camZ1 = cos(theta2)  * radius;
            camY1=0.0f;
            
         }
       
    
    
}

void framebuffer_size(GLFWwindow* window, int width, int height)
{

    glViewport(0, 0, width, height);
}

//Shaders

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 COD;\n"
    "layout (location = 1) in vec2 uv;\n"
    "layout (location = 2) in vec3 normal;\n"
    "out vec3 COD1;\n"
    "out vec3 FragPos;\n"
    "out vec3 Normal;\n"

    "out vec2 fragUV;\n"
    "uniform mat4 view;\n"
    "uniform mat4 projection;\n"
    "void main()\n"
    "{\n"
    "FragPos =COD;\n"
    "Normal = normalize(normal);\n"
    "fragUV=uv;\n"
    "   gl_Position = projection*view*vec4(COD, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "precision mediump float;\n"
    "out vec4 outColor;\n"
    "uniform vec3 lightPos;\n"
    "uniform vec3 lightColor;\n"
    "uniform vec3 viewPos;\n"
    "uniform vec3 specularColor;\n"
    "uniform sampler2D tex; \n"
    "in vec2 fragUV;\n"
    "in vec3 Normal;\n"  
    "in vec3 FragPos; \n"
    "void main()\n"
    "{\n"
    "   vec4 materialColor = texture(tex, fragUV);\n"

    //ambient
    "float ambientStrength = 0.1f;\n"
    "vec4 ambient = vec4(ambientStrength * specularColor, 1.0);\n"
  	
    // diffuse 
    "vec3 norm = normalize(Normal);\n"
    "vec3 lightDir = normalize(lightPos - FragPos);\n"
    "float diff = max(dot(norm, lightDir), 0.0);\n"
    "vec4 diffuse = (diff) * materialColor;\n"
    
    //specular
   
    "vec3 viewDir = normalize(viewPos - FragPos);\n"
    "vec3 halfwayDir = normalize(lightDir + viewDir); \n"
    " float spec = pow(max(dot(norm, halfwayDir), 0.0), 10.0);\n"
    "vec4 specular = vec4(spec*specularColor, 1.0); \n"

    "vec4 result = (ambient + diffuse +specular) ;\n"
    "outColor =result;\n"
    "}\n\0";




int main()
{



    windowIntializeConfig();

    //Window creation
    GLFWwindow* window = glfwCreateWindow(800, 800, "Assignment-4", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size);


    if (glewInit() != GLEW_OK)
    { 
        std :: cout << "Failed to initialize GLEW" << std :: endl; 
        return -1;
     }



   
    // Compiling Shaders

    unsigned int vtxShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vtxShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vtxShader);
 
    int success;
    char log[512];
    glGetShaderiv(vtxShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vtxShader, 512, NULL, log);
        std::cout << "vertex shader compilation failed\n" << log << std::endl;
    }
 
    unsigned int fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragShader);
  
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragShader, 512, NULL, log);
        std::cout << "frag shader compilation failed\n" << log << std::endl;
    }
    // Linking Shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vtxShader);
    glAttachShader(shaderProgram, fragShader);
    glLinkProgram(shaderProgram);
  
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, log);
        std::cout << "Shader Link Failed\n" << log << std::endl;
    }
    glDeleteShader(vtxShader);
    glDeleteShader(fragShader);



   

    vector<float> vertices1;
    vector<float>vertices2;
    vector<float>vertices3;
    vector<float>normals;
    vector<float>vertices5;
    
   
    int stacks = 20;
    int slices = 20;
    const float pi = 3.14f;
    float theta1 = 0;
    float phi =0;
    vector<float> vertices;
    vector<float> Tvertices;
    vector<GLuint> indices;

    for (int i = 0; i <= stacks; ++i)
    {
        float V = (float)i / (float)stacks;
        float phi = V * pi;

        // loop through the slices.
        for (int j = 0; j <= slices; ++j)
        {
            float U = (float)j / (float)slices;
            float theta = U * (pi * 2);

            // use spherical coordinates to calculate the vertices.
            float x = cos(theta) * sin(phi);
            float y = cos(phi);
            float z = sin(theta) * sin(phi);
           
           
           
            vertices.push_back(x*0.5);
            vertices.push_back(y*0.5);
            vertices.push_back(z*0.5);
          
            Tvertices.push_back(1-(theta/(2*pi)));
            Tvertices.push_back(phi/pi);
            
            normals.push_back(x);
            normals.push_back(y);
            normals.push_back(z);
            
            

        }
    }
    
    
    for (int i = 0; i < slices * stacks + slices; ++i){
        indices.push_back(GLuint(i));
        indices.push_back(GLuint(i + slices + 1));
        indices.push_back(GLuint(i + slices));

        indices.push_back(GLuint(i + slices + 1));
        indices.push_back(GLuint(i));
        indices.push_back(GLuint(i + 1));
    }





    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*vertices.size(), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*indices.size(), indices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
    unsigned int VBO_texture; 
    glGenBuffers(1, &VBO_texture); 
     glBindBuffer(GL_ARRAY_BUFFER, VBO_texture); 
    glBufferData(GL_ARRAY_BUFFER, 9*Tvertices.size(), Tvertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0); 
    glEnableVertexAttribArray(1);
    unsigned int VBO_normal; 
    glGenBuffers(1, &VBO_normal); 
     glBindBuffer(GL_ARRAY_BUFFER, VBO_normal); 
    glBufferData(GL_ARRAY_BUFFER, 9*normals.size(), normals.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),  (void*)(0 * sizeof(float))); 
    glEnableVertexAttribArray(2);
    
   
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 
    

  

    unsigned int texture;
glGenTextures(1, &texture);
glBindTexture(GL_TEXTURE_2D, texture);

glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


int width, height, nrChannels;
stbi_set_flip_vertically_on_load(false);

unsigned char *data = stbi_load("earth.jpg", &width, &height, &nrChannels, 0);
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



 

   
glEnable(GL_DEPTH_TEST); 
    while (!glfwWindowShouldClose(window))
    {





        processInput(window);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
        glUseProgram(shaderProgram);
      glActiveTexture(GL_TEXTURE0); // Texture unit 0
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(glGetUniformLocation(shaderProgram, "tex"), 0);


       view = glm::lookAt(glm::vec3(camX, camY, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
        glm::mat4 projectionMatrix = mat4(1.0f);
        projectionMatrix =glm::perspective(glm::radians(45.0f),1.0f,0.1f,100.0f);
        glm :: vec3 viewpos = vec3(camX, camY, camZ);
        glm :: vec3 lightPos= vec3(camX1, camY1, camZ1);
        glm :: vec3 lightColor=vec3(1.0f, 1.0f, 1.0f);
       
         unsigned int lytLoc= glGetUniformLocation(shaderProgram, "lightPos");
        glUniform3fv(lytLoc, 1, glm::value_ptr(lightPos));
        unsigned int lytColorLoc= glGetUniformLocation(shaderProgram, "lightColor");
        glUniform3fv(lytColorLoc, 1, glm::value_ptr(lightColor));
        unsigned int viewPosLoc= glGetUniformLocation(shaderProgram, "viewPos");
        glUniform3fv(viewPosLoc, 1, glm::value_ptr(viewpos));
        unsigned int specLoc= glGetUniformLocation(shaderProgram, "specularColor");
        glUniform3fv(specLoc, 1, glm::value_ptr(specularColor));
        unsigned int viewLoc= glGetUniformLocation(shaderProgram, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        unsigned int projLoc= glGetUniformLocation(shaderProgram, "projection");
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
        glBindVertexArray(VAO); 
        glDrawElements(GL_TRIANGLES, 9*vertices.size() , GL_UNSIGNED_INT, 0);
        tx==1?glPolygonMode(GL_FRONT_AND_BACK, GL_LINE):glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        glPointSize(20);
        
       
      
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);


    glfwTerminate();
    return 0;
}

