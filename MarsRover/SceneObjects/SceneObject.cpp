//
// Created by musiek on 4/16/21.
//

#include "SceneObject.h"

SceneObject::SceneObject(GLdouble x, GLdouble y, GLdouble z, GLdouble xRot, GLdouble yRot, GLdouble zRot)
                                                                                                    : position(x, y, z),
                                                                                                      rotation(xRot, yRot, zRot) {}

SceneObject::SceneObject(const Point &position, const Rotation &rotation) : position(position), rotation(rotation) {}
