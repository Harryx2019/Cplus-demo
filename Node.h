#pragma once
template<class T>
class Node {
private:
	Node<T>* next; //ָ���̽���ָ��
public:
	T data; //������

	Node(const T& data, Node<T>* next = 0); //���캯��
	void insertAfter(Node<T>* p); //�ڱ����֮�����һ��ͬ����p
	Node<T>* deleteAfter();  //ɾ�������ĺ�̽�㣬���������ַ
	Node<T>* nextNode();  
	const Node<T>* nextNode() const; //��ȡ��̽��ĵ�ַ
};

//���ʵ�ֲ���
//���캯������ʼ�����ݺ�ָ���Ա
template<class T>
Node<T>::Node(const T& data,Node<T>* next):data(data),next(next){ }

//���غ�̽���ָ��
template<class T>
Node<T>* Node<T>::nextNode() {
	return next;
}

template<class T>
const Node<T>* Node<T>::nextNode() const {
	return next;
}

//�ڵ�ǰ���֮�����һ�����p
template<class T>
void Node<T>::insertAfter(Node<T>* p) {
	p->next = next;
	next = p;
}

//ɾ����ǰ���ĺ�̽�㣬���������ַ
template<class T>
Node<T>* Node<T>::deleteAfter() {
	Node<T>* tempPtr = next;
	if (next == 0)
		return 0;
	next = tempPtr->next;
	return tempPtr;
}