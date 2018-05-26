//#include<iostream>
//#include<fstream>
//#include<vector>
//#include<queue>
//#include<time.h>
//#include"TOOLS.h"
//#include<stdlib.h>
//using namespace std;
//
//class tuple2 {
//public:
//	tuple2(int a, int b) {
//		this->a = a;
//		this->b = b;
//	}
//	int a;
//	int b;
//};
//
//int k = 2;
//vector<int> *Nk;
//int pointNum =10000;//7605
//vector<int> *G;
//bool *pointValid;
//int *validCircle;
//int *minHeap;
//int *heapPos;
//int heapLast;
//
//void loadG() {
//	G = new vector<int>[pointNum];
//	ifstream infile;
//	infile.open("C:\\Users\\Administrator\\Desktop\\pj2\\dataset\\10000-15.txt", ios::in);
//	char c[200];
//	int a, b;
//	while (!infile.eof()) {
//		infile >> a >> b >> c >> c;
//		G[a].push_back(b);
//		G[b].push_back(a);
//	}
//	/*int e = 0;
//	for (int i = 0; i < pointNum-1; i++) {
//		for (int j = 1+1; j < pointNum; j++) {
//			if (rand() / double(RAND_MAX)>=0.015) {
//				continue;
//			}
//			e++;
//			G[i].push_back(j);
//			G[j].push_back(i);
//		}
//	}
//	cout << "e:" << e << endl;*/
//}
//
//void switchHeap(int pos1, int pos2) {
//	int p1 = minHeap[pos1];
//	int p2 = minHeap[pos2];
//	heapPos[p1] = pos2;
//	heapPos[p2] = pos1;
//	minHeap[pos1] = p2;
//	minHeap[pos2] = p1;
//}
//
//void initHeap(int pos) {
//	int rchild = (pos + 1) * 2;
//	int lchild = rchild - 1;
//	int maxPos = pos;
//	if (rchild<pointNum&&validCircle[minHeap[rchild]]<validCircle[minHeap[maxPos]]) {
//		maxPos = rchild;
//	}
//	if (lchild<pointNum&&validCircle[minHeap[lchild]]<validCircle[minHeap[maxPos]]) {
//		maxPos = lchild;
//	}
//	if (maxPos != pos) {
//		switchHeap(maxPos, pos);
//		initHeap(maxPos);
//	}
//}
//
//void initData() {
//	construct Nk,validCircle
//	Nk = new vector<int>[pointNum];
//	validCircle = new int[pointNum];
//	pointValid = new bool[pointNum];
//	minHeap = new int[pointNum];
//	heapPos = new int[pointNum];
//	heapLast = pointNum - 1;
//	bool *ifVisited = new bool[pointNum];
//	vector<int> visited;
//	visited.clear();
//	for (int i = 0; i < pointNum; i++) {
//		ifVisited[i] = false;
//		validCircle[i] = 1;
//		pointValid[i] = true;
//		minHeap[i] = i;
//		heapPos[i] = i;
//	}
//	construct Nk
//	for (int i = 0; i < pointNum; i++) {
//		ifVisited[i] = true;
//		Nk[i].push_back(i);
//		queue<tuple2> q;
//		while (!q.empty()) {
//			q.pop();
//		}
//		q.push(tuple2(i, 0));
//		while (q.size() != 0) {
//			tuple2 cur = q.front();
//			q.pop();
//			if (cur.b >= k) {
//				break;
//			}
//			int curPoint = cur.a;
//			int curFloor = cur.b + 1;
//			vector<int>::iterator it;
//			for (it = G[curPoint].begin(); it != G[curPoint].end(); it++) {
//				if (ifVisited[*it] == true) {
//					continue;
//				}
//				ifVisited[*it] = true;
//				q.push(tuple2(*it, curFloor));
//				visited.push_back(*it);
//				Nk[i].push_back(*it);
//			}
//		}
//		vector<int>::iterator it;
//		for (it = visited.begin(); it != visited.end(); it++) {
//			ifVisited[*it] = false;
//		}
//		visited.clear();
//	}
//	construct validCircle
//	for (int i = 0; i < pointNum; i++) {
//		validCircle[i] = getNear1Number(Nk, i);
//	}
//	init heap
//	for (int i = (pointNum + 1) / 2 - 1; i > 0; i--) {
//		initHeap(i);
//	}
//	delete[] ifVisited;
//}
//
//void changeDown(int pos) {
//	if (pos<0 || pos>heapLast) {
//		return;
//	}
//	int rchild = (pos + 1) * 2;
//	int lchild = rchild - 1;
//	int maxPos = pos;
//	if (rchild <= heapLast && validCircle[minHeap[rchild]]<validCircle[minHeap[maxPos]]) {
//		maxPos = rchild;
//	}
//	if (lchild <= heapLast && validCircle[minHeap[lchild]]<validCircle[minHeap[maxPos]]) {
//		maxPos = lchild;
//	}
//	if (maxPos != pos) {
//		switchHeap(maxPos, pos);
//		changeDown(maxPos);
//	}
//}
//
//void changeUp(int pos) {
//	if (pos<0 && pos>heapLast) {
//		return;
//	}
//	int parent = (pos + 1) / 2 - 1;
//	int pCur = minHeap[pos];
//	if (parent >= 0 && parent <= heapLast) {
//		int pPar = minHeap[parent];
//		if (validCircle[pPar]>validCircle[pCur]) {
//			switchHeap(parent, pos);
//			changeUp(parent);
//		}
//	}
//}
//
//void changePos(int pos) {
//	if (pos<0 && pos>heapLast) {
//		return;
//	}
//	int rchild = (pos + 1) * 2;
//	int lchild = rchild - 1;
//	int parent = (pos + 1) / 2 - 1;
//	int pCur = minHeap[pos];
//	if (parent >= 0 && parent <= heapLast) {
//		int pPar = minHeap[parent];
//		if (validCircle[pPar]>validCircle[pCur]) {
//			switchHeap(parent, pos);
//			changeUp(parent);
//			return;
//		}
//	}
//	int maxPos = pos;
//	if (rchild <= heapLast && validCircle[minHeap[rchild]]<validCircle[minHeap[maxPos]]) {
//		maxPos = rchild;
//	}
//	if (lchild <= heapLast && validCircle[minHeap[lchild]]<validCircle[minHeap[maxPos]]) {
//		maxPos = lchild;
//	}
//	if (maxPos != pos) {
//		switchHeap(maxPos, pos);
//		changeDown(maxPos);
//	}
//}
//
//void delPoint(int point) {
//	pointValid[point] = false;
//	int pos = heapPos[point];
//	if (pos>heapLast) {
//		return;
//	}
//	if (heapLast != pos) {
//		int pointLast = minHeap[heapLast];
//		heapLast--;
//		minHeap[pos] = pointLast;
//		heapPos[pointLast] = pos;
//		changePos(pos);
//	}
//	else {
//		heapLast--;
//	}
//}
//
//int getMinPoint() {
//	if (heapLast == -1) {
//		return -1;
//	}
//	int res = minHeap[0];
//	delPoint(res);
//	return res;
//}
//
//void refreshNkBySubmit(int src, int tar) {
//	vector<int>::iterator it;
//	for (it = Nk[tar].begin(); it != Nk[tar].end(); it++) {
//		if (*it == src) {
//			Nk[tar].erase(it);
//			break;
//		}
//	}
//}
//
//int run() {
//	int res = 0;
//	int curPoint = getMinPoint();
//	while (curPoint != -1) {
//		res++;
//		vector<int>::iterator it;
//		for (it = Nk[curPoint].begin(); it != Nk[curPoint].end(); it++) {
//			if (pointValid[*it] == false) {
//				continue;
//			}
//			delPoint(*it);
//			vector<int>::iterator it2;
//			for (it2 = Nk[*it].begin(); it2 != Nk[*it].end(); it2++) {
//				if (pointValid[*it2] == false) {
//					continue;
//				}
//				refreshNkBySubmit(*it, *it2);
//				validCircle[*it2] = getNear1Number(Nk, *it2);
//				changePos(heapPos[*it2]);
//			}
//		}
//		curPoint = getMinPoint();
//	}
//	return res;
//}
//
//int main() {
//	loadG();
//	initData();
//	int start = clock();
//	cout << run() << endl;
//	int end = clock();
//	cout << "Time:" << (double)(end - start) / CLOCKS_PER_SEC << endl;
//	int x;
//	cin >> x;
//	delete[] Nk;
//	delete[] G;
//	delete[] pointValid;
//	delete[] validCircle;
//	delete[] minHeap;
//	delete[] heapPos;
//	return 0;
//}
