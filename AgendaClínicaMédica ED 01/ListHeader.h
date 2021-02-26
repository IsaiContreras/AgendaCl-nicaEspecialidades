#ifndef _NODES
#define _NODES
#include <Windows.h>
#include <fstream>
#include "ListNodeHeader.h"
using namespace std;
fstream listFile;

template <typename T> class LinkedList {
	Node<T> *first = NULL;
	Node<T> *last = NULL;
	char *file;
	void AddReadNode(Node<T>);
	void DeleteAll();
public:
	LinkedList(char*);
	Node<T>* getFirst();
	Node<T>* getLast();
	void AddNode(T);
	void DeleteNode(Node<T>*);
	Node<T>* SearchNode(int);
	void PrintOnWindow(HWND, int, const char*);
	int CountList();
	~LinkedList();
};
//// PRIVATE METHODS ////
template <typename T> void LinkedList<T>::AddReadNode(Node<T> readData) {
	Node<T> *nuevo = new Node<T>(readData);
	nuevo->prev = nuevo->next = NULL;
	if (first == NULL) {
		first = nuevo;
		last = nuevo;
	}
	else {
		last->next = nuevo;
		nuevo->prev = last;
		last = nuevo;
	}
}
template <typename T> void LinkedList<T>::DeleteAll() {
	while (first != NULL) {
		Node<T>* toDel = first;
		first = first->next;
		delete toDel;
	}
}
//// PUBLIC METHODS ////
template <typename T> Node<T>* LinkedList<T>::getFirst() {
	return this->first;
}
template <typename T> Node<T>* LinkedList<T>::getLast() {
	return this->last;
}
template <typename T> LinkedList<T>::LinkedList(char* file) {
	this->file = file;
	Node<T> aux;
	listFile.open(this->file, ios::in | ios::binary | ios::ate);
	if (listFile.is_open()) {
		int size = listFile.tellg();
		listFile.seekg(0, ios::beg);
		if (size > 0) {
			listFile.read((char*)&aux, sizeof(Node<T>));
			while (!listFile.eof()) {
				AddReadNode(aux);
				listFile.read((char*)&aux, sizeof(Node<T>));
			}
		}
	}
	listFile.close();
}
template <typename T> void LinkedList<T>::AddNode(T data) {
	Node<T> *nuevo = new Node<T>(data);
	nuevo->prev = nuevo->next = NULL;
	if (first == NULL) {
		first = nuevo;
		last = nuevo;
	}
	else {
		last->next = nuevo;
		nuevo->prev = last;
		last = nuevo;
	}
}
template <typename T> void LinkedList<T>::DeleteNode(Node<T>* toRemove) {
	if (toRemove->next == NULL & toRemove->prev == NULL) {
		delete toRemove;
		first = last = NULL;
	}
	else if (toRemove->prev == NULL) {
		toRemove->next->prev = NULL;
		first = toRemove->next;
		delete toRemove;
	}
	else if (toRemove->next == NULL) {
		toRemove->prev->next = NULL;
		last = toRemove->prev;
		delete toRemove;
	}
	else {
		toRemove->next->prev = toRemove->prev;
		toRemove->prev->next = toRemove->next;
		delete toRemove;
	}
}
template <typename T> Node<T>* LinkedList<T>::SearchNode(int ref) {
	Node<T> *aux = first;
	while (aux != NULL) {
		if (aux->getData().getID() == ref) {
			return aux;
		}
		aux = aux->next;
	}
	return NULL;
}
template <typename T> void LinkedList<T>::PrintOnWindow(HWND hWindow, int type, const char* search) {
	if (type == 0) {
		SendMessage(hWindow, LB_RESETCONTENT, 0, 0);
		Node<T> *aux = first;
		while (aux != NULL) {
			if (search != NULL) {
				T temp = aux->getData();
				if (temp != search) {
					aux = aux->next;
					continue;
				}
			}
			char buff[100];
			strcpy(buff, aux->callPrint());
			SendMessage(hWindow, LB_ADDSTRING, 0, (LPARAM)buff);
			aux = aux->next;
		}
	}
	else {
		SendMessage(hWindow, CB_RESETCONTENT, 0, 0);
		Node<T> *aux = first;
		while (aux != NULL) {
			if (search != NULL) {
				T temp = aux->getData();
				if (temp != search) {
					aux = aux->next;
					continue;
				}
			}
			char buff[100];
			strcpy(buff, aux->callPrint());
			SendMessage(hWindow, CB_ADDSTRING, 0, (LPARAM)buff);
			aux = aux->next;
		}
	}
}
template <typename T> int LinkedList<T>::CountList() {
	int c = 0;
	Node<T> *aux = first;
	while (aux != NULL) {
		c++;
		aux = aux->next;
	}
	return c;
}
template <typename T> LinkedList<T>::~LinkedList() {
	Node<T> *aux = first;
	listFile.open(this->file, ios::out | ios::binary);
	if (listFile.is_open()) {
		while (aux != NULL) {
			listFile.write((char*)aux, sizeof(Node<T>));
			aux = aux->next;
		}
	}
	listFile.close();
	DeleteAll();
}
#endif