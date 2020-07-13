#include <iostream>
#include "LinkedList.h"
using namespace std;

void ApplyLinkedList() {
	LinkedList<int>list;

	//����10�������������ͷ����
	for (int i = 0; i < 10; i++) {
		int item;
		cin >> item;
		list.insertFront(item);
	}

	//�������
	cout << "List:";
	list.reset();
	//�����������ݣ�ֱ������β
	while (!list.endOfList()) {
		cout << list.data() << " ";
		list.next();
	}
	cout << endl;

	//������Ҫɾ��������
	int key;
	cout << "Please enter some integer needed to be deleted: ";
	cin >> key;

	//���Ҳ�ɾ�����
	list.reset();
	while (!list.endOfList()) {
		if (list.data() == key)
			list.deleteCurrent();
		list.next();
	}

	//�������
	cout << "List:";
	list.reset();
	while (!list.endOfList()) {
		cout << list.data() << " ";
		list.next();
	}
	cout << endl;
}