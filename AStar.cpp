#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>

#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <list>
#include <utility>

/*
	A* -> frontier = priority queue
*/

using namespace std; // std:: is implied.

struct node{
	//initial = {{a}, {b}, {c}}; goal = {{b, a}, {x}, {x}};   **bottom to top
	std::vector<stack <char> > state;

	struct node *parent;

	//(0,1), (0,2), (1,0), (1,2), (2,0), (2, 1), etc.
	std::pair<int,int>  action; 

	int gCost;	
	int hCost;
};

bool operator<(const node& n1, const node& n2){
		return (n1.gCost + n1.hCost) > (n2.gCost + n2.hCost);
}

//Falta considerar contenedores vacios??
int isGoal(vector<stack <char> > actual, vector<stack <char> > goal)
{
	int i, j;
	int res = 1;

	for(i = 0; i < goal.size(); i++)
	{
		if(actual[i].size() != goal[i].size())
		{			
			return 0;				
		}
		while( goal[i].size() > 0)
		{
			if(goal[i].top() != 'X')
			{			
				if(actual[i].top() != goal[i].top())
				{
					return 0;
				}

				actual[i].pop();
				goal[i].pop();
			}
			else
			{
				goal[i].pop();
			}
		}
	}
	return res;
}

int heuristic(vector<stack <char> > actual, vector<stack <char> > goal)
{
	int i, j, dif;
	int s1, s2;
	int res = 0;

	for(i = 0; i < goal.size(); i++)
	{
		while( goal[i].size() > 0 && actual[i].size() > 0)
		{
			if(goal[i].top() != 'X')
			{		
				dif = actual[i].size() - goal[i].size();
				if( dif > 0 )	
				{
					while(dif > 0)
					{
						actual[i].pop();
						res++;
						dif--;
					}
				}	
				else if( dif < 0 )		
				{
					while(dif < 0)
					{
						goal[i].pop();
						res++;
						dif++;
					}
				}
				
				if(actual[i].top() != goal[i].top())
				{
					res++;
				}

				actual[i].pop();
				goal[i].pop();
			}
			else
			{
				goal[i].pop();
				do
				{
					actual[i].pop();
				}while(actual[i].size() > 0);

			}
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

		(*child)->gCost = parent->gCost + (1 + abs(action.first - action.second));

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
	stack<pair <int, int> > solution;
	pair<int,int>  action;

	priority_queue <struct node *> frontier;
	map < vector<stack <char> >, int > isInFrontier;
	map < vector<stack <char> >, int >::iterator itFrontier;

	set < vector<stack <char> > > explored;
	set < vector<stack <char> > >::iterator itExplored;
	
	struct node *root = new node;
	struct node *actualNode = new node;
	struct node *childNode = new node;

	cin >> maxHeight; 

	//Read to specify initial state
	if(root != NULL){
		for(int k =0;k < init.length(); k++){
			if(init[k]=='('){ //new container
				while(!temp.empty()) //to empty the temp stack
					temp.pop();
			}else if(init[k]==')'){//finish the container
				root->state.push_back(temp);
			}else if(init[k]>=65 && init[k]<=90){//char from A to Z
				temp.push(init[k]);
			}
		}
		while(!temp.empty()) //to empty the temp stack
			temp.pop();

		root->parent = NULL;
		root->gCost = 0;
	}

	//Read to specify goal state
	for(int k =0;k < goal.length(); k++){
		if(goal[k]=='X'){
			temp.push(goal[k]);
			goalState.push_back(temp);
		}else if(goal[k]=='(' || goal[k]==';'){ //new container
			while(!temp.empty()) //to empty the temp stack
				temp.pop();
		}else if(goal[k]==')'){//finish the container
			goalState.push_back(temp);
		}else if(goal[k]>=65 && goal[k]<=90){//char from A to Z
			temp.push(goal[k]);
		}
	}
	while(!temp.empty()) //to empty the temp stack
		temp.pop();

	root->hCost = heuristic(root->state, goalState);

	//Step 1: Initialize the frontier using the initial state
	frontier.push( root );
	isInFrontier.insert( map< vector<stack <char> >, int >::value_type(root->state, root->gCost + root->hCost) );

	//Step 2: Initialize the exprored set to be empty
	explored.clear();

	do{
		//Failure if the frontier is empty
		if(isInFrontier.empty())
		{
			cout << "Frontier empty" << endl;
			return -1;			
		}

		//Remove leaf node from frontier
		do
		{
			actualNode = frontier.top();
			frontier.pop();

		}while(isInFrontier.erase(actualNode->state) != 1);  

		cout << endl;
		//cout << "LEAF:  " << actualNode->action.first << "," << actualNode->action.second << endl;
		//cout << "g: " << actualNode->gCost << "h: " << actualNode->hCost << endl;

		//Success if is the goal				
		if(isGoal(actualNode->state, goalState) == 1)
		{
			cout << "GOOAL" << endl;
			cout << actualNode->gCost << endl;
			
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
		
		//Add the node to the explored set
		explored.insert(actualNode->state);

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
						//Only if they are not in frontier or explored
						//cout << "action: (" << childNode->action.first << "," << childNode->action.second << ")" << endl;
						childNode->hCost = heuristic(childNode->state, goalState);
						//cout << "g: " << childNode->gCost << " h: " << childNode->hCost << endl;

						itExplored = explored.find(childNode->state);
						itFrontier = isInFrontier.find(childNode->state);
						
						//if(itExplored == explored.end()  ||  itFrontier == isInFrontier.end() )
						if(itExplored == explored.end())
						{					
							frontier.push(childNode);
							isInFrontier.insert( map< vector<stack <char> >, int >::value_type(childNode->state, childNode->gCost + childNode->hCost) );
						}
						if( itFrontier != isInFrontier.end() && itFrontier->second > (childNode->gCost + childNode->hCost))
						{
							isInFrontier.erase(itFrontier);

							frontier.push(childNode);
							isInFrontier.insert( map< vector<stack <char> >, int >::value_type(childNode->state, childNode->gCost + childNode->hCost) );
					
						}
					}
				}
			}
		}
	}while(frontier.size() > 0);
	cout << "No solution found" << endl;

	return 0;
}
