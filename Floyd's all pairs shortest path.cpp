#include<iostream>
#include<fstream>
#include<string>
using namespace std;

int main(){
	ifstream fin;
	ofstream fout;
	fin.open("input.txt");
	fout.open("output.txt");
	int A[6][6][6], R[6][6][6], start, end, num, path[6] = { 0 };
	string input;
	for (int i = 1; i < 6; i++){
		for (int j = 1; j < 6; j++){
			fin >> num;
			if (num == 0 && i != j)
				A[0][i][j] = 99999;
			else
				A[0][i][j] = num;
		}
	}
	
	for (int i = 1; i < 6; i++){
		for (int j = 1; j < 6; j++){
			if (i == j || A[0][i][j] == 99999)
				R[0][i][j] = 0;
			else
				R[0][i][j] = i;
		}
	}

	fin >> start;
	fin >> end;
	
	for (int k = 1; k < 6; k++){
		for (int i = 1; i < 6; i++){
			for (int j = 1; j < 6; j++){
				if (i == j)
					A[k][i][j] = 0;
				else if (i == k || j == k)
					A[k][i][j] = A[k - 1][i][j];
				else{
					if ((A[k - 1][i][k] + A[k - 1][k][j]) < A[k - 1][i][j])
						A[k][i][j] = A[k - 1][i][k] + A[k - 1][k][j];
					else
						A[k][i][j] = A[k - 1][i][j];
				}

				if (A[k - 1][i][j] <= A[k - 1][i][k] + A[k - 1][k][j])
					R[k][i][j] = R[k - 1][i][j];
				else if (A[k - 1][i][j] > A[k - 1][i][k] + A[k - 1][k][j])
					R[k][i][j] = R[k - 1][k][j];
			}
		}
	}
	/*
	for (int i = 1; i < 6; i++){
		for (int j = 1; j < 6; j++){
			cout<<R[0][i][j];
		}
		cout << endl;
	}
	*/
	path[0] = start;
	int clk=1,now=start;
	while (1){
		if (path[clk - 1] == R[5][now][end])
			break;
		else{
			path[clk] = R[5][now][end];
			now = R[5][now][end];
			clk++;
		}
	}
	path[clk] = end;
	for (int x = 0; x < 6; x++){
		if (path[x] == 0)
			break;
		else if (path[x] == 1)
			fout << "v1"<<' ';
		else if (path[x] == 2)
			fout << "v2" << ' ';
		else if (path[x] == 3)
			fout << "v3" << ' ';
		else if (path[x] == 4)
			fout << "v4" << ' ';
		else if (path[x] == 5)
			fout << "v5" << ' ';

	}
	fout << A[5][start][end];
	fin.close();
	fout.close();
}