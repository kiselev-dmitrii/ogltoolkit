#include "StreamUtils.h"

std::ostream &StreamUtils::operator<<(std::ostream &stream, const glm::vec2 &vec) {
        stream << "(" << vec.x << ", " << vec.y << ")";
        return stream;
}

std::ostream &StreamUtils::operator<<(std::ostream &stream, const glm::vec3 &vec) {
        stream << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
        return stream;
}

std::ostream &StreamUtils::operator<<(std::ostream &stream, const glm::vec4 &vec) {
        stream << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
        return stream;
}

std::ostream &StreamUtils::operator<<(std::ostream &stream, const glm::mat3 &mat) {
        stream << endl;
        stream << "|" << mat[0][0] << " " << mat[0][1] << " " << mat[0][2] << "|" << endl;
        stream << "|" << mat[1][0] << " " << mat[1][1] << " " << mat[1][2] << "|" << endl;
        stream << "|" << mat[2][0] << " " << mat[2][1] << " " << mat[2][2] << "|" << endl;
        return stream;
}

std::ostream &StreamUtils::operator<<(std::ostream &stream, const glm::mat4 &mat) {
        stream << endl;
        stream << "|" << mat[0][0] << " " << mat[0][1] << " " << mat[0][2] << " " << mat[0][3] << "|" << endl;
        stream << "|" << mat[1][0] << " " << mat[1][1] << " " << mat[1][2] << " " << mat[1][3] << "|" << endl;
        stream << "|" << mat[2][0] << " " << mat[2][1] << " " << mat[2][2] << " " << mat[2][3] << "|" << endl;
        stream << "|" << mat[3][0] << " " << mat[3][1] << " " << mat[3][2] << " " << mat[3][3] << "|" << endl;
        return stream;
}

std::ostream &StreamUtils::operator<<(std::ostream &stream, const glm::quat &q) {
        stream << "(" << q[0] << ", " << q[1] << ", " << q[2] << ", " << q[3] << ")";
        return stream;
}
