#ifndef TREENODE_H
#define TREENODE_H

#include <string>
#include <map>

using std::map;
using std::string;
using namespace std;

typedef map<string, TreeNode*> NodeMap;

/** Класс узла дерева. Каждый узел имеет имя
  */
class TreeNode {
protected:
        TreeNode*       m_parentNode;           //родительский узел
        NodeMap         m_childNodes;           //дочерние узлы

        string          m_nodeName;             //имя узла
        static int      m_nodeCounter;          //общее кол-во узлов которое было создано

public:
        // Создает пустую вершину без родителя c именем nodeName
        TreeNode(const string& nodeName);
        // Создает вершину с именем unknown_i
        TreeNode();
        // Разрушает данную ноду, при этом дочерние ноды становятся без родителя
        ~TreeNode();

        // Устанавливает/возвращает родителя
        void            setParentNode(TreeNode* parent);
        TreeNode*       parentNode() const;

        // Добавляет дочернюю ноду
        void            addChildNode(TreeNode* child);
        // Удаляет дочернюю ноду
        void            removeChildNode(TreeNode* child);
        void            removeChildNode(const string& name);
        // Удаляет все дочерние ноды
        void            removeAllChild();

        // Возвращает дочернюю ноду текущего узла
        TreeNode*       childNode(const string& name);
        // Ищет дочернюю ноду по всем нижележащим узлам и возвращает указатель на нее
        TreeNode*       findChildNode(const string& name);

        // Отображает поддерево (c отступом offset)
        void            show(unsigned int offset=0) const;
};

#endif // TREENODE_H
