#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include <unordered_map>
#include "../Object/Object.h"

class Shader : IObject {

    GLuint m_ProgramID;
    GLuint m_vsID;
    GLuint m_fsID;
    GLuint m_gsID;
    std::unordered_map<std::string, GLint> m_uniformMap;

    static std::string ReadFile(const std::string &path);
    static GLuint CompileShader(GLuint type, const std::string &Source);
    static void LinkShaders(GLuint programID, GLuint vs, GLuint fs);
    void CreateShaderProg(const std::string &srcVS, const std::string &srcFS);
    void CreateProgram();
    void LinkShaderToProgram(GLuint shaderID);
    virtual void releaseResources() override;

  public:
    Shader(const Shader &) = delete;
    Shader(Shader &&) = delete;
    Shader &operator=(const Shader &) = delete;
    Shader &operator=(Shader &&) = delete;

  public:
    ~Shader() { releaseResources(); }
    Shader();
    Shader(const std::string &pathToVS, const std::string &pathToFS);
    void CreateFragShader(const std::string &path);
    void DeleteFragShader();
    void CreateVertShader(const std::string &path);
    void DeleteVertShader();
    void CreateGeomShader(const std::string &path);
    void DeleteProgram();
    void DeleteGeomShader();
    void CreateShader(const std::string &pathToVS, const std::string &pathToFS);
    void DeleteShader();
    void SetUniformMat4f(const std::string &u_name, const glm::mat4 &matrix);
    void SetUniform1i(const std::string &u_name, GLint val);
    void SetUniform4f(const std::string &u_name, GLfloat x, GLfloat y,
                      GLfloat z, GLfloat w);
    GLint GetUniformLocation(const std::string &u_name);
    void Bind();
    void Unbind();

};
