#include "Debug.h"

std::ostream &operator<<(std::ostream &stream, glm::vec2 vector) {
        stream << "(" << vector.x << "," << vector.y << ")";
        return stream;
}

std::ostream &operator<<(std::ostream &stream, glm::vec3 vector) {
        stream << "(" << vector.x << "," << vector.y << "," << vector.z << ")";
        return stream;
}
