__author__ = 'Parsa Bagheri'
# a simple stack implementation

class Node(object):
	def __init__ (self, value, next = None):
		self.__value = value
		self.__next = next
	
	def setNext (self, next):
		self.__next = next
	
	def getNext (self):
		return self.__next
	
	def getValue (self):
		return self.__value


class Stack (object):
	def __init__ (self):
		self.__stack = []
		self.__top = None
		self.__size = 0
	
	def __repr__ (self):
		string = 'Stack (size = {}, stack = ['.format (self.__size)
		for i in self.__stack:
			string += '{} '.format(str(i.getValue()))
		string += '])'
		return string

	def push (self, value):
		node = Node (value, self.__top)
		self.__top = node
		self.__stack.append (self.__top)
		self.__size += 1
	
	def pop (self):
		if self.__size <= 0:
			return None
		node = self.__top
		self.__top = node.getNext ()
		self.__stack.pop ()
		self.__size -= 1
		return node.getValue ()

	def peek (self):
		if self.__size <= 0:
			return None
		return self.__top.getValue ()
	
	def size (self):
		return self.__size

