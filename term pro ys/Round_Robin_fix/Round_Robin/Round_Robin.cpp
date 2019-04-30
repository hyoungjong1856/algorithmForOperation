#include <cstdio>
#include <iostream>
#include <queue>
#include <cstring>
#include <string>

using namespace std;
// ���μ��� ����ü
struct Process {
	static int count;				// ���μ����� ���� ���� ī����
	int number;						// ���μ��� �⺻Ű
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
		number = Process::count++;
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

int Process::count = 0;



struct comparison {
	bool operator()(Process t, Process u) {
		return t.arrival_time > u.arrival_time;
	}
};

template <typename R>
int rr_process(R* origin_queue, R* table_que, int quant);

struct key {
	bool operator()(Process t, Process u) {
		return t.number > u.number;
	}
};

template <typename T>
void showing(T que, T table_queue) {
	while (!que.empty()) {
		Process p = que.front();
		que.pop();
		printf("���μ��� �̸� : %s arrive time : %d Burst Time : %d , Waiting time : %d , Turnaround Time : %d , normalized time %.2lf, running time : %d ���μ��� ���� �ð� : %d \n", p.name.c_str(), p.arrival_time, p.burst_time, p.waiting_time, p.turnaround_time, p.normalized_time, p.running_time, p.process_arrival_time);
	}
	if (!table_queue.empty()) {
		printf("----------------���̺� ��� ----------------------\n");
	}

	while (!table_queue.empty()) {
		Process p = table_queue.front();
		table_queue.pop();
		printf("���μ��� Ű : %d ���μ��� �̸� : %s arrive time : %d Burst Time : %d , Waiting time : %d , Turnaround Time : %d , normalized time %.2lf, running time : %d ���μ��� ���� �ð� : %d \n", p.number, p.name.c_str(), p.arrival_time, p.burst_time, p.waiting_time, p.turnaround_time, p.normalized_time, p.running_time, p.process_arrival_time);
	}
}

int main() {
	int num, y, z;
	string n;
	int quant;

	queue<Process> origin_que;			// ������ �Է��� ť
	queue<Process> table_que;

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

	showing(origin_que,table_que);

	rr_process(&origin_que, &table_que, quant);

	showing(origin_que,table_que);

	return 0;
}
template <typename R>
int rr_process(R* origin_queue,R* table_queue, int quant) {
	queue<Process> memory_queue;
	priority_queue<Process, vector<Process>, comparison> tmp;
	priority_queue<Process, vector<Process>, key> table_queue_tmp;
	Process processor;
	Process	tmp_process;
	int time = 0;   //���� ����ð�
	int total_time = 0;
	int time_burst_sum = 0;
	int remain_q = 0;

	// ���� �ʰ� �� ����̺�Ÿ�� + �� ����ƮŸ��
	while (!origin_queue->empty()) {
		Process temp = origin_queue->front();
		tmp.push(temp);

		int lastArrival_time = 0;
		//2 4  0 8
		if (lastArrival_time < temp.arrival_time)
			lastArrival_time = temp.arrival_time;

		time_burst_sum += temp.burst_time;

		time = time_burst_sum + lastArrival_time;

		origin_queue->pop();
	}

	// time�� t���� time�ʱ��� ī��Ʈ �Ѵ�.
	for (int t = 0; t <= 2*time; t++) {
		// tmp ť���� �޸� ť�� �ֱ�
		cout << "���� t�� " << t << endl;
		if(memory_queue.size() > 0)
			cout << "���� �޸�ž " << memory_queue.front().name << endl;
		int tmp_size = tmp.size();		// tmp ť�� ������
		for (int i = 0; i < tmp_size; i++) {
			int arr_time = (int)tmp.top().arrival_time;
			if (arr_time == t) {
				tmp_process = tmp.top();
				cout << "�޸�ť���ֱ� " << tmp_process.name << endl;
				memory_queue.push(tmp_process);		// �޸� ť�� ������ burst time�� ���� �� �������� �ڵ� ������ �ȴ�.
				tmp.pop();
				//printf("%d �ʿ� �޸� ť�� %s�� ���Խ��ϴ�. \n", t,tmp_process.name.c_str());
			}
		}

		if (processor.isNull()) {
			// �޸�ť���� ���μ����� ��Ͻ�Ų��.
			if (!memory_queue.empty()) {
				processor = memory_queue.front();
				cout << "���μ��� ���� " << processor.name << endl;
				memory_queue.pop();
				processor.running_time = 0;			// �ʱ�ȭ ��Ų��.
				processor.process_arrival_time = t;		// ���μ����� ���� �ð� ���.

				remain_q = quant;
				//printf("%d �ʿ� ���μ����� %s�� ���Խ��ϴ�. \n", t, processor.name.c_str());			// ����... �� 1�ʾ� ���ܼ� �����°�?
			}
		}

		// processor�� ����� �ȵǾ����� ���� �޸��� �տ� �ִ� ���� ���� ��Ͻ�Ų��.
		if (!processor.isNull()) {
			
			// ���μ����� �ִ� waiting time���� �޸� ť�� remain time�� �� ������ ���μ��� ť�� �޸�ť�� �ְ�. �޸�ť�� ���μ����� �ִ´�.
			/*if (!memory_queue.empty()) {
				Process temp_process = memory_queue.front();
				if (temp_process.arrival_time < processor.arrival_time) { //arriveŸ������ �켱������ ������ �ȴ�.
					memory_queue.pop();
					memory_queue.push(processor);
					origin_queue->push(processor);
					processor = temp_process;
					processor.process_arrival_time = t;		// ���μ����� ���� �ð� ��� (ü���� �� �ð�)
				}
			}*/	
			

			if (processor.burst_time > quant && remain_q >= 0){        //���� ���� burstŸ���� quant���� ũ�ٸ�
				processor.running_time += 1;      //���� �����Ȳ�� quant��ŭ�� ������Ų��.
				processor.remain_time -= 1;
				//processor.burst_time -= 1;
				cout << "���� ���μ��� " << processor.name << " ���� �� " << 1 << " ���� �Ͼ� " << processor.burst_time << endl;

				
				if (remain_q == 1) {
					memory_queue.push(processor);
					cout << processor.name << "���μ��� ����" << endl;
					processor.setNull(true);
				}
				cout << "���� ���� �� " << remain_q << endl;

				remain_q -= 1;
				cout << "���� ���� ���� �� " << remain_q << endl;
			}
			
			else if (processor.burst_time <= quant) {
				cout << "���� ���μ��� " << processor.name << " ������ ���� �� " << processor.burst_time << endl;
				processor.running_time += processor.burst_time;
				processor.remain_time = 0;
			}

			if (processor.remain_time == 0) {
				cout << t << " " << processor.name << " " << processor.arrival_time << " " << processor.burst_time << endl;
				processor.turnaround_time = t - processor.arrival_time + 1;
				processor.waiting_time = processor.turnaround_time - processor.burst_time;
				processor.normalized_time = (double)processor.turnaround_time / processor.burst_time;
				//printf("%d �ʿ� ���μ��� %s�� origin_queue�� ���Խ��ϴ�.\n ", t, processor.name.c_str());
				cout << "���� " << processor.name << endl;

				origin_queue->push(processor);
				table_queue_tmp.push(processor);
			

				if (t > total_time) {					// ��ü �� ���� �ð��� ���� �ð����� ������ �� ���� �ð��� ���� �ð����� 
					total_time = t;
				}
				processor.setNull(true);
			}
		}
	}
	while (!table_queue_tmp.empty()) {
		table_queue->push(table_queue_tmp.top());
		table_queue_tmp.pop();
	}

	return total_time + 1;
}