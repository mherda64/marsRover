//
// Created by musiek on 07.06.2021.
//

#include "Terrain.h"

Terrain::Terrain(const vec3 &position, const vec3 &rotation, const vec3 &color, const vec3 &lightColor,
                 string path, float radius) : StaticObject(position, rotation, color, lightColor, path,
                                                                         radius) {
    minVec = model.getMinVec("Plane");
    maxVec = model.getMaxVec("Plane");

    heightMap = new HeightMap("./resources/heightmap.ppm", minVec, maxVec);
}

//void Terrain::draw(Shader &shader) {
//    model.draw(shader);
//}

void Terrain::draw(Shader &shader) {
    StaticObject::draw(shader);
}

HeightMap *Terrain::getHeightMap() {
    return heightMap;
}

Terrain::~Terrain() {
    delete heightMap;
}
