#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
#include<time.h>
#include"TOOLS.h"
using namespace std;


int main(){
	int pointNum=100;
	bool **G=new bool*[100];
	for(int i=0;i<100;i++){
		G[i]=new bool[100];
	}
	for (int i = 0; i < pointNum-1; i++) {
		for (int j = i+1; j < pointNum; j++) {
			if (i == 2 || j == 2||i==7||j==7) {
				G[i][j]=G[j][i]=false;
			}
			G[i][j]=G[j][i]=true;
		}
	}
	int s=clock();
	startBK(G,100);
	int e=clock();
	cout << "Time:" << (double)(e - s) / CLOCKS_PER_SEC << endl;
	return 0;
}
