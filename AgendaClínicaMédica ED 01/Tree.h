#ifndef _TREE_LIST
#define _TREE_LIST
#include <Windows.h>
#include <fstream>
#include "TreeNode.h"
using namespace std;
fstream treeList;

template <typename S> class TreeList {
	NodeTree<S>* root = NULL;
	char *file;
};
#endif