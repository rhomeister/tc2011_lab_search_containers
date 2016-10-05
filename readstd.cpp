#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

int main (int argc, char* argv[]){
	int maxlevel;
	string l1,l2,l3;
	char aux;

	cin >> maxlevel;
	getline(cin,l1);//to catch the \n char in the first line
	getline(cin,l2);
	getline(cin,l3);
	cout << "Max level " << maxlevel << '\n';
	cout << "Start: " << l2 << '\n';
	cout << "Goal: " << l3 << '\n';
}