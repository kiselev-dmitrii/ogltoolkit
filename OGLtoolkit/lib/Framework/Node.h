#ifndef NODE_H
#define NODE_H

#include <map>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

using std::string;
using std::map;
using glm::vec3;
using glm::quat;

using namespace glm;
using namespace std;

typedef map<string, Node*> NodeMap;

/** Класс представляющий собой систему координат.
  * Нужен для управления движением объектов.
  * Множество различных Node можно организовывать в иерархии.
  * Node можно привязать к объекту типа Movable, для управления этим объектом.
  */
class Node {
        Node*           m_parentNode;           //указатель на родительский узел
        NodeMap         m_childNodes;           //дочерние узлы (String->Node)
        string          m_name;                 //имя узла, используется в поиске по дереву

        vec3            m_position;             //позиция в родительской СК
        quat            m_orientation;          //ориентация СК относительно родительской
        vec3            m_scale;                //масштаб в родительской СК

        mat4            m_localToParent;        //матрица перехода от локальной к родительской СК
        bool            m_isNeedToUpdate;       //определяет, нужно ли обновлять матрицы?

private:
        // Конструирует узел с именем name
        Node(const string& name);
        // Удаляет узел, со всеми дочерними узлами
        ~Node();

        // Возвращает имя узла
        string& name() const;

        // Возвращает родительский узел
        Node*   parentNode() const;
        // Устанавливает родительский узел
        void    setParentNode(Node* parent);

        // Возвращает дочернюю ноду по имени
        Node*   childNode(const string& name) const;
        // Добавляет уже созданную ноду как дочернюю к данной СК
        void    addNode(Node* child);
        // Удаляет ноду
        void    removeNode(Node* child);


        // Устанавливает позицию в родительской/мировой СК
        void    setPositionInParent(const vec3& position);
        void    setPositionInWorld(const vec3& position);

        // Устанавливает ориентацию в родительской/мировой СК
        void    setOrientationInParent(const quat& orientation);
        void    setOrientationInWorld(const quat& orientation);

        // Перемещает в родительской/локальной/мировой СК
        void    translateInParent(const vec3& delta);
        void    translateInLocal(const vec3& delta);
        void    translateInWorld(const vec3& delta);
        // Вращает в родительской/локальной/мировой СК по кватерниону
        void    rotateInParent(const quat& quaternion);
        void    rotateInLocal(const quat& quaternion);
        void    rotateInWorld(const quat& quaternion);


        // Возвращает матрицу, столбцы которой содержат оси координат локальной СК
        mat3    localAxes();

        // Возвращает указатель на матрицу перехода от локальной СК в родительскую/мировую
        mat4*   fromLocalToWorld();
        mat4*   fromLocalToParent();

        // Возвращает указатель на матрицу перехода от мировой/родительской СК в локальную
        mat4*   fromWorldToLocal();
        mat4*   fromParentToLocal();
};

#endif // NODE_H
