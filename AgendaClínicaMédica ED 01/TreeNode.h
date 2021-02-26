#ifndef _TREE_NODE
#define _TREE_NODE

template <typename S> class TreeList;

template <typename S> class NodeTree {
	friend class TreeList<S>;
	S data;
	NodeTree* left;
	NodeTree* right;
public:
	NodeTree() {};
	NodeTree(S);
	S getData();
	void setData(S);
	NodeTree<S>* getLeft();
	NodeTree<S>* getRight();
	char* callPrint();
};
template <typename S> NodeTree<S>::NodeTree(S data) {
	this->data = data;
}
template <typename S> S NodeTree<S>::getData() {

}
template <typename S> void NodeTree<S>::setData(S data) {

}
template <typename S> NodeTree<S>* NodeTree<S>::getLeft() {

}
template <typename S> NodeTree<S>* NodeTree<S>::getRight() {

}
template <typename S> char* NodeTree<S>::callPrint() {

}
#endif
