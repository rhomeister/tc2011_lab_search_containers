import fileinput

queue = []
initial_state = []
end_state = []

def heuristic_function():
	return value
	
def gcost():
	return value
	
def hcost():
	return value
	
def fcost():
	return value
	
def create_state():
	return state
	
def expand():
	print("hello")
	return

def check_end(state):
	for i, element in enumerate(state):
		print(element)

input = fileinput.input()
i = 0
for line in input: #read line by line of stdin
	i += 1
	if i == 1: #reads first line, which contains maximum stack height
		max_stack = int(line.strip())
		print (max_stack)
	elif i == 2: #reads second line, which contains the intial state
		#the following block formats the line and creates the initial state data structure
		initial_state = line.strip()
		initial_state = initial_state.replace(" ", "")
		initial_state = initial_state.replace("(", "")
		initial_state = initial_state.replace(")", "")
		initial_state = initial_state.split(';')
		for i, element in enumerate(initial_state):
			initial_state[i] = element.split(",")
		print(initial_state)
	elif i == 3: #reads the third line, which contains the end state
		#the following block formats the line and creates the end state data structure
		end_state = line.strip()
		end_state = end_state.replace(" ", "")
		end_state = end_state.replace("(", "")
		end_state = end_state.replace(")", "")
		end_state = end_state.split(';')
		for i, element in enumerate(end_state):
			end_state[i] = element.split(",")
		print(end_state)
print("sup")
	
