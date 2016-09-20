import fileinput

queue = []

input = fileinput.input()
i = 0
for line in input:
  if i == 0:
    max_stack = int(line.strip())
    print (max_stack)
  if i == 1:
    j = 0
    initial_state = line.strip()
    initial_state = initial_state.replace(" ", "")
    initial_state = initial_state.replace("(", "")
    initial_state = initial_state.replace(")", "")
    initial_state = initial_state.split(';')
    try:
      while initial_state[j] is not None:
        list(initial_state[j])
        j += 1
    except IndexError:
    	pass
    print(initial_state)
  if i == 2:
    end_state = line.strip()
    
    print(end_state)
  i += 1
