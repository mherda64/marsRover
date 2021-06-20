//
// Created by musiek on 07.06.2021.
//

#include "Terrain.h"

Terrain::Terrain(string path) : model(path) {
    minVec = model.getMinVec("Plane");
    maxVec = model.getMaxVec("Plane");

    heightMap = new HeightMap("./resources/heightmap.ppm", minVec, maxVec);
}

void Terrain::draw(Shader &shader) {
    model.draw(shader);
}

HeightMap *Terrain::getHeightMap() {
    return heightMap;
}

Terrain::~Terrain() {
    delete heightMap;
}
