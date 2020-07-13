#pragma once
#include <iostream>
#include <cstdlib>

#include "Node.h"
using namespace std;

template<class T>
class LinkedList {
private:
	//���ݳ�Ա
	Node<T>* front, * rear; //��ͷ�ͱ�βָ��
	Node<T>* prevPtr, * currPtr; //��¼��ǰ����λ�õ�ָ�룬�ɲ����ɾ����������
	int size;  //���е�Ԫ�ظ���
	int position; //��ǰԪ���ڱ��е�λ����š��ɺ���resetʹ��

	//������Ա
	//�����½�㣬������Ϊitem,ָ����ΪptrNext
	Node<T>* newNode(const T& item, Node<T>* ptrNext = NULL);

	//�ͷŽ��
	void freeNode(Node<T>* p);

	//������L���Ƶ���ǰ�����赱ǰ��Ϊ�գ�
	//�����ƹ��캯����"operator="����
	void copy(const LinkedList<T>& L);

public:
	LinkedList();                        //���캯��
	LinkedList(const LinkedList<T>& L);  //���ƹ��캯��
	~LinkedList();                       //��������
	LinkedList<T>& operator=(const LinkedList<T>& L);  //���ظ�ֵ�����

	int getSize() const;  //����������Ԫ�ظ���
	bool isEmpty() const; //�����Ƿ�Ϊ��

	void reset(int pos = 0); //��ʼ���α��λ��
	void next(); //ʹ�α��ƶ���һ�¸����
	bool endOfList() const; //�α��Ƿ�����β
	int currentPosition(void) const; //�����α굱ǰ��λ��

	void insertFront(const T& item); //�ڱ�ͷ������
	void insertRear(const T& item);  //�ڱ�β��ӽ��
	void insertAt(const T& item); //�ڵ�ǰ���֮ǰ������
	void insertAfter(const T& item); //�ڵ�ǰ���֮�������

	T deleteFront(); //ɾ��ͷ���
	void deleteCurrent(); //ɾ����ǰ���

	T& data(); //���ضԵ�ǰ����Ա���ݵ�����
	const T& data() const;

	//��������ͷ����н����ڴ�ռ䡣������������"operator="����
	void clear();
};

//�����½�㣬������Ϊitem,ָ����ΪptrNext
template<class T>
Node<T>* LinkedList<T>::newNode(const T& item, Node<T>* ptrNext) {
	Node<T>* newNode;
	newNode = new Node<T>(item, ptrNext);
	if (newNode == NULL) {
		cerr << "Memory allocation failure!" << endl;
		exit(1);
	}
	return newNode;
}

//�ͷŽ��
template<class T>
void LinkedList<T>::freeNode(Node<T>* p) {
	delete p;
}

//������L���Ƶ���ǰ�����赱ǰ��Ϊ�գ�
//�����ƹ��캯����"operator="����
template<class T>
void LinkedList<T>::copy(const LinkedList<T>& L) {
	if (L.size == 0)
		return;
	front = rear = newNode(L.front->data);
	for (Node<T>* srcNode = L.front->nextNode(); srcNode != NULL; srcNode = srcNode->nextNode()) {
		Node<T>* newNode = newNode(srcNode->data);
		rear->insertAfter(newNode);
		rear = newNode;
	}
	size = L.size;
	reset(position = L.currentPosition());
}

//���캯��
template<class T>
LinkedList<T>::LinkedList():front(NULL),rear(NULL),prevPtr(NULL),currPtr(NULL),size(0),position(0){ }

//���ƹ��캯��
template<class T>
LinkedList<T>::LinkedList(const LinkedList<T>& L): front(NULL), rear(NULL), prevPtr(NULL), currPtr(NULL), size(0), position(0) {
	copy(L);
}

//��������
template<class T>
LinkedList<T>::~LinkedList() {
	clear();
}

