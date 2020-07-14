#pragma once
#include <cassert>

//ģ��Ķ��壬SIZEΪջ�Ĵ�С
template<class T,int SIZE=50>
class Stack {
private:
	T list[SIZE];   //���飬���ڴ��ջ��Ԫ��
	int top;        //ջ��λ�ã������±꣩
public:
	Stack();        //���캯������ʼ��ջ
	void push(const T& item); //��Ԫ��itemѹ��ջ
	T pop();        //��ջ��Ԫ�ص���ջ
	void clear();   //��ջ���
	const T& peek() const; //����ջ��Ԫ��
	bool isEmpty() const;  //�����Ƿ�ջ��
	bool isFull() const;  //�����Ƿ�ջ��
};

//ģ���ʵ��
template<class T,int SIZE>
Stack<T,SIZE>::Stack():top(-1){ }  //���캯����ջ����ʼ��Ϊ-1

template<class T, int SIZE>
void Stack<T, SIZE>::push(const T& item) {
	assert(!isFull());
	list[++top] = item;
}

template<class T, int SIZE>
T Stack<T, SIZE>::pop() {
	assert(!isEmpty());
	return list[top--];
}

template<class T, int SIZE>
const T& Stack<T, SIZE>::peek() const {
	assert(!isEmpty());
	return list[top];
}

template<class T, int SIZE>
bool Stack<T, SIZE>::isEmpty() const {
	return top == -1;
}

template<class T, int SIZE>
bool Stack<T, SIZE>::isFull() const {
	return top == SIZE - 1;
}

template<class T, int SIZE>
void Stack<T, SIZE>::clear() {
	top = -1;
}