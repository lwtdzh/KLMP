#pragma once
#include<iostream>
#include<vector>
#include<map>
#include"BK.h"
using namespace std;


bool ifInVector(vector<int> &v, int tar) {
	vector<int>::iterator it;
	for (it = v.begin(); it != v.end(); it++) {
		if (*it == tar) {
			return true;
		}
	}
	return false;
}

int getNear1Number(vector<int> *Nk, int k) {
	map<int, int> map;
	int len = 0;
	vector<int>::iterator it;
	for (it = Nk[k].begin(); it != Nk[k].end(); it++) {
		map[*it] = len;
		len++;
	}
	bool **tarG = new bool*[len];
	for (int i = 0; i < len; i++) {
		tarG[i] = new bool[len];
	}
	for (int i = 0; i < len - 1; i++) {
		for (int j = i + 1; j < len; j++) {
			int a1 = map[i];
			int a2 = map[j];
			if (ifInVector(Nk[a1], a2) == true) {
				tarG[a1][a2] = tarG[a2][a1] = false;
			}
			else {
				tarG[a1][a2] = tarG[a2][a1] = true;
			}
		}
	}
	int res = startBK(tarG, len);
	for (int i = 0; i < len; i++) {
		delete[] tarG[i];
	}
	delete[] tarG;
	return res;
}