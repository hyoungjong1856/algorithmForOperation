/*
��¥ 19. 03 .25
�˰��� ��Ʈ : ȫ����, ������

�ۼ��� :ȫ����
SPN ���� �õ�
*/

#include <cstdio>
#include <iostream>
#include <queue>
#include <cstring>

using namespace std;
// ���μ��� ����ü
struct Process {
	string name;					// ���μ����� �̸�
	int arrival_time;			// �޸𸮿� �� �ð�
	int burst_time;				// ����ð�
	int waiting_time;			// ��ٸ� �ð�
	int turnaround_time ;			// �� ����ð�
	double normalized_time;			// ����ȭ �ð�
	int running_time ;			// �����ð�
	int remain_time; 				// �����ϱ⿡ ���� �ð�.
	Process() :name("null") {};
	Process(string aname, int aarrival_time, int aburst_time, int awaiting_time, int aturnaround_time, double anormalized_time, int arunning_time, int aremain_time){
		name = aname;
		arrival_time = aarrival_time;
		burst_time = aburst_time;
		waiting_time = awaiting_time;
		turnaround_time = aturnaround_time;
		normalized_time = anormalized_time;
		running_time = arunning_time;
		remain_time = burst_time;
	}

	bool isNull() {
		if (name == "null") {
			return true;
		}
		else {
			return false;
		}
	}

	void setNull(bool isNull) {
		if (isNull == true) {
			name = "null";
		}
	}
};

// SPN ���μ��� �Լ� 
template <typename T>
void spn_process(T* origin_queue);

//SRTN ���μ��� �Լ�
template <typename T>
void srtn_process(T* origin_queue);

//hrrn ���μ��� �Լ�
template <typename T>
void hrrn_process(T* origin_queue);

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

// hrrn �� �Լ�
struct hrrn {
	bool operator()(Process t, Process u) {
		double t_response_ratio = ((double)t.waiting_time + t.burst_time) / t.burst_time;
		double u_response_ratio = ((double)u.waiting_time + u.burst_time) / u.burst_time;
		return t_response_ratio < u_response_ratio;
	}
};

// �ܼ��� que�� burst time �� ������ִ� �Լ� (�ܼ� �׽�Ʈ�� ) 
template <typename T>
void showing(T que) {
	while (!que.empty()) {
		Process p = que.front();
		que.pop();
		printf("���μ��� �̸� : %s arrive time : %d Burst Time : %d , Waiting time : %d , Turnaround Time : %d , normalized time %.2lf, running time : %d \n", p.name.c_str(), p.arrival_time, p.burst_time, p.waiting_time, p.turnaround_time, p.normalized_time, p.running_time);
	}
}

int main() {
	queue<Process> que;			// ������ �Է��� ť
								//Process p{ "p1",0,2,3,4,5,6,7 };
	Process p{"dd",1,2,3,4,5,6,7};
	//printf("?���μ��� �̸� : %s arrive time : %d Burst Time : %d , Waiting time : %d , Turnaround Time : %d , normalized time %lf, running time : %d \n", p.name, p.arrival_time, p.burst_time, p.waiting_time, p.turnaround_time, p.normalized_time, p.running_time);	//
	que.push(Process{ "p1",0,3,0,0,0,0,0 });
	//printf("?%s\n", p.name.c_str());
	//printf("?���μ��� �̸� : %s arrive time : %d Burst Time : %d , Waiting time : %d , Turnaround Time : %d , normalized time %lf, running time : %d \n", p.name.c_str(), p.arrival_time, p.burst_time, p.waiting_time, p.turnaround_time, p.normalized_time, p.running_time);
	que.push(Process{ "p2",1,7,0,0,0,0,0 });
	que.push(Process{ "p3",3,2,0,0,0,0,0 });
	que.push(Process{ "p4",5,5,0,0,0,0,0 });
	que.push(Process{ "p5",6,3,0,0,0,0,0 });

	showing(que);

	hrrn_process(&que);			// ť�� �ּҸ� �Լ��� �Ű������� ���
	
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
	Process processor;										// ���μ��� ���
	Process tmp_process;

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
		// tmp ť���� �޸� ť�� �ֱ�
		int tmp_size = tmp.size();		// tmp ť�� ������
		for (int i = 0; i < tmp_size; i++) {
			int arr_time = (int)tmp.top().arrival_time;
			if (arr_time == t) {
				tmp_process = tmp.top();
				memory_queue.push(tmp_process);		// �޸� ť�� ������ burst time�� ���� �� �������� �ڵ� ������ �ȴ�.
				tmp.pop();
//				printf("%d �ʿ� �޸� ť�� %s�� ���Խ��ϴ�. \n", t,tmp_process.name.c_str());
			}
		}

		// processor�� ����� �ȵǾ����� ���� �޸��� �տ� �ִ� ���� ���� ��Ͻ�Ų��.
		if (processor.isNull()) {
			// �޸�ť���� ���μ����� ��Ͻ�Ų��.
			if (!memory_queue.empty()) {
				processor = memory_queue.top();
				memory_queue.pop();
				processor.running_time = 0;			// �ʱ�ȭ ��Ų��.
				printf("%d �ʿ� ���μ����� %s�� ���Խ��ϴ�. \n", t, processor.name.c_str());			// ����... �� 1�ʾ� ���ܼ� �����°�?
			}
		}
		if (!processor.isNull()) {
			if (processor.remain_time > 0) {
				processor.running_time++;
				processor.remain_time--;
			}
			if (processor.remain_time == 0) {
				processor.turnaround_time = t - processor.arrival_time + 1;
				processor.waiting_time = processor.turnaround_time - processor.burst_time;
				processor.normalized_time = (double)processor.turnaround_time / processor.burst_time;
//				printf("%d �ʿ� ���μ��� %s�� origin_queue�� ���Խ��ϴ�.\n ", t, processor.name.c_str());
				origin_queue->push(processor);
				processor.setNull(true);
			}
			
		}
		
	}
}



// Strn ���μ��� �Լ� ���⼭�� ť�� �����͸� �Է¹ް� �� ť�� hrrn ���μ��� �����층�� �����Ͽ� ��⿭�� �ְ� �����ϴ� �Լ�
// ������ ť�� �켱���� ť���ƴ� �Ϲ� ���� stl ť�� ���
// ���� �����̸� spn�� ���� ����̴�. ���μ����� ��� �ð��� ����ؼ� ��ȸ�� ������
// response ratio= (WT+BT) /BT (�����)�� ���� ���μ����� �켱���� �����.
template <typename T>
void srtn_process(T* origin_queue) {
	priority_queue<Process, vector<Process>, spn> memory_queue;		// �޸� ť
	priority_queue<Process, vector<Process>, comparison> tmp;
	Process processor;										// ���μ��� ���
	Process tmp_process;

	// ���� ť�� �Է¹޾Ƽ� ���Ľ�Ű�鼭 temp �켱���� ť�� �Է½�Ų��.
	while (!origin_queue->empty()) {
		tmp.push(origin_queue->front());
		origin_queue->pop();
	}

	// time�� t���� 20�ʱ��� ī��Ʈ �Ѵ�.
	for (int t = 0; t <= 20; t++) {
		// tmp ť���� �޸� ť�� �ֱ�
		int tmp_size = tmp.size();		// tmp ť�� ������
		for (int i = 0; i < tmp_size; i++) {
			int arr_time = (int)tmp.top().arrival_time;
			if (arr_time == t) {
				tmp_process = tmp.top();
				memory_queue.push(tmp_process);		// �޸� ť�� ������ burst time�� ���� �� �������� �ڵ� ������ �ȴ�.
				tmp.pop();
				//				printf("%d �ʿ� �޸� ť�� %s�� ���Խ��ϴ�. \n", t,tmp_process.name.c_str());
			}
		}

		// processor�� ����� �ȵǾ����� ���� �޸��� �տ� �ִ� ���� ���� ��Ͻ�Ų��.
		// �׸��� SRTN�� ���� ���μ��� ������� ��ϵ� �޸��� ���� remain time�� �� ������ ü����. 
		if (processor.isNull()) {
			// �޸�ť���� ���μ����� ��Ͻ�Ų��.
			if (!memory_queue.empty()) {
				processor = memory_queue.top();
				memory_queue.pop();
				processor.running_time = 0;			// �ʱ�ȭ ��Ų��.
				printf("%d �ʿ� ���μ����� %s�� ���Խ��ϴ�. \n", t, processor.name.c_str());			// ����... �� 1�ʾ� ���ܼ� �����°�?
			}
		}
		if (!processor.isNull()) {
			// ���μ����� �ִ� waiting time���� �޸� ť�� remain time�� �� ������ ���μ��� ť�� �޸�ť�� �ְ�. �޸�ť�� ���μ����� �ִ´�.
			if (!memory_queue.empty()) {
				Process temp_process = memory_queue.top();
				if (temp_process.remain_time < processor.remain_time) {
					memory_queue.pop();
					memory_queue.push(processor);
					origin_queue->push(processor);
					printf("%d�ʿ� ���μ��� %s�� �޸� ť�� �ִ� ���μ��� %s�� ��ȯ�Ͽ����ϴ�.", t, processor.name.c_str(), temp_process.name.c_str());
					processor = temp_process;
				}
			}
			
			if (processor.remain_time > 0) {
				processor.running_time++;
				processor.remain_time--;
			}
			if (processor.remain_time == 0) {
				processor.turnaround_time = t - processor.arrival_time + 1;
				processor.waiting_time = processor.turnaround_time - processor.burst_time;
				processor.normalized_time = (double)processor.turnaround_time / processor.burst_time;
				//				printf("%d �ʿ� ���μ��� %s�� origin_queue�� ���Խ��ϴ�.\n ", t, processor.name.c_str());
				origin_queue->push(processor);
				processor.setNull(true);
			}

		}

	}
}

// HRRN ���μ��� �Լ� ���⼭�� ť�� �����͸� �Է¹ް� �� ť�� HRRN ���μ��� �����층�� �����Ͽ� ��⿭�� �ְ� �����ϴ� �Լ�
// �� �Լ��� �����ϸ� ��.
// ������ ť�� �켱���� ť���ƴ� �Ϲ� ���� stl ť�� ���
template <typename T>
void hrrn_process(T* origin_queue) {
	priority_queue<Process, vector<Process>, spn> memory_queue;		// �޸� ť
	priority_queue<Process, vector<Process>, comparison> tmp;
	priority_queue<Process, vector<Process>, hrrn> hrrn_queue;		// hrrn �����ϴ� ť.
	Process processor;										// ���μ��� ���
	Process tmp_process;

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
		// tmp ť���� �޸� ť�� �ֱ�
		int tmp_size = tmp.size();		// tmp ť�� ������
		for (int i = 0; i < tmp_size; i++) {
			int arr_time = (int)tmp.top().arrival_time;
			if (arr_time == t) {
				tmp_process = tmp.top();
				memory_queue.push(tmp_process);		// �޸� ť�� ������ burst time�� ���� �� �������� �ڵ� ������ �ȴ�.
				tmp.pop();
				//				printf("%d �ʿ� �޸� ť�� %s�� ���Խ��ϴ�. \n", t,tmp_process.name.c_str());
			}
		}

		// processor�� ����� �ȵǾ����� ���� �޸��� �տ� �ִ� ���� ���� ��Ͻ�Ų��.
		if (processor.isNull()) {

			// �޸� ť�� �ִ� ���� hrrn ť��(hrrn ���μ��� ������ ������ �ٽ� ���Ľ�Ų��.)
			while (!memory_queue.empty()) {
				Process temp_process = memory_queue.top();
				temp_process.waiting_time = t - temp_process.arrival_time;
				hrrn_queue.push(temp_process);
				memory_queue.pop();
			}

			// hrrnť���� ���μ����� ��Ͻ�Ų��.
			if (!hrrn_queue.empty()) {
				processor = hrrn_queue.top();
				hrrn_queue.pop();
				processor.running_time = 0;			// �ʱ�ȭ ��Ų��.
				printf("%d �ʿ� ���μ����� %s�� ���Խ��ϴ�. \n", t, processor.name.c_str());			// ����... �� 1�ʾ� ���ܼ� �����°�?
			}

			// �����ִ� hrrn ť�� �ٽ� �޸� ť�� �ִ´�.
			while (!hrrn_queue.empty()) {
				memory_queue.push(hrrn_queue.top());
				hrrn_queue.pop();
			}
		}
		if (!processor.isNull()) {
			if (processor.remain_time > 0) {
				processor.running_time++;
				processor.remain_time--;
			}
			if (processor.remain_time == 0) {
				processor.turnaround_time = t - processor.arrival_time + 1;
				processor.waiting_time = processor.turnaround_time - processor.burst_time;
				processor.normalized_time = (double)processor.turnaround_time / processor.burst_time;
				//				printf("%d �ʿ� ���μ��� %s�� origin_queue�� ���Խ��ϴ�.\n ", t, processor.name.c_str());
				origin_queue->push(processor);
				processor.setNull(true);
			}

		}

	}
}