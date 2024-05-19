#pragma once

#include <cstddef>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "../VertexIndex/VertexIndex.hpp"
#include "../VertexBuffer/VertexBuffer.hpp"

class Mesh {
    std::vector<GLfloat> vbo_data;
    std::vector<GLuint> vio_data;
    VertexBuffer *vbo;
    VertexIndex *vio;
    size_t size;

  public:
    Mesh(const std::string &path) {
        std::ifstream file(path);
        if (!file.is_open()) {
            throw std::logic_error("Couldn't open the file");
        }
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string arg;
            ss >> arg;
            if (arg == "v") {
                ss >> arg;
                vbo_data.push_back(std::stof(arg));
                ss >> arg;
                vbo_data.push_back(std::stof(arg));
                ss >> arg;
                vbo_data.push_back(std::stof(arg));
            } else if (arg == "f") {
                ss >> arg;
                auto bad = arg.find('/');
                if (bad != -1) {
                    arg.resize(bad);
                }
                vio_data.push_back(std::abs(std::stoi(arg)) - 1);
                ss >> arg;
                bad = arg.find('/');
                if (bad != -1) {
                    arg.resize(bad);
                }
                vio_data.push_back(std::abs(std::stoi(arg)) - 1);
                ss >> arg;
                bad = arg.find('/');
                if (bad != -1) {
                    arg.resize(bad);
                }
                vio_data.push_back(std::abs(std::stoi(arg)) - 1);
                ++size;
            }
        }
        vbo = new VertexBuffer(vbo_data.data(),
                               vbo_data.size() * sizeof(GLfloat));
        vio = new VertexIndex(vio_data.data(), vio_data.size(),
                              sizeof(vio_data[0]));
        file.close();
    }
    VertexBuffer &GetVBO() { return *vbo; }
    VertexIndex &GetVIO() { return *vio; }
    size_t getMeshSize() { return vio_data.size(); }
    ~Mesh() {
        delete vbo;
        delete vio;
    }
};