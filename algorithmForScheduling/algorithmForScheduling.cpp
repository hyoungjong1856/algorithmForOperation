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
	string name;					// ���μ����� �̸�
	double arrival_time;			// �޸𸮿� �� �ð�
	double burst_time;				// ����ð�
	double waiting_time;			// ��ٸ� �ð�
	double turnaround_time;			// �� ����ð�
	double normalized_time;			// ����ȭ �ð�
	double running_time;			// �����ð�
	Process(double arrival_time, double burst_time) : arrival_time(arrival_time), burst_time(burst_time), waiting_time(0), turnaround_time(0), normalized_time(0) {}
};

// SPN ���μ��� �Լ� 
template <typename T>
void spn_process(T* aa);

// ���μ��� �� �Լ�,  �Է½ð����� �����ϴ� �Լ�
struct comparison {
	bool operator()(Process t, Process u) {
		return t.arrival_time > u.arrival_time;
	}
};

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
	que.push(Process(5, 2));
	que.push(Process(3, 5));
	que.push(Process(6, 3));

	spn_process(&que);			// ť�� �ּҸ� �Լ��� �Ű������� ���
	
	showing(que);

	return 0;
}

// SPN ���μ��� �Լ� ���⼭�� ť�� �����͸� �Է¹ް� �� ť�� SPN ���μ��� �����층�� �����Ͽ� ��⿭�� �ְ� �����ϴ� �Լ�
// �� �Լ��� �����ϸ� ��.
// ������ ť�� �켱���� ť���ƴ� �Ϲ� ���� stl ť�� ���
template <typename T>
void spn_process(T* origin_queue) {
	priority_queue<Process, vector<Process>, spn> memory_queue;		// �޸� ť
	priority_queue<Process, vector<Process>, comparison> tmp;


	// ���� ť�� �Է¹޾Ƽ� ���Ľ�Ű�鼭 temp �켱���� ť�� �Է½�Ų��.
	while (!origin_queue->empty()) {
		tmp.push(origin_queue->front());
		origin_queue->pop();
	}
	
//	while (!tmp.empty()) {
//		cout << "�ӽ� ť"<<tmp.top().arrival_time << endl;
//		tmp.pop();
//	}
	// time�� t���� 20�ʱ��� ī��Ʈ �Ѵ�.
	for (int t = 0; t <= 20; t++) {
		int arr_time = tmp.top().arrival_time;
		if (arr_time == t) {
			memory_queue.push(tmp.top);
			tmp.pop();

		}
	}
}