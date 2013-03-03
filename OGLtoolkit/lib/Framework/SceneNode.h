#ifndef SCENENODE_H
#define SCENENODE_H

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "TreeNode.h"

using namespace glm;
using glm::vec3;
using glm::quat;

/** Иерархические вложенные системы координат.
  * К каждому узлу можно подключить дочерний узел и т.д
  * Это также называется графом сцены.
  * Наследуется от TreeNode. Здесь часто будет применятся приведенние TreeNode* к SceneNode*
  */
class SceneNode : public TreeNode {
private:
        vec3    m_position;                     //позиция, относительно родительской СК
        quat    m_orientation;                  //ориентация, относительно родительской СК
        vec3    m_scale;                        //масштаб, относительно родительской СК

        vec3    m_positionInWorld;              //позиция, относительно мировой СК
        quat    m_orientationInWorld;           //оринетация, относительно мировой СК
        vec3    m_scaleInWorld;                 //масштаб, относительно мировой СК

        bool    m_isUpdateWorldValues;          //определяет, требуется ли обновление
        bool    m_isUpdateLocalToWorldMatrix;   //определяет, требуется ли обновление модельной матрицы

        mat4    m_localToWorldMatrix;
        mat4    m_worldToLocalMatrix;

private:
        // Инициализация начальных значений
        void    init();

        // Обновление positionInWorld и т.д
        void    updateWorldValues();

        // Сообщает данному и нижестоящим узлам, что требуется обновить мировые координаты
        // Это нужно производить при кадом изменении координат
        // Хотя это может быть неэффективно
        void    notifyNeedToUpdateWorldValues();

        // Обновляет матрицу перехода ил локальных координат в мировые
        void    updateLocalToWorldMatrix();

public:
        // Конструирует СК с именем Unknown_i
        SceneNode();
        // Конструирует СК с именем name
        SceneNode(const string& name);
        // Разрушает СК
        ~SceneNode();

        // Конвертирует вектор/кватернион из мировой СК в локальную
        vec3            convertWorldToLocal(const vec3& worldVec);
        quat            convertWorldToLocal(const quat& worldQuat);
        // Конвертирует вектор/кватернион из локальной СК в мировую
        vec3            convertLocalToWorld(const vec3& localVec);
        quat            convertLocalToWorld(const quat& localQuat);

        // Устанавливает позицию/ориентацию/масштаб в родительской СК
        void            setPositionInParent(const vec3& position);
        void            setOrientationInParent(const quat& orientation);
        void            setScaleInParent(const vec3& scale);

        // Возвращает позицию/ориентацию/масштаб в родительской СК
        const vec3&     positionInParent();
        const quat&     orientationInParent();
        const vec3&     scaleInParent();

        //Устанавливает позицию/ориентацию/масштаб в мировой СК
        void            setPositionInWorld(const vec3& position);
        void            setOrientationInWorld(const quat& orientation);
        void            setScaleInWorld(const vec3& scale);

        // Возвращает позицию/ориентацию/масштаб в мировых координатах
        const vec3&     positionInWorld();
        const quat&     orientationInWorld();
        const vec3&     scaleInWorld();

        // Перемещает ноду на вектор delta
        void            translateInLocal(const vec3& delta);
        void            translateInParent(const vec3& delta);
        void            translateInWorld(const vec3& delta);

        // Вращает ноду по кватерниону quaternion
        void            rotateInLocal(const quat& quaternion);
        void            rotateInParent(const quat& quaternion);
        void            rotateInWorld(const quat& quaternion);

        // Вращает ноду по оси axis на угол angle в. Axis задана в соответствующей СК
        void            rotateInLocal(const vec3& axis, float angle);
        void            rotateInParent(const vec3& axis, float angle);
        void            rotateInWorld(const vec3& axis, float angle);

        // Устанавливает ориентацию таким образом, чтобы ось -Z была направлена в target, а Y в сторону up
        // В основном применяется в классе Camera
        void            lookAt(const vec3& target, const vec3& up);

        // Возвращает матрицу перехода из локальной СК в глобальную и обратную
        const mat4&     localToWorldMatrix();
        const mat4&     worldToLocalMatrix();

        // Пеереопределенные события при добавлении/удалении ноды
        virtual void    onAddChild();
        virtual void    onRemoveChild();
};

#endif // SCENENODE_H
