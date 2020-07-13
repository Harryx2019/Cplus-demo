#pragma once
#include <iostream>
#include <cstdlib>

#include "Node.h"
using namespace std;

template<class T>
class LinkedList {
private:
	//数据成员
	Node<T>* front, * rear; //表头和表尾指针
	Node<T>* prevPtr, * currPtr; //记录表当前遍历位置的指针，由插入和删除操作更新
	int size;  //表中的元素个数
	int position; //当前元素在表中的位置序号。由函数reset使用

	//函数成员
	//生成新结点，数据域为item,指针域为ptrNext
	Node<T>* newNode(const T& item, Node<T>* ptrNext = NULL);

	//释放结点
	void freeNode(Node<T>* p);

	//将链表L复制到当前表（假设当前表为空）
	//被复制构造函数和"operator="调用
	void copy(const LinkedList<T>& L);

public:
	LinkedList();                        //构造函数
	LinkedList(const LinkedList<T>& L);  //复制构造函数
	~LinkedList();                       //析构函数
	LinkedList<T>& operator=(const LinkedList<T>& L);  //重载赋值运算符

	int getSize() const;  //返回链表中元素个数
	bool isEmpty() const; //链表是否为空

	void reset(int pos = 0); //初始化游标的位置
	void next(); //使游标移动到一下个结点
	bool endOfList() const; //游标是否到了链尾
	int currentPosition(void) const; //返回游标当前的位置

	void insertFront(const T& item); //在表头插入结点
	void insertRear(const T& item);  //在表尾添加结点
	void insertAt(const T& item); //在当前结点之前插入结点
	void insertAfter(const T& item); //在当前结点之后插入结点

	T deleteFront(); //删除头结点
	void deleteCurrent(); //删除当前结点

	T& data(); //返回对当前结点成员数据的引用
	const T& data() const;

	//清空链表：释放所有结点的内存空间。被析构函数和"operator="调用
	void clear();
};

//生成新结点，数据域为item,指针域为ptrNext
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

//释放结点
template<class T>
void LinkedList<T>::freeNode(Node<T>* p) {
	delete p;
}

//将链表L复制到当前表（假设当前表为空）
//被复制构造函数和"operator="调用
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

//构造函数
template<class T>
LinkedList<T>::LinkedList():front(NULL),rear(NULL),prevPtr(NULL),currPtr(NULL),size(0),position(0){ }

//复制构造函数
template<class T>
LinkedList<T>::LinkedList(const LinkedList<T>& L): front(NULL), rear(NULL), prevPtr(NULL), currPtr(NULL), size(0), position(0) {
	copy(L);
}

//析构函数
template<class T>
LinkedList<T>::~LinkedList() {
	clear();
}

//重载赋值运算符
template<class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& L) {
	clear();
	copy(L);
	return *this;
}

//返回链表中元素个数
template<class T>
int LinkedList<T>::getSize() const {
	return size;
}

//判断是否空表
template<class T>
bool LinkedList<T>::isEmpty() const {
	return(size == 0);
}

//初始化游标位置
template<class T>
void LinkedList<T>::reset(int pos) {
	if (0 <= pos && pos <= size) {
		position = 0;
		prevPtr = NULL;
		currPtr = front;
		//游标回到头结点，再逐步前移
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

//使游标移动到下一个结点
template<class T>
void LinkedList<T>::next() {
	position++;
	prevPtr = currPtr;
	if (currPtr != NULL) {
		currPtr = currPtr->nextNode();
	}
}

//游标是否到了链尾
template<class T>
bool LinkedList<T>::endOfList() const {
	return(currPtr == NULL);
}

//返回游标当前的位置
template<class T>
int LinkedList<T>::currentPosition() const {
	return position;
}

//在表头插入结点
template<class T>
void LinkedList<T>::insertFront(const T& item) {
	front = newNode(item, front);
	if (isEmpty()) 
		rear = front;
	size++;
	reset(++position);
}

//在表尾插入结点
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

//在当前结点之前插入结点
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

//在当前结点之后插入结点
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

//删除头结点
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

//删除当前结点
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

//返回对当前结点成员数据的引用
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

//清空链表
template<class T>
void LinkedList<T>::clear() {
	while (!isEmpty())
		deleteFront();
}

void ApplyLinkedList();