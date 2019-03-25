// �⺻ ����
/*

https://twpower.github.io/93-how-to-use-priority_queue-in-cpp
priority_queue<T, Container, Compare> :���ϴ� �ڷ��� �� Ŭ���� T�� ���� ����, ���⼭ Container�� vertor�� ���� �����̳��̸� Compare�� ���Լ� Ŭ�����̴�.

insert(element) :�켱���� ť�� ���� �߰�
pop() �켱���� ť���� top�� ���Ҹ� ����

top() top�� �ִ� ���Ҹ� ��ȯ

empty() :��������� true �ƴϸ� false�� ��ȯ
size() :�켱���� ť�� ���ԵǾ� �ִ� ���ҵ��� ���� ��ȯ

*/

#include <iostream>
#include <queue>

using namespace std;

int main() {

	// priority_queue
	priority_queue<int, vector<int>, less<int>> pq;
	// or priority_queue<int> pq;


	//push(element)
	pq.push(5);
	pq.push(2);
	pq.push(8);
	pq.push(9);
	pq.push(1);
	pq.push(14);
	


	//pop()
	pq.pop();
	pq.pop();

	//top();
	cout << "pq top : " << pq.top() << "\n";


	//empty() , size()
	if (!pq.empty()) cout << "pq size : " << pq.size() << "\n";

	while (!pq.empty()) {
		cout << pq.top() << " ";
		pq.pop();
	}

	cout << "\n";

	return 0;
}