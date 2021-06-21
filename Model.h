#ifndef MARSROVER_MODEL_H
#define MARSROVER_MODEL_H


#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Shader.h"
#include "Mesh.h"

class Model {
public:
    Model(string path);

    virtual void draw(Shader &shader);

    glm::vec3 getLeftMiddleWheelOrigin();
    glm::vec3 getRightMiddleWheelOrigin();

    glm::vec3 getOrigin(string name);

    glm::vec3 getMinVec(string meshName);
    glm::vec3 getMaxVec(string meshName);

private:
    vector<Mesh> meshes;
    vector<Texture> loadedTextures;
    string directory;

    void loadModel(string path);
    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);


};


#endif //MARSROVER_MODEL_H
