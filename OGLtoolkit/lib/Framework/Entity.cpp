#include "Entity.h"
#include "lib/Utils/Debug.h"

Entity::Entity(VertexArray *vertexArray) : Movable() {
        m_vertexArray = vertexArray;
}

VertexArray* Entity::vertexArray() const {
        return m_vertexArray;
}
