#ifndef MARSROVER_MESH_H
#define MARSROVER_MESH_H


#include <vec3.hpp>
#include <vec2.hpp>
#include <glad/glad.h>
#include "Vertex.h"
#include "Texture.h"
#include "Shader.h"

#include <string>
#include <vector>
using namespace glm;


using namespace std;


class Mesh {
public:
    string name;
    vector<Vertex> vertices;
    vector<uint> indices;
    vector<Texture> textures;

    Mesh(string name, vector<Vertex> vertices, vector<uint> indices, vector<Texture> textures);

    void draw(Shader& shader);

private:
    uint VAO, VBO, EBO;

    void setupMesh();

};


#endif //MARSROVER_MESH_H
