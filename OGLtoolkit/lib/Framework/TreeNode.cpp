#include "TreeNode.h"
#include "lib/Utils/StringUtils.h"

int TreeNode::m_nodeCounter = 0;

TreeNode::TreeNode(const string &nodeName) {
        ++m_nodeCounter;

        m_nodeName = nodeName;
        m_parentNode = NULL;
}

TreeNode::TreeNode() {
        ++m_nodeCounter;

        m_nodeName = "Unknown_" + StringUtils::numToStr(m_nodeCounter);
        m_parentNode = NULL;
}

TreeNode::~TreeNode() {
        if (m_parentNode) m_parentNode->removeChildNode(this);
        removeAllChild();
}

void TreeNode::setParentNode(TreeNode *parent) {
        m_parentNode = parent;
        if (parent!=NULL) m_parentNode->addChildNode(this);
}

TreeNode* TreeNode::parentNode() const {
        return m_parentNode;
}

void TreeNode::addChildNode(TreeNode *child) {
        m_childNodes.insert(std::pair<child->m_name, child>);
        if (child->m_parentNode!=this) child->setParentNode(this);
}

void TreeNode::removeChildNode(TreeNode *child) {
        if (child==NULL) return;

        m_childNodes.erase(child->m_nodeName);
        child->m_parentNode = NULL;
}

void TreeNode::removeChildNode(const string &name) {
        TreeNode* child = childNode(name);
        removeChildNode(child);
}

void TreeNode::removeAllChild() {
        // Устанавливаем родителя дочерних узлов в NULL
        NodeMap::iterator it;
        for (it=m_childNodes.begin(); it!=m_childNodes.end(); ++it) {
                TreeNode* child = it->second;
                child->m_parentNode = NULL;
        }

        //Удаляем все дочерние узлы
        m_childNodes.erase(m_childNodes.begin(), m_childNodes.end());
}

TreeNode* TreeNode::childNode(const string &name) {
        NodeMap::iterator it = m_childNodes.find(name);

        if (it==m_childNodes.end()) {
                return NULL;
        } else {
                return it->second;
        }
}

TreeNode* TreeNode::findChildNode(const string &name) {
        TreeNode* child = childNode(name);

        // Если не нашли на первом уровне, рекурсивно ищем
        if (child==NULL) {
                NodeMap::iterator it;
                for(it=m_childNodes.begin(); it!=m_childNodes.end(); ++it) {
                        TreeNode* child = it->second;
                        return child->findChildNode(name);
                }
                // Выполнится, только если список нодов пуст
                return NULL;
        } else {
                return child;
        }
}
