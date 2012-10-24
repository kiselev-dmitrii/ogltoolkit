#ifndef STREAMUTILS_H
#define STREAMUTILS_H

#include <iostream>
#include <glm/glm.hpp>

/** Наборы функций и операторов для удобного ввода-вывода
  */
namespace StreamUtils {
        std::ostream &operator<<(std::ostream &stream, const glm::vec2 &vec);
        std::ostream &operator<<(std::ostream &stream, const glm::vec3 &vec);
        std::ostream &operator<<(std::ostream &stream, const glm::vec4 &vec);
        std::ostream &operator<<(std::ostream &stream, const glm::mat3 &mat);
        std::ostream &operator<<(std::ostream &stream, const glm::mat4 &mat);
}

#endif // STREAMUTILS_H
