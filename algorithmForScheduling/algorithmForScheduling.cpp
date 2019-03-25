/*
��¥ 19. 03 .25
�˰��� ��Ʈ : ȫ����, ������

�ۼ��� :ȫ����
SPN ���� �õ�
*/

#include <iostream>
#include <queue>

using namespace std;
// ���μ��� ����ü
struct Process {
	double arrival_time;			// �޸𸮿� �� �ð�
	double burst_time;				// ����ð�
	double waiting_time;			// ��ٸ� �ð�
	double turnaround_time;			// �� ����ð�
	double normalized_time;			// ����ȭ �ð�
	Process(double arrival_time, double burst_time) : arrival_time(arrival_time), burst_time(burst_time), waiting_time(0), turnaround_time(0), normalized_time(0) {}
};

// SPN ���μ��� �Լ� 
template <typename T>
void spn_process(T* aa);

// spn �� �Լ�
struct spn {
	bool operator()(Process t, Process u) {
		return t.burst_time > u.burst_time;
	}
};

// �ܼ��� que�� burst time �� ������ִ� �Լ� (�ܼ� �׽�Ʈ�� ) 
template <typename T>
void showing(T que) {
	while (!que.empty()) {
		Process p = que.front();
		que.pop();
		cout << p.burst_time << endl;
	}
}

int main() {
	queue<Process> que;			// ������ �Է��� ť
	que.push(Process(0, 3));
	que.push(Process(1, 7));
	que.push(Process(3, 2));
	que.push(Process(5, 5));
	que.push(Process(6, 3));

	spn_process(&que);			// ť�� �ּҸ� �Լ��� �Ű������� ���
	
	showing(que);

	return 0;
}

// SPN ���μ��� �Լ� ���⼭�� ť�� �����͸� �Է¹ް� �� ť�� SPN ���μ��� �����층�� �����Ͽ� ��⿭�� �ְ� �����ϴ� �Լ�
// �� �Լ��� �����ϸ� ��.
template <typename T>
void spn_process(T* aa) {
	priority_queue<Process, vector<Process>, spn> pq;

}