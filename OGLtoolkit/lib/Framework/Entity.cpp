#include "Entity.h"
#include "lib/Debug/Debug.h"

void Entity::init() {
        m_position = vec3(0);
        m_orientation = vec3(0);
        m_scale = vec3(1);
        m_pivot = vec3(0);

        m_isModelMatrixChanged = true;
}

Entity::Entity() {
        init();
}

Entity::Entity(const string &filename) {
        init();
        setMesh(filename);
}

void Entity::updateBuffers() {
        // Проверил, можно использовать uploadData
        m_vbo.uploadData(m_mesh.vertices(), m_mesh.verticesSize(), Hint::STATIC_DRAW);
        m_ibo.uploadData(m_mesh.indices(), m_mesh.indicesSize(), Hint::STATIC_DRAW);
}

void Entity::updateInterpretation() {
        m_vao.bind();
                m_vbo.setAttribAssociation("vertexPosition", 3, GL_FLOAT, 0, sizeof(Vertex));
                m_vbo.setAttribAssociation("vertexNormal", 3, GL_FLOAT, sizeof(vec3), sizeof(Vertex));
                m_vbo.setAttribAssociation("vertexTexCoord", 2, GL_FLOAT, 2*sizeof(vec3), sizeof(Vertex));

                m_ibo.bind();
        m_vao.unbind();
}

void Entity::setMesh(const Mesh &mesh) {
        TRACE("Возможно в Mesh нужен свой оператор присваивания, т.к память заного не выделится");
        m_mesh = mesh;
        updateBuffers();
        updateInterpretation();
}

void Entity::setMesh(const string &filename) {
        m_mesh.loadMeshFromFile(filename);
        updateBuffers();
        updateInterpretation();
}

Mesh* Entity::mesh() {
        return &m_mesh;
}

void Entity::setPosition(const vec3 &pos) {
        m_position = pos;
        m_isModelMatrixChanged = true;
}

void Entity::setOrientation(const vec3 &angles) {
        m_orientation = angles;
        m_isModelMatrixChanged = true;
}

void Entity::setScale(const vec3 &scales) {
        m_scale = scales;
        m_isModelMatrixChanged = true;
}

void Entity::setPivot(const vec3 &coord) {
        m_pivot = coord;
        m_isModelMatrixChanged = true;
}

void Entity::move(const vec3 &delta) {
        m_position += delta;
        m_isModelMatrixChanged = true;
}

void Entity::rotate(const vec3 &delta) {
        m_orientation += delta;
        m_isModelMatrixChanged = true;
}

void Entity::stretch(const vec3 &delta) {
        m_scale += delta;
        m_isModelMatrixChanged = true;
}

vec3 Entity::position() { return m_position; }

vec3 Entity::orientation() { return m_orientation; }

vec3 Entity::scale() { return m_scale; }

vec3 Entity::pivot() { return m_pivot; }

mat4* Entity::modelMatrix() {
        //TRACE("Возможно нужно брать m_pivot, вместо -m_pivot");
        // Заметим, что порядок умножений должен быть обратный
        // ModelMatrix = E*Pos*Scale*Orient*Pivot*v
        // Сначала мы переносим в лок. сис-му координат, затем поворачиваем
        // Затем устанавливаем позицию
        if(m_isModelMatrixChanged) {
                m_modelMatrix = glm::translate(mat4(1), m_position);
                m_modelMatrix = glm::scale(m_modelMatrix, m_scale);
                m_modelMatrix = glm::rotate(m_modelMatrix, m_orientation.x, vec3(1,0,0));
                m_modelMatrix = glm::rotate(m_modelMatrix, m_orientation.y, vec3(0,1,0));
                m_modelMatrix = glm::rotate(m_modelMatrix, m_orientation.z, vec3(0,0,1));
                m_modelMatrix = glm::translate(m_modelMatrix, -m_pivot);

                m_isModelMatrixChanged = false;
        }

        return &m_modelMatrix;
}

VertexArray* Entity::vertexArray() {
        return &m_vao;
}
