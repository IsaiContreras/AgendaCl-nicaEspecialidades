#ifndef _NODE_LIST
#define _NODE_LIST

template <typename T> class LinkedList;

template <typename T> class Node {
	friend class LinkedList<T>;
	T data;
	Node *next;
	Node *prev;
public:
	Node() {};
	Node(T);
	T getData();
	void setData(T);
	Node<T>* getNext();
	char* callPrint();
};
template <typename T> Node<T>::Node(T data) {
	this->data = data;
	this->next = NULL;
	this->prev = NULL;
}
template <typename T> T Node<T>::getData() {
	return this->data;
}
template <typename T> void Node<T>::setData(T data) {
	this->data = data;
}
template <typename T> Node<T>* Node<T>::getNext() {
	return this->next;
}
template <typename T>char* Node<T>::callPrint() {
	return data.print();
}
#endif