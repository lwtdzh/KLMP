//#include"BK.h"
//#include<fstream>
//#include<ctime>
//#include<stdlib.h>
//#include<queue>
//#include"TOOLS.h"
//using namespace std;
//
//vector<int> *Nk;
//int pointNum =5000;//7605
//vector<int> *G;
//int k = 2;
//bool **GkHopSupplement;
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
//void loadG() {
//	G = new vector<int>[pointNum];
//	ifstream infile;
//	infile.open("C:\\Users\\Administrator\\Desktop\\pj2\\dataset\\5000-500.txt", ios::in);
//	char c[200];
//	int a, b;
//	while (!infile.eof()) {
//		infile >> a >> b ;
//		G[a].push_back(b);
//		G[b].push_back(a);
//	}
//}
//
//void initData() {
//	GkHopSupplement = new bool*[pointNum];
//	Nk = new vector<int>[pointNum];
//	bool *ifVisited = new bool[pointNum];
//	vector<int> visited;
//	for (int i = 0; i < pointNum; i++) {
//		ifVisited[i] = false;
//		GkHopSupplement[i] = new bool[pointNum];
//		for (int j = 0; j < pointNum; j++) {
//			GkHopSupplement[i][j] = true;
//		}
//	}
//	//constructNk
//	for (int i = 0; i < pointNum; i++) {
//		ifVisited[i] = true;
//		Nk[i].push_back(i);
//		visited.push_back(i);
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
//	//construct GkHopSupp
//	for (int i = 0; i < pointNum ; i++) {
//		vector<int>::iterator it;
//		for (it = Nk[i].begin(); it != Nk[i].end(); it++) {
//			GkHopSupplement[i][*it] = false;
//		}
//	}
//}
//
//int run() {
//	return startBK(GkHopSupplement, pointNum);
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
//	return 0;
//}