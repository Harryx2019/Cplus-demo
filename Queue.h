#pragma once
#include<cassert>

template<class T,int SIZE=50>
class Queue {
private:
	int front, rear, count;  //队头指针，队尾指针，元素个数
	T list[SIZE];  //队列元素数组
public:
	Queue();
	void insert(const T& item); //新元素入队
	T remove(); //元素出队
	void clear();  //清空队列
	const T& getFront() const; //访问队首指针

	//测试队列状态
	int getLength() const;
	bool isEmpty() const;
	bool isFull() const;
};

template<class T, int SIZE>
Queue<T,SIZE>::Queue():front(0),rear(0),count(0){ }

template<class T, int SIZE>
void Queue<T, SIZE>::insert(const T& item) {
	assert(count != SIZE);
	count++;
	list[rear] = item;
	rear = (rear + 1) % SIZE;  //队尾指针增1，用取余运算实现循环队列
}

template<class T, int SIZE>
T Queue<T, SIZE>::remove() {
	assert(count != 0);
	int temp = front;
	count--;
	front = (front + 1) % SIZE;
	return list[temp];
}

template<class T, int SIZE>
const T& Queue<T, SIZE>::getFront() const {
	return list[front];
}

template<class T, int SIZE>
int Queue<T, SIZE>::getLength() const {
	return count;
}

template<class T, int SIZE>
bool Queue<T, SIZE>::isEmpty() const {
	return count == 0;
}

template<class T, int SIZE>
bool Queue<T, SIZE>::isFull() const {
	return count == SIZE;
}

template<class T, int SIZE>
void Queue<T, SIZE>::clear() {
	count = 0;
	front = 0;
	rear = 0;
}
