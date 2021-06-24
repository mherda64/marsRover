//
// Created by musiek on 07.06.2021.
//

#ifndef MARSROVER_TERRAIN_H
#define MARSROVER_TERRAIN_H


#include "Model.h"
#include "HeightMap.h"
#include "StaticObject.h"

class Terrain : public StaticObject {
public:
    glm::vec3 minVec;
    glm::vec3 maxVec;

    HeightMap* heightMap;

    Terrain(const vec3 &position, const vec3 &rotation, const vec3 &color, const vec3 &lightColor, const vec3 &scale,
            string path1, float radius);
    virtual ~Terrain();
    HeightMap* getHeightMap();

    void draw(Shader &shader) override;
};


#endif //MARSROVER_TERRAIN_H
