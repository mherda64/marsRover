#ifndef MARSROVER_MODEL_H
#define MARSROVER_MODEL_H


#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Shader.h"
#include "Mesh.h"



class Model {
public:
    Model(char* path);

    void draw(Shader &shader);

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