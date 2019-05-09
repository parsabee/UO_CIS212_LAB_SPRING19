__author__ = 'Adam Noack'
# using the stack ADT that we created

from stack import Stack

def print_stack(stack_1):
	stack_2 = Stack()
	print ('Stack:')
	element = stack_1.pop()
	while element != None:
		print ('+-------+')
		print('|  {}\t|'.format(element))
		print ('+-------+')
		stack_2.push(element)
		element = stack_1.pop()
	
	element = stack_2.pop()
	while element != None:
		stack_1.push(element)
		element = stack_2.pop()

if __name__ == '__main__':
	stack = Stack()

	for i in range(50, 60):
		stack.push(i)
	print_stack(stack)
