#pragma once
#include<iostream>
#include<vector>
using namespace std;

template < class T >
void clearVector(vector< T >& vt)
{
	vector< T > vtTemp;
	vtTemp.swap(vt);
}

int getArrayLen(int *a) {
	return (sizeof(a) / sizeof(a[0]));
}

int* findInterSection(int *a1, int *a2) {
	int maxLen = (a1[0] > a2[0]) ? a1[0] : a2[0];
	int *res = new int[maxLen + 1];
	res[0] = 0;
	for (int i = 1; i <= a1[0]; i++) {
		for (int j = 1; j <= a2[0]; j++) {
			if (a1[i] == a2[j]) {
				int curPos = res[0] + 1;
				res[0]++;
				res[curPos] = a1[i];
				break;
			}
		}
	}
	return res;
}

void findInterSectionInside(vector<int> &a1, int *a2) {
	int lenA1 = a1.size();
	int maxLen = (lenA1 > a2[0]) ? lenA1 : a2[0];
	int *tmpStorage = new int[maxLen + 1];
	tmpStorage[0] = 0;
	vector<int>::iterator it;
	for (it = a1.begin(); it != a1.end(); it++) {
		int curA1 = *it;
		for (int i = 1; i <= a2[0]; i++) {
			if (a2[i] == curA1) {
				tmpStorage[0]++;
				tmpStorage[tmpStorage[0]] = curA1;
			}
		}
	}
	a1.clear();
	for (int i = 1; i <= tmpStorage[0]; i++) {
		a1.push_back(tmpStorage[i]);
	}
	delete[] tmpStorage;
}

int* findInterSection(vector<int> &a1, int *a2) {
	int lenA1 = a1.size();
	int maxLen = (lenA1 > a2[0]) ? lenA1 : a2[0];
	int *tmpStorage = new int[maxLen + 1];
	tmpStorage[0] = 0;
	vector<int>::iterator it;
	for (it = a1.begin(); it != a1.end(); it++) {
		int curA1 = *it;
		for (int i = 1; i <= a2[0]; i++) {
			if (a2[i] == curA1) {
				tmpStorage[0]++;
				tmpStorage[tmpStorage[0]] = curA1;
			}
		}
	}
	return tmpStorage;
}

//ignore duplicated items.
int *findUnion(int *a1, int *a2) {
	int maxLen = a1[0] + a2[0];
	int *res = new int[maxLen + 1];
	res[0] = maxLen;
	int curPos = 1;
	for (int i = 1; i <= a1[0]; i++) {
		res[curPos] = a1[i];
		curPos++;
	}
	for (int i = 1; i <= a2[0]; i++) {
		res[curPos] = a2[i];
		curPos++;
	}
	return res;
}

int *addElementForNew(int *a, int b) {
	int *res = new int[a[0] + 2];
	memcpy(res, a, sizeof(a[0])*(a[0] + 1));
	res[0] = a[0] + 1;
	res[a[0] + 1] = b;
	return res;
}

void subElementInside(int *a, int b) {
	int len = a[0];
	int pos = -1;
	for (int i = 1; i <= len; i++) {
		if (a[i] == b) {
			pos = i;
			break;
		}
	}
	if (pos != -1) {
		a[0]--;
		for (int i = pos + 1; i <= len; i++) {
			a[i - 1] = a[i];
		}
	}
}

void addElementInside(int *a, int b) {
	int len = a[0];
	int *res = new int[a[0] + 2];
	memcpy(res, a, sizeof(a[0])*(a[0] + 1));
	res[0] = a[0] + 1;
	res[a[0] + 1] = b;
	delete[] a;
	a = res;
}

bool isContain(int *a, int b) {
	int len = a[0];
	for (int i = 1; i <= len; i++) {
		if (a[i] == b) {
			return true;
		}
	}
	return false;
}

bool isContainInNeighbor(int *a, int b, int **N) {
	int len = a[0];
	for (int i = 1; i <= len; i++) {
		int curPoint = a[i];
		for (int j = 1; j <= N[curPoint][0]; j++) {
			if (b == N[curPoint][j]) {
				return true;
			}
		}
	}
	return false;
}

void copyX(vector<int> &src, vector<int> &des) {
	vector<int>::iterator it;
	for (it = src.begin(); it != src.end(); it++) {
		des.push_back(*it);
	}
}

//R[0]==the length of array.
void BK(int *R, int *P, int *X, int **N, int &maxSize) {
	if (P[0] == 0 && X[0] == 0) {
		if (R[0] > maxSize) {
			maxSize = R[0];
		}
		return;
	}
	int Xnumber = X[0];
	int Pnumber = P[0];
	int *pivot = findInterSection(X, P);
	int len = P[0];
	for (int i = len; i >=1; i--) {
		if (isContainInNeighbor(pivot, P[i], N)) {
			continue;
		}
		//int *Rcp = addElementForNew(R, P[i]);
		R[0]++;
		R[R[0]] = P[i];
		int *Pcp = findInterSection(P, N[P[i]]);
		//vector<int> Xcp;
		//Xcp.clear();
		//copyX(X, Xcp);
		//findInterSectionInside(Xcp, N[P[i]]);
		int *Xcp = findInterSection(X, N[P[i]]);
		BK(R, Pcp, Xcp, N, maxSize);
		delete[] Pcp;
		delete[] Xcp;
		R[0]--;
		P[0]--;
		X[0]++;
		X[X[0]] = P[i];
	}
	delete[] pivot;
	X[0] = Xnumber;
	P[0] = Pnumber;
}

int startBK(bool **G, int pointNum) {
	int res = 0;
	int **N = new int*[pointNum];
	for (int i = 0; i < pointNum; i++) {
		N[i] = new int[pointNum];
		N[i][0] = 0;
	}
	for (int i = 0; i < pointNum - 1; i++) {
		for (int j = i + 1; j < pointNum; j++) {
			if (G[i][j] == true) {
				N[i][N[i][0] + 1] = j;
				N[j][N[j][0] + 1] = i;
				N[i][0]++;
				N[j][0]++;
			}
		}
	}
	int *iniR = new int[pointNum+1];
	int *iniX = new int[pointNum + 1];
	iniR[0] = 0;
	int *iniP = new int[pointNum + 1];
	iniP[0] = pointNum;
	iniX[0] = 0;
	for (int i = 1; i <= pointNum; i++) {
		iniP[i] = i - 1;
	}
	BK(iniR, iniP, iniX, N, res);
	delete[] iniP;
	delete[] iniR;
	delete[] iniX;
	for (int i = 0; i < pointNum; i++) {
		delete[] N[i];
	}
	delete[] N;
	return res;
}
