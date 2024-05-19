#include "Shader.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>

GLuint Shader::CompileShader(GLuint type, const std::string &source) {

    GLuint id = glCreateShader(type);
    const char *src_c = source.c_str();
    glShaderSource(id, 1, &src_c, nullptr);
    glCompileShader(id);

    GLint res;
    glGetShaderiv(id, GL_COMPILE_STATUS, &res);
    if (res == GL_FALSE) {
        std::cout << "_____Shader compilation failure_____" << std::endl;
        int len;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
        GLchar msg[len];
        glGetShaderInfoLog(id, len, &len, msg);
        std::cout << msg << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

std::string Shader::ReadFile(const std::string &path) {
    std::ifstream i_file(path);
    if (!i_file.is_open()) {
        throw std::logic_error("File cannot be found: " + path);
    }
    std::string retval;
    while (!i_file.eof()) {
        std::string temp;
        std::getline(i_file, temp);
        temp.push_back('\n');
        retval += temp; // it strips newlines!
    }
    i_file.close();
    return retval;
}

Shader::Shader() {
    m_ProgramID = 0;
    m_fsID = 0;
    m_vsID = 0;
    m_gsID = 0;
}

void Shader::releaseResources() { DeleteShader(); }

Shader::Shader(const std::string &pathToVS, const std::string &pathToFS)
    : Shader() {
    CreateShader(pathToVS, pathToFS);
}

void Shader::CreateShader(const std::string &pathToVS,
                          const std::string &pathToFS) {
    CreateShaderProg(ReadFile(pathToVS), ReadFile(pathToFS));
}

void Shader::CreateFragShader(const std::string &path) {
    DeleteFragShader();
    std::string source = ReadFile(path);
    m_fsID = Shader::CompileShader(GL_FRAGMENT_SHADER, source);
    if (m_vsID) {
        CreateProgram();
        Shader::LinkShaders(m_ProgramID, m_vsID, m_fsID);
    }
}

void Shader::CreateVertShader(const std::string &path) {
    DeleteVertShader();
    std::string source = ReadFile(path);
    m_vsID = Shader::CompileShader(GL_VERTEX_SHADER, source);
    if (m_fsID) {
        CreateProgram();
        Shader::LinkShaders(m_ProgramID, m_vsID, m_fsID);
    }
}

void Shader::CreateGeomShader(const std::string &path) {
    DeleteGeomShader();
    std::string source = ReadFile(path);
    m_gsID = Shader::CompileShader(GL_GEOMETRY_SHADER, source);
    if (m_fsID && m_vsID) {
        LinkShaderToProgram(m_gsID);
    }
}

void Shader::LinkShaderToProgram(GLuint shaderID) {
    glAttachShader(m_ProgramID, shaderID);
    glLinkProgram(m_ProgramID);
    GLint res;
    glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &res);
    if (res == GL_FALSE) {
        std::cout << "_____Shader linking failure_____" << std::endl;
        int len;
        glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &len);
        GLchar msg[len];
        glGetProgramInfoLog(m_ProgramID, len, &len, msg);
        std::cout << msg << std::endl;
        DeleteProgram();
        return;
    }
    glValidateProgram(m_ProgramID);
}

void Shader::DeleteGeomShader() { glDeleteShader(m_gsID); }

void Shader::CreateShaderProg(const std::string &vertexShader,
                              const std::string &fragmentShader) {
    DeleteShader();
    CreateProgram();
    m_vsID = Shader::CompileShader(GL_VERTEX_SHADER, vertexShader);
    m_fsID = Shader::CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
    Shader::LinkShaders(m_ProgramID, m_vsID, m_fsID);
}

void Shader::LinkShaders(GLuint programID, GLuint vs, GLuint fs) {
    glAttachShader(programID, vs);
    glAttachShader(programID, fs);
    glLinkProgram(programID);
    glValidateProgram(programID);
}

void Shader::Bind() { glUseProgram(m_ProgramID); }

void Shader::Unbind() { glUseProgram(0); }

void Shader::CreateProgram() {
    if (!m_ProgramID) {
        m_ProgramID = glCreateProgram();
    }
}

void Shader::DeleteFragShader() {
    glDeleteShader(m_fsID);
    m_uniformMap.clear();
    m_fsID = 0;
    DeleteProgram();
}

void Shader::DeleteVertShader() {
    glDeleteShader(m_vsID);
    m_vsID = 0;
    DeleteProgram();
}

void Shader::DeleteShader() {
    DeleteFragShader();
    DeleteVertShader();
    DeleteProgram();
}

void Shader::DeleteProgram() {
    glDeleteProgram(m_ProgramID);
    m_ProgramID = 0;
}

void Shader::SetUniform4f(const std::string &u_name, GLfloat x, GLfloat y,
                          GLfloat z, GLfloat w) {
    glUniform4f(GetUniformLocation(u_name), x, y, z, w);
}

GLint Shader::GetUniformLocation(const std::string &u_name) {
    GLint location;
    auto it = m_uniformMap.find(u_name);
    if (it == m_uniformMap.end()) {
        location = glGetUniformLocation(m_ProgramID, u_name.c_str());
        if (location != -1) {
            m_uniformMap[u_name] = location;
        }
    } else
        location = it->second;
    return location;
}

void Shader::SetUniform1i(const std::string &u_name, GLint val) {
    int loc = GetUniformLocation(u_name);
    glUniform1i(loc, val);
}

void Shader::SetUniformMat4f(const std::string &u_name,
                             const glm::mat4 &matrix) {
    Bind();
    int loc = GetUniformLocation(u_name);
    glUniformMatrix4fv(loc, 1, GL_FALSE, &matrix[0][0]);
    Unbind();
}