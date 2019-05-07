import stack

s1 = stack.Stack()

for i in range(5):
	s1.push(i)

def print_stack(s1):
	s2 = stack.Stack()
	while True:
		element = s1.pop()
		if element != None:
			print(element)
			s2.push(element)
		else: break
	
	while True:
		element = s2.pop()
		if element != None:
			s1.push(element)
		else: break


print_stack(s1)
print_stack(s1)
