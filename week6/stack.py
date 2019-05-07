class Stack():
	def __init__(self):
		self.l = []
		
	def push(self, element):
		self.l.append(element)

	def pop(self):
		element = None
		if len(self.l) > 0:
			element = self.l[-1]
			del self.l[-1]
		return element

	def peek(self):
		if len(self.l) > 0:
			return self.l[-1]
		return None
