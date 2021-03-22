#include "tree.h"

Tree::Tree(){}

Tree::Tree(unique_ptr<NodeBase>& root): root(move(root)){}