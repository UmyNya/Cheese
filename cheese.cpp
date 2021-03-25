/*
note:

1.initialze the variables

2.determine what type of each hole.
if z<=r only,it's connected to the bottom; store it in to a array startPointIndex[] to visit it more convenient. and numOfStaetPoint++. Besides, it is the start of our path, so isKnown->known, to avoid visit again when findPath()
if z>=h-r only, connects with the top 
if z<=r&&z>=h-r£¬it can go through the cheese. Thus, give the answer "Yes" directly.
if r<z<h-r, in the middle

3.find the path start from each hole in startPointIndex.
visit each unknown hole, and check if they are connected.
if connected{//by DPS
	if the new hole is the type that can go to the top ,retrun 1 .give the answer "Yes" directly.
	else find another new hole that connect with the new hole. if no other hole can be connected, return 0
}

4. cout the answer

5.By UmyNya £¨github)
*/

/*
example data
3
2 4 1
0 0 1
0 0 3
2 5 1
0 0 1
0 0 4
2 5 2
0 0 2
2 0 4

*/

#include<iostream>
using namespace std;

int T;//the number of groups of data
int n;//the number of hole
int h;// height of cheese
int r;//radius of holes
int datas[1000][5] = { 0 };//row:n<=1000;	col:0~2:x,y,z 3:isKonwn :0->unknown,1->known		4 type of holes: 0 for middle/can't go to anywhere, 1 for start/can get to the bottom, 2 for end /can get to the top
int startPointIndex[1000];//store the index of start holes in datas[][];
int numOfStartHole = 0;//how many start holes are stored in startPointIndex[]

int whichType();//define the type of holes
bool findPath();//fine a path from bottom to top by DFS(Depth first search). if find the path we need, return 1; or else ,return 0
bool isConnected(int);//find a unknown(haven't been in a path) hole one by one. if it can connect with the current hole: if the unkown one can get to the top, return 1; else find the next unknown hole that can connect to it. if no hole can connect to it, return 0;

int main() {
	cin >> T;
	for (int t = 0; t < T; t++) {
		//initialize
		int isYes = 0;//a sign to decide the answer is Yes or No.

		cin >> n >> h >> r;
		for (int count = 0; count < n; count++) {
			cin >> datas[count][0] >> datas[count][1] >> datas[count][2];
			datas[count][3] = 0;
			datas[count][4] = 0;
		}

		//define th type of holes
		isYes=whichType();

		if (isYes == 0) {
			isYes=findPath();//find a path to go through the cheese
		}

		//cout the answer
		if (isYes==1) {
			cout << "Yes\n";
		}
		else {
			cout << "No\n";
		}
	}
}

int whichType() {
	int possible = -1;//-1:impossible to find the way,for no hole going through the top (if no hole go through the bottom,numOfStart==0,then it will end quickly. Thus, just pay attention to the end hole.); 0 for maybe we can find the path ; 1 for there exists the path
	for (int count = 0; count < n; count++) {
		if (datas[count][2] <= r) {//can visit bottom
			datas[count][3] = 1;
			datas[count][4] = 1;
			startPointIndex[numOfStartHole] = count;
			numOfStartHole++;
		}
		if (datas[count][2] >= h - r) {
			
			if (datas[count][4] == 1) {//go through the cheese
				return 1;//2r>=h
			}
			else {
				possible = 0;
				datas[count][4] = 2;//can visit top
			}
		}
	}
	return possible;//middle
}

bool findPath() {
	for (int count = 0; count < numOfStartHole; count++) {//try to start from each hole that connects to the bottom
		bool temp=isConnected(count);
		if (temp == 1) {
			return 1;
		}
	}
	return 0;
}

bool isConnected(int count) {
	for (int count2 = 0; count2 < n; count2++) {
		if (datas[count2][3] == 0&&count2!=count) {//if the other hole is unknown(haven't been in any path

			//calculate teh square of the distance of two holes
			int distanceSquare = 0;
			for (int degree = 0; degree < 3; degree++) {
				distanceSquare += (datas[count][degree] - datas[count2][degree]) * (datas[count][degree] - datas[count2][degree]);
			}

			//if they are connected
			if (distanceSquare <= 4 * r * r) {
				if (datas[count2][4] == 2) {
					return 1;
				}
				else {
					datas[count2][3] = 1;//has been known
					datas[count2][4] = 1;//it can go to the bottom
					bool temp=isConnected(count2);
					if (temp == 1) {
						return 1;
					}
				}
			}		
		}
	}
	return 0;//there doesn't exsit another hole that can be connected, which means this path is fail to go through the theese
}