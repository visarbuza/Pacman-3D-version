#ifndef GHOST_H
#define GHOST_H

#include <glm/gtc/matrix_transform.hpp>

class Ghost {
  private:
    glm::vec3 position;
    glm::vec3 front;
    float velocity;
  public:
    void draw();
};

#endif