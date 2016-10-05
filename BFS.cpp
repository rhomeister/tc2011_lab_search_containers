#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>

#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <list>
#include <utility>

/*
	BFS -> frontier = queue
*/

using namespace std; // std:: is implied.

struct node{
	//initial = [[a], [b], [c]]; goal = [[b, a], [x], [x]];   **bottom to top
	std::vector<stack <char> > state;

	struct node *parent;

	//0 = (0,1); 1 = (0,2); 2 = (1,0); 
	//3 = (1,2); 4 = (2,0); 5 = (2, 1);
	std::pair<int,int>  action;
};

int isGoal(vector<stack <char> > actual, vector<stack <char> > goal)
{
	int i, j;
	int res = 1;

	for(i = 0; i < goal.size(); i++)
	{		
		if( goal[i].size() > 0 && goal[i].top() == 'X')
		{
			goal[i].pop();
			continue;
		}
		else if(actual[i].size() != goal[i].size())
		{			
			return 0;				
		}
		while( goal[i].size() > 0)
		{
			if(actual[i].top() != goal[i].top())
			{
				return 0;
			}

			actual[i].pop();
			goal[i].pop();
		}
	}
	return res;
}

int expandNode(struct node **child, struct node *parent, pair<int,int> action, int limit)
{	
	char aux;

	//Only expand valid nodes
	if( !(parent->state[action.first].empty()) && (parent->state[action.second].size() < limit))
	{		
		(*child) = new node;

		(*child)->parent = parent;
		(*child)->state = parent->state;
		(*child)->action = action;

		//Adding element to new continer
		aux = (*child)->state[action.first].top();
		(*child)->state[action.second].push( aux );

		//Removing element from origin container
		(*child)->state[action.first].pop();

		return 1;
	}
	return 0;

}

int main(int arg, char** argv)
{
	char box;
	int fin = 0;
	int i, j, maxHeight;

	string init,goal; //auxiliar buffers

	stack<char>temp;
	vector<stack <char> > goalState;
	vector<stack <char> > debugState; //for debug purpose
	stack<pair <int, int> > solution;
	pair<int,int>  action;

	queue <struct node *> frontier;
	set <struct node *> explored;
	set<struct node *>::iterator it;
	
	struct node *root = new node;
	struct node *actualNode = new node;
	struct node *childNode = new node;

	cin >> maxHeight;
	getline(cin,init);//to catch the \n char in the first line
	getline(cin,init);
	getline(cin,goal); 

	//Read to specify initial state
	if(root != NULL){
		for(int k =0;k < init.length(); k++){
			if(init[k]=='('){ //new container
				while(!temp.empty())//to empty the stack
					temp.pop();
			}else if(init[k]==')'){//finish the container
				root->state.push_back(temp);
			}else if(init[k]>=65 && init[k]<=90){//char from A to Z
				temp.push(init[k]);
			}
		}
		while(!temp.empty()) //to empty the stack
				temp.pop();

		root->parent = NULL;
	}
	/*
	debugState = root->state;
	cout << "debug part: inputs\n";
	cout << "init State\n";
	for(int k=0;k<debugState.size();k++){
		cout << "container " << k << '\n';
		while(!debugState[k].empty()){
			cout<<debugState[k].top()<<' ';
			debugState[k].pop();
		}
		cout << '\n';
	}*/

	//Read to specify goal state
	for(int k =0;k < goal.length(); k++){
		if(goal[k]=='X'){ //Don't care
			temp.push(goal[k]);
			goalState.push_back(temp);
			while(!temp.empty()) //to empty the stack
				temp.pop();
		}else if(goal[k]=='(' || goal[k]==';'){ //new container
			while(!temp.empty()) //to empty the stack
				temp.pop();
		}else if(goal[k]==')'){//finish the container
			goalState.push_back(temp);
		}else if(goal[k]>=65 && goal[k]<=90){//char from A to Z
			temp.push(goal[k]);
		}
	}

	while(!temp.empty()) //to empty the stack
		temp.pop();
	/*
	debugState = goalState;
	cout << "goal State\n";
	for(int k=0;k<debugState.size();k++){
		cout << "container " << k << '\n';
		while(!debugState[k].empty()){
			cout<<debugState[k].top()<<' ';
			debugState[k].pop();
		}
		cout << '\n';
	}*/

	isGoal(root->state, goalState);

	//Step 1: Initialize the frontier using the initial state
	frontier.push(root);

	//Step 2: Initialize the exprored set to be empty
	explored.clear();
	do{
		//Failure if the frontier is empty
		if(frontier.empty())
		{
			cout << "Frontier empty" << endl;
			return -1;			
		}

		//Remove leaf node from frontier
		actualNode = frontier.front();
		frontier.pop();
		
		//Add the node to the explored set
		explored.insert(actualNode);

		//Expand the node 
		for(i = 0; i < goalState.size(); i++)
		{
			for(j = 0; j < goalState.size(); j++)
			{
				if(i != j)		
				{				
					action = make_pair(i, j); 					
					if(expandNode(&childNode, actualNode, action, maxHeight) == 1)
					{
						//Add the resulting nodes to frontier
						//Only if they are not in frontier or explored*/

						it = explored.find(childNode);
						if(it == explored.end())
						{
							//Success if is the goal
							fin = isGoal(childNode->state, goalState);
							
							if(fin == 1)
							{
								actualNode = childNode;
								while(actualNode->parent != NULL)
								{
									solution.push(actualNode->action);
									actualNode = actualNode->parent;
								}

								while(!(solution.empty()) )
								{
									cout << "(" << solution.top().first << "," << solution.top().second << ")  " << endl;
									solution.pop();
								}
								return 1;
							}
							frontier.push(childNode);
						}
					}
				}
			}
		}
	}while(frontier.size() > 0 && fin == 0);

	cout << "No solution found" << endl;

	return 0;
}
