#include "Entity.h"
#include "lib/Utils/Debug.h"

Entity::Entity(MeshInfo *meshInfo) : Movable() {
        m_meshInfo = meshInfo;
}

MeshInfo* Entity::meshInfo() const {
        return m_meshInfo;
}
