class RegexNode:
    def __init__(self, value, left=None, right=None):
        self.value = value  # e.g., '*', '|', '.', literal
        self.left = left
        self.right = right
        
    def __repr__(self):
        if self.left and self.right:
            return f"({self.left} {self.value} {self.right})"
        elif self.left:
            return f"({self.value} {self.left})"
        else:
            return f"{self.value}"
