#pragma once
#include <cassert>

//模板的定义，SIZE为栈的大小
template<class T,int SIZE=50>
class Stack {
private:
	T list[SIZE];   //数组，用于存放栈的元素
	int top;        //栈顶位置（数组下标）
public:
	Stack();        //构造函数，初始化栈
	void push(const T& item); //将元素item压入栈
	T pop();        //将栈顶元素弹出栈
	void clear();   //将栈清空
	const T& peek() const; //访问栈顶元素
	bool isEmpty() const;  //测试是否栈空
	bool isFull() const;  //测试是否栈满
};

//模板的实现
template<class T,int SIZE>
Stack<T,SIZE>::Stack():top(-1){ }  //构造函数，栈顶初始化为-1

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