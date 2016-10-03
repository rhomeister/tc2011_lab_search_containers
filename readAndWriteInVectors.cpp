#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

int main (int argc, char* argv[]){
	int maxHeight;

	string init,goal;

	int container=0;

	vector<char>temp;
	vector<vector <char> > initState;
	vector<vector <char> > goalState;

	cin >> maxHeight;
	cout << "Max Height: " << maxHeight <<'\n';
	getline(cin,init);//to catch the \n char in the first line
	getline(cin,init);
	getline(cin,goal);
	cout << "Start: " << init << '\n';
	cout << "Goal: " << goal << "\n\n";
	//Read to specify initial state
	cout << "Init State\n";
	for(int i =0;i < init.length(); i++){
		if(init[i]=='('){ //new container
			temp.clear();
			cout << "Initiate container " << container << '\n';
			cout << '[';
		}else if(init[i]==')'){//finish the container
			initState.push_back(temp);
			cout << "]\nFinishing container " << container << '\n';
			container++;
		}else if(init[i]>=65 && init[i]<=90){//char from A to Z
			temp.push_back(init[i]);
			cout << init[i] << ' ';
		}
	}
	temp.clear();
	container = 0;
	//Read to specify goal state
	cout << "Goal State\n";
	for(int i =0;i < goal.length(); i++){
		if(goal[i]=='X'){ //Don't care
			temp.clear();
			goalState.push_back(temp);
			cout << "Don't care container: " << container <<'\n';
			container++;
		}else if(goal[i]=='('){ //new container
			temp.clear();
			cout << "Initiate container " << container << '\n';
			cout << '[';
		}else if(goal[i]==')'){//finish the container
			goalState.push_back(temp);
			cout << "]\nFinishing container " << container << '\n';
			container++;
		}else if(goal[i]>=65 && goal[i]<=90){//char from A to Z
			temp.push_back(goal[i]);
			cout << goal[i] << ' ';
		}
	}
}