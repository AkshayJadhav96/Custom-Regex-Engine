class State:
    def __init__(self):
        self.transitions = {}
    
    def add_transition(self, symbol, state):
        if symbol not in self.transitions:
            self.transitions[symbol] = []
        self.transitions[symbol].append(state)
    
class NFA:
    def __init__(self,start,accept):
        self.start = start
        self.accept = accept
    

