#include "Mesh.h"

Mesh::Mesh(string name, vector<Vertex> vertices, vector<uint> indices, vector<Texture> textures, glm::vec3 minVec, glm::vec3 maxVec) {

    this->name = name;
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
    this->minVec = minVec;
    this->maxVec = maxVec;

    setupMesh();

}

void Mesh::setupMesh() {
    // Creating buffers and vertex array object
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint), &indices[0], GL_STATIC_DRAW);

    // Vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    // Vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

    // Texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    glBindVertexArray(0);
}

void Mesh::draw(Shader &shader) {

    for (uint i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);

        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }

    glActiveTexture(GL_TEXTURE0);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

}

glm::vec3 Mesh::getOrigin() {
    return glm::vec3((minVec.x + maxVec.x) / 2, (minVec.y + maxVec.y) / 2, (minVec.z + maxVec.z) / 2);
}

const vec3 &Mesh::getMinVec() const {
    return minVec;
}

const vec3 &Mesh::getMaxVec() const {
    return maxVec;
}