//���ظ�ֵ�����
template<class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& L) {
	clear();
	copy(L);
	return *this;
}

//����������Ԫ�ظ���
template<class T>
int LinkedList<T>::getSize() const {
	return size;
}

//�ж��Ƿ�ձ�
template<class T>
bool LinkedList<T>::isEmpty() const {
	return(size == 0);
}

//��ʼ���α�λ��
template<class T>
void LinkedList<T>::reset(int pos) {
	if (0 <= pos && pos <= size) {
		position = 0;
		prevPtr = NULL;
		currPtr = front;
		//�α�ص�ͷ��㣬����ǰ��
		while (pos--) {
			next();
		}
	}
	else {
		position = pos;
		prevPtr = NULL;
		currPtr = NULL;
	}
}

//ʹ�α��ƶ�����һ�����
template<class T>
void LinkedList<T>::next() {
	position++;
	prevPtr = currPtr;
	if (currPtr != NULL) {
		currPtr = currPtr->nextNode();
	}
}

//�α��Ƿ�����β
template<class T>
bool LinkedList<T>::endOfList() const {
	return(currPtr == NULL);
}

//�����α굱ǰ��λ��
template<class T>
int LinkedList<T>::currentPosition() const {
	return position;
}

//�ڱ�ͷ������
template<class T>
void LinkedList<T>::insertFront(const T& item) {
	front = newNode(item, front);
	if (isEmpty()) 
		rear = front;
	size++;
	reset(++position);
}

//�ڱ�β������
template<class T>
void LinkedList<T>::insertRear(const T& item) {
	Node<T>* newNode = newNode(item);
	if (isEmpty()) {
		front = rear = newNode;
	}
	else {
		rear->insertAfter(newNode);
		rear = newNode;
	}
	size++;
	reset(position);
}

//�ڵ�ǰ���֮ǰ������
template<class T>
void LinkedList<T>::insertAt(const T& item) {
	if (currPtr != NULL) {
		Node<T>* newNode = newNode(item, currPtr);
		if (prevPtr != NULL)
			prevPtr->insertAfter(newNode);
		else
			front = prevPtr = newNode;
		size++;
		reset(++position);
	}
}

//�ڵ�ǰ���֮�������
template<class T>
void LinkedList<T>::insertAfter(const T& item) {
	if (currPtr != NULL) {
		Node<T>* newNode = newNode(item, currPtr->nextNode());
		currPtr->insertAfter(newNode);
		if (rear == currPtr)
			rear = newNode;
		size++;
	}
}

//ɾ��ͷ���
template<class T>
T LinkedList<T>::deleteFront() {
	if (isEmpty()) {
		cerr << "List is empty,delete error." << endl;
		exit(1);
	}
	Node<T>* delNode = front;
	front = front->nextNode();
	if (--size == 0)
		rear = NULL;
	reset(--position);
	T item = delNode->data;
	freeNode(delNode);
	return item;
}

//ɾ����ǰ���
template<class T>
void LinkedList<T>::deleteCurrent() {
	if (currPtr != NULL) {
		if (front == currPtr)
			front = currPtr->nextNode();
		if (rear == currPtr)
			rear = prevPtr;
		if (prevPtr != NULL)
			prevPtr->deleteAfter();
		freeNode(currPtr);
		size--;
		reset(--position);
	}
}

//���ضԵ�ǰ����Ա���ݵ�����
template<class T>
T& LinkedList<T>::data() {
	if (currPtr == NULL) {
		cerr << "Current node is invalid." << endl;
		exit(1);
	}
	return currPtr->data;
}

template<class T>
const T& LinkedList<T>::data()const {
	if (currPtr == NULL) {
		cerr << "Current node is invalid." << endl;
		exit(1);
	}
	return currPtr->data;
}

//�������
template<class T>
void LinkedList<T>::clear() {
	while (!isEmpty())
		deleteFront();
}

void ApplyLinkedList();