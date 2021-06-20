#include "Model.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


uint TextureFromFile(const char *path, const string &directory, bool gamma = false);

Model::Model(string path) {
    loadModel(path);
}

void Model::draw(Shader &shader) {
    for (uint i = 0; i < meshes.size(); i++)
    {
        meshes[i].draw(shader);
    }
}

void Model::loadModel(string path) {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
        return;
    }
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
        directory = path.substr(0, path.find_last_of('\\'));
    #else
        directory = path.substr(0, path.find_last_of('/'));
    #endif


#ifdef WINDOWS
    directory = path.substr(0, path.find_last_of('\\'));
#else
    directory = path.substr(0, path.find_last_of('/'));
#endif
    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene) {
    // process all the node's meshes (if any)
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    // then do the same for each of its children
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene) {
    string name;
    vector<Vertex> vertices;
    vector<uint> indices;
    vector<Texture> textures;

    name = mesh->mName.C_Str();

    glm::vec3 min(mesh->mVertices[0].x, mesh->mVertices[0].y, mesh->mVertices[0].z);
    glm::vec3 max(mesh->mVertices[0].x, mesh->mVertices[0].y, mesh->mVertices[0].z);

    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {

        // process vertex positions, normals and texture coordinates
        glm::vec3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;

        if (vector.x < min.x) min.x = vector.x;
        if (vector.x > max.x) max.x = vector.x;
        if (vector.y < min.y) min.y = vector.y;
        if (vector.y > max.y) max.y = vector.y;
        if (vector.z < min.z) min.z = vector.z;
        if (vector.z > max.z) max.z = vector.z;

        Vertex vertex;
        vertex.Position = vector;

        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;

        if(mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex);
    }

    // process indices
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    // process material
    if(mesh->mMaterialIndex >= 0)
    {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        vector<Texture> diffuseMaps = loadMaterialTextures(material,
                                                           aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        vector<Texture> specularMaps = loadMaterialTextures(material,
                                                            aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }

    return Mesh(name, vertices, indices, textures, min, max);
}


vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName)
{
    vector<Texture> textures;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        bool skip = false;
        for(unsigned int j = 0; j < loadedTextures.size(); j++)
        {
            if(std::strcmp(loadedTextures[j].path.data(), str.C_Str()) == 0)
            {
                textures.push_back(loadedTextures[j]);
                skip = true;
                break;
            }
        }
        if(!skip)
        {   // if texture hasn't been loaded already, load it
            Texture texture;
            texture.id = TextureFromFile(str.C_Str(), directory);
            texture.type = typeName;
            texture.path = str.C_Str();
            textures.push_back(texture);
            loadedTextures.push_back(texture); // add to loaded textures
        }
    }
    return textures;
}

glm::vec3 Model::getLeftMiddleWheelOrigin() {
    for (Mesh mesh : meshes) {
        if (mesh.name == "Left_Middle_Wheel_Cylinder.001") return mesh.getOrigin();
    }
}

glm::vec3 Model::getRightMiddleWheelOrigin() {
    for (Mesh mesh : meshes) {
        if (mesh.name == "Right_Middle_Wheel_Cylinder.007") return mesh.getOrigin();
    }
}

glm::vec3 Model::getMinVec(string meshName) {
    for (Mesh mesh : meshes) {
        if (mesh.name == meshName) return mesh.getMinVec();
    }
}

glm::vec3 Model::getMaxVec(string meshName) {
    for (Mesh mesh : meshes) {
        if (mesh.name == meshName) return mesh.getMaxVec();
    }
}

uint TextureFromFile(const char *path, const string &directory, bool gamma)
{
    string filename = string(path);
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
        filename = directory + '\\' + filename;
    #else
        filename = directory + '/' + filename;
    #endif


    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}