#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

int main (int argc, char* argv[]){
	string line;
	string l1,l2,l3;
	int cntline=1;
	ifstream infile("problem1.in");
	if(infile.is_open()){
		while(getline(infile,line)){
			switch(cntline){
				case 1:
					l1=line;
					break;
				case 2:
					l2=line;
					break;
				case 3:
					l3=line;
					break;
			}
			cntline++;
		}
		infile.close();
		int level = std::stoi(l1);
		cout << argv[1];
		cout << "Max level: " << level <<'\n';
		cout << "Start: " << l2 << '\n';
		cout << "Goal: " << l3 << '\n';

	}
	else cout << "Unable to open file";

	return 0;
}