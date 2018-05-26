#include<iostream>
#include<fstream>
#include<ctime>
#include<stdlib.h>
#include<queue>
using namespace std;

class tuple2 {
public:
	tuple2(int a, int b) {
		this->a = a;
		this->b = b;
	}
	int a;
	int b;
};

vector<int> *G;
int pointNum = 6006;
int need = 60;
vector<int> *Nk;
int *validCircle;
int k = 2;
int *maxHeap;
int *heapPos;
int heapLast;
vector<int> resultSet;

void loadG() {
	G = new vector<int>[pointNum];
	ifstream infile;
	infile.open("C:\\Users\\Administrator\\Desktop\\pj2\\real-datasets\\bitcoinotc\\soc-sign-bitcoinotc.txt", ios::in);
	long long c,d;
	int a, b;
	while (!infile.eof()) {
		infile >> a >> b>>c>>d;
		G[a].push_back(b);
		G[b].push_back(a);
	}
}

void switchHeap(int pos1, int pos2) {
	int p1 = maxHeap[pos1];
	int p2 = maxHeap[pos2];
	heapPos[p1] = pos2;
	heapPos[p2] = pos1;
	maxHeap[pos1] = p2;
	maxHeap[pos2] = p1;
}

void initHeap(int pos) {
	int rchild = (pos + 1) * 2;
	int lchild = rchild - 1;
	int maxPos = pos;
	if (rchild<=heapLast&&validCircle[maxHeap[rchild]]>validCircle[maxHeap[maxPos]]) {
		maxPos = rchild;
	}
	if (lchild<=heapLast&&validCircle[maxHeap[lchild]]>validCircle[maxHeap[maxPos]]) {
		maxPos = lchild;
	}
	if (maxPos != pos) {
		switchHeap(maxPos, pos);
		initHeap(maxPos);
	}
}

void initData() {
	maxHeap = new int[pointNum];
	heapPos = new int[pointNum];
	heapLast = pointNum - 1;
	validCircle = new int[pointNum];
	bool *ifVisited = new bool[pointNum];
	Nk = new vector<int>[pointNum];
	vector<int> visited;
	for (int i = 0; i < pointNum; i++) {
		ifVisited[i] = false;
		validCircle[i] = 0;
		maxHeap[i] = i;
		heapPos[i] = i;
	}
	for (int i = 0; i < pointNum; i++) {
		ifVisited[i] = true;
		Nk[i].push_back(i);
		visited.push_back(i);
		queue<tuple2> q;
		while (!q.empty()) {
			q.pop();
		}
		q.push(tuple2(i, 0));
		while (q.size() != 0) {
			tuple2 cur = q.front();
			q.pop();
			if (cur.b >= k) {
				break;
			}
			int curPoint = cur.a;
			int curFloor = cur.b + 1;
			vector<int>::iterator it;
			for (it = G[curPoint].begin(); it != G[curPoint].end(); it++) {
				if (ifVisited[*it] == true) {
					continue;
				}
				ifVisited[*it] = true;
				q.push(tuple2(*it, curFloor));
				visited.push_back(*it);
				Nk[i].push_back(*it);
			}
		}
		vector<int>::iterator it;
		for (it = visited.begin(); it != visited.end(); it++) {
			ifVisited[*it] = false;
		}
		visited.clear();
	}
}

void calcW() {
	for (int i=0; i < pointNum; i++) {
		//cout << Nk[i].size() << endl;
		for (int j = 0; j < Nk[i].size()-1; j++) {
			int near1 = Nk[i][j];
			for (int k = j + 1; k < Nk[i].size(); k++) {
				int near2 = Nk[i][k];
				for (int x = 0; x < Nk[near1].size(); x++) {
					if (Nk[near1][x] == near2) {
						validCircle[i]++;
						break;
					}
				}
			}
		}
	}
	for (int r = (pointNum + 1) / 2 - 1; r > 0; r--) {
		initHeap(r);
	}
}

void changeDown(int pos) {
	if (pos<0 || pos>heapLast) {
		return;
	}
	int rchild = (pos + 1) * 2;
	int lchild = rchild - 1;
	int maxPos = pos;
	if (rchild <= heapLast && validCircle[maxHeap[rchild]]>validCircle[maxHeap[maxPos]]) {
		maxPos = rchild;
	}
	if (lchild <= heapLast && validCircle[maxHeap[lchild]]>validCircle[maxHeap[maxPos]]) {
		maxPos = lchild;
	}
	if (maxPos != pos) {
		switchHeap(maxPos, pos);
		changeDown(maxPos);
	}
}

void changeUp(int pos) {
	if (pos<0 && pos>heapLast) {
		return;
	}
	int parent = (pos + 1) / 2 - 1;
	int pCur = maxHeap[pos];
	if (parent >= 0 && parent <= heapLast) {
		int pPar = maxHeap[parent];
		if (validCircle[pPar]<validCircle[pCur]) {
			switchHeap(parent, pos);
			changeUp(parent);
		}
	}
}

void changePos(int pos) {
	if (pos<0 && pos>heapLast) {
		return;
	}
	int rchild = (pos + 1) * 2;
	int lchild = rchild - 1;
	int parent = (pos + 1) / 2 - 1;
	int pCur = maxHeap[pos];
	if (parent >= 0 && parent <= heapLast) {
		int pPar = maxHeap[parent];
		if (validCircle[pPar]<validCircle[pCur]) {
			switchHeap(parent, pos);
			changeUp(parent);
			return;
		}
	}
	int maxPos = pos;
	if (rchild <= heapLast && validCircle[maxHeap[rchild]]>validCircle[maxHeap[maxPos]]) {
		maxPos = rchild;
	}
	if (lchild <= heapLast && validCircle[maxHeap[lchild]]>validCircle[maxHeap[maxPos]]) {
		maxPos = lchild;
	}
	if (maxPos != pos) {
		switchHeap(maxPos, pos);
		changeDown(maxPos);
	}
}

void delPoint(int point) {
	int pos = heapPos[point];
	if (pos>heapLast) {
		return;
	}
	if (heapLast != pos) {
		int pointLast = maxHeap[heapLast];
		heapLast--;
		maxHeap[pos] = pointLast;
		heapPos[pointLast] = pos;
		changePos(pos);
	}
	else {
		heapLast--;
	}
}

int getMinPoint() {
	if (heapLast == -1) {
		return -1;
	}
	int res = maxHeap[0];
	delPoint(res);
	return res;
}

int run() {
	for (int i = 0; i < need; i++) {
		resultSet.push_back(getMinPoint());
	}

	

	return 0;
}


int main() {
	loadG();
	initData();
	calcW();
	run();
	int x;
	cin >> x;
	return 0;
}