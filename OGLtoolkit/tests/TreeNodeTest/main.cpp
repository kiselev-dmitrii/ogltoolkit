#include "lib/Framework/TreeNode.h"
#include <iostream>

using namespace std;

int main() {
        TreeNode* nodes = new TreeNode[11];

        nodes[0].addChildNode(&nodes[1]);
        nodes[0].addChildNode(&nodes[2]);
        nodes[0].addChildNode(&nodes[3]);

        nodes[1].addChildNode(&nodes[4]);
        nodes[1].addChildNode(&nodes[5]);

        nodes[3].addChildNode(&nodes[6]);
        nodes[3].addChildNode(&nodes[7]);

        TreeNode* node = new TreeNode("cool node");
        node->setParentNode(&nodes[0]);
        nodes[0].show();

        delete nodes->findChildNode("Unknown_4");

        nodes[0].show();

        return 0;
}

