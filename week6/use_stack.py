import stack

s1 = stack.Stack()
s2 = stack.Stack()

n = 5

for i in range(n):
	s1.push(i)

for i in range(n):
	element = s1.pop()
	print(element)
	s2.push(element)

for i in range(n):
	s1.push(s2.pop())

for i in range(n):
	print(s1.pop())
