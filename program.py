import fileinput

input = fileinput.input()
for line in input:
    for j in range(int(line)):
        print "Hello World!"
