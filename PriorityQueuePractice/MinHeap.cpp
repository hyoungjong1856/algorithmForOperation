/*
Priority Queue �����ڵ�

*/
#include <iostream>
#include <queue>

using namespace std;

int main() {

	priority_queue <int, vector<int>, less<int>> pq; // �������� less �ڸ��� greater�� �־���.

	//push(element)
	pq.push(5);
	pq.push(2);
	pq.push(8);
	pq.push(9);
	pq.push(1);
	pq.push(14);


	pq.pop();
	pq.pop();

	//top()
	cout << "pq top : " << pq.top() << '\n';

	//empty(), size()
	if (!pq.empty()) cout << "pq size: " << pq.size() << '\n';


	// pop all
	while (!pq.empty()) {
		cout << pq.top() << " ";
		pq.pop();
	}

	cout << '\n';

	return 0;
}