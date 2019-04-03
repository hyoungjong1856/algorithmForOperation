#include <cstdio>
#include <iostream>
#include <queue>
#include <string>
#include <cstring>

using namespace std;
// ���μ��� ����ü
struct Process {
	string name;					// ���μ����� �̸�
	int arrival_time;			// �޸𸮿� �� �ð�
	int burst_time;				// ����ð�
	int waiting_time;			// ��ٸ� �ð�
	int turnaround_time;			// �� ����ð�
	double normalized_time;			// ����ȭ �ð�
	int running_time;			// �����ð�
	int remain_time; 				// �����ϱ⿡ ���� �ð�.
	int process_arrival_time;		// ���μ����� ���� �ð�.
	Process() :name("null") {};
	Process(string aname, int aarrival_time, int aburst_time, int awaiting_time, int aturnaround_time, double anormalized_time, int arunning_time, int aremain_time) {
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

template <typename T>
void showing(T que) {
	while (!que.empty()) {
		Process p = que.front();
		que.pop();
		printf("���μ��� �̸� : %s arrive time : %d Burst Time : %d , Waiting time : %d , Turnaround Time : %d , normalized time %.2lf, running time : %d ���μ��� ���� �ð� : %d \n", p.name.c_str(), p.arrival_time, p.burst_time, p.waiting_time, p.turnaround_time, p.normalized_time, p.running_time, p.process_arrival_time);
	}
}

struct rr {
	bool operator()(Process t, Process u) {
		return t.arrival_time > u.arrival_time;
	}
};

struct comparison {
	bool operator()(Process t, Process u) {
		return t.arrival_time > u.arrival_time;
	}
};

template <typename R>
int rr_process(R* origin_queue, int quant);
/*bool compare(Process &a, Process &b) {
	if (a.arrival_time < b.arrival_time)
		return true;
	else
		return false;

}
*/



int main() {
	int num, y, z;
	string n;
	int quant;

	queue<Process> origin_que;			// ������ �Է��� ť

	cout << "Enter number of processes : ";
	cin >> num;
	cout << "Enter Time Quantum: ";
	cin >> quant;
	cout << endl;

	for (int i = 0; i < num; i++) {
		cout << "Enter name of process name: ";
		cin >> n;
		cout << "Enter arrival time & burst time: ";
		cin >> y >> z;
		origin_que.push(Process(n, y, z,0,0,0,0,0));

		cout << endl;

	}

	//showing(origin_que);

	rr_process(&origin_que, quant);

	showing(origin_que);

	return 0;
}
template <typename R>
int rr_process(R* origin_queue,int quant) {
	priority_queue<Process, vector<Process>, rr>memory_queue;
	priority_queue<Process, vector<Process>, comparison > tmp;
	Process processor;
	Process	tmp_process;
	int time = 0;
	int time_burst_time;
	int total_time = 0;
	int time_burst_sum = 0;

	while (!origin_queue->empty()) {
		Process temp = origin_queue->front();
		tmp.push(temp);
		if (time < (temp.arrival_time + time_burst_sum)) {
			time_burst_sum += temp.burst_time;
			time = temp.arrival_time + time_burst_sum;
		}
		origin_queue->pop();
	}
	//printf("time : %d\n", time);

	// time�� t���� time�ʱ��� ī��Ʈ �Ѵ�.
	for (int t = 0; t <= time; t++) {
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
		if (!processor.isNull()) {
			// ���μ����� �ִ� waiting time���� �޸� ť�� remain time�� �� ������ ���μ��� ť�� �޸�ť�� �ְ�. �޸�ť�� ���μ����� �ִ´�.
			if (!memory_queue.empty()) {
				Process temp_process = memory_queue.top();
				if (temp_process.arrival_time < processor.arrival_time) { //arriveŸ������ �켱������ ������ �ȴ�.
					memory_queue.pop();
					memory_queue.push(processor);
					origin_queue->push(processor);
					processor = temp_process;
					processor.process_arrival_time = t;		// ���μ����� ���� �ð� ��� (ü���� �� �ð�)
				}
			}

			if (processor.remain_time > 0) {
				processor.running_time++;

				processor.remain_time = processor.burst_time - quant;  //�����ð� = ��burstŸ�� - quantumŸ��
				if (processor.remain_time <= 0){
					processor.remain_time = 0;
				}
			}
			if (processor.remain_time == 0) {
				processor.turnaround_time = t - processor.arrival_time + 1;
				processor.waiting_time = processor.turnaround_time - processor.burst_time;
				processor.normalized_time = (double)processor.turnaround_time / processor.burst_time;
				//printf("%d �ʿ� ���μ��� %s�� origin_queue�� ���Խ��ϴ�.\n ", t, processor.name.c_str());
				origin_queue->push(processor);

				if (t > total_time) {					// ��ü �� ���� �ð��� ���� �ð����� ������ �� ���� �ð��� ���� �ð����� 
					total_time = t;
				}
				processor.setNull(true);
			}

		}
	}

	return total_time + 1;
}