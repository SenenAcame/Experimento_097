//#include "GLgEngine.hpp"
//
//const *vertexShaderSource = "#version 330 core\n"
//    "layout (location = 0) in vec3 aPos;\n"
//    "void main()\n"
//    "{\n"
//    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//    "}\0";
//
//const *fragmentShaderSource = "#version 330 core\n"
//    "out vec4 FragColor;\n"
//    "void main()\n"
//    "{\n"
//    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//    "}\0";
//
//int main(){
//    //_________GLFW INIT_____________
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//    #ifdef __APPLE__
//        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//    #endif
//
//    //______CREATE GLFW WINDOW__________
//    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGl", NULL, NULL);
//    if(window == NULL) throw std::runtime_error("GLFW Error creating Window");
//    glfwMakeContextCurrent(window);
//    glfwSetFramebufferSizeCallBack(window, framebuffer_size_callback);
//    
//    //______Initializate GLAD__________
//    if(!gladLoaderGLLoader(GLADloadproc)glfwGetProcAdress) throw std::runtime_error("Failed to initializate GLAD");
//    
//    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
//    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//    glCompileShader(vertexShader);
//    //check for shader compile errors
//    int success;
//    char infoLog[512];
//    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//    if(!success){
//        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
//        throw std::runtime_error("ERROR::SHADER::VERTEX::COMPILATION::FAILED\n");
//    }
//
//    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//    glCompileShader(fragmentShader);
//    //check for shader compile errors
//    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
//    if(!success){
//        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
//        throw std::runtime_error("ERROR::SHADER::FRAGMENT::COMPILATION::FAILED\n");
//    }
//
//    unsigned int shaderProgram = glCreateProgram();
//    glAttachShader(shaderProgram, vertexShader);
//    glAttachShader(shaderProgram, fragmentShader);
//    glLinkProgram(shaderProgram);
//    //check for linking errors
//    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
//    if(!success){
//        glGetProgramInfoLog(fragmentShader, 512, NULL, infoLog);
//        throw std::runtime_error("ERROR::SHADER::PROGRAM::LINKING::FAILED\n");
//    }
//    glDeleteShader(vertexShader);
//    glDeleteShader(fragmentShader);
//
//    //set up vertex data (and buffers) and configure vertex attributes
//    
//    float vertices[] = {
//        0.5f,  0.5f, 0.0f,
//        0.5f, -0.5f, 0.0f,
//       -0.5f,  0.5f, 0.0f,
//       -0.5f, -0.5f, 0.0f
//    };
//    unsigned int indices[] = {
//        0, 1, 2,
//        1, 2, 3
//    };
//    unsigned int VBO, VAO, EBO;
//    glGenVertexArrays(1, &VAO);
//    glGenBuffers(1, &VBO);
//    glGenBuffers(1, &EBO);
//    //bind the vertex Array objecs
//    glBindVertexArray(VAO);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    //DO not ubind the EBO while a VAO is active
//    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//
//
//    glBindVertexArray(0);
//
//    //uncomment this to draw in wireframe polygons
//    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//
//    //__________ViewPort______________
//    //glViewport(0, 0, 800, 600);
//
//    //void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//    //glfwSetFramebufferSizeCallBack(window, framebuffer_size_callback);
//
//    while(!glfwWindowShouldClose(window)){
//        //ESCAPE INPUT
//        processInput(window);
//
//        //RENDERING COMMANDS
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        //draw triangle
//        glUseProgram(shaderProgram);
//        glBindVertexArray(VAO);
//
//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//        //Check and call events and swap buffers
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    glDeleteVertexArrays(1, &VAO);
//    glDeleteBuffers(1, &VBO);
//    glDeleteBuffers(1, &EBO);
//    glDeleteProgram(shaderProgram);
//
//    glfwTerminate();
//    return 0;
//}
//
//void processInput(GLFWwindow* window){
//    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
//        glfwSetWindowShouldClose(window, true);
//    }
//}
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height){
//    glViewport(0,0,width, height);
//}