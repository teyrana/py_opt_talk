class BinaryTreeNode:
    def __init__(self, source):
        self.left = None
        self.right = None
        self.value = int(source)

    def add(self, new_value):
        if new_value == self.value:
            return  # no-op
        elif new_value < self.value:
            if None is self.left:
                self.left = BinaryTreeNode(new_value)
            else:
                self.left.add(new_value)

        elif new_value > self.value:
            if None is self.right:
                self.right = BinaryTreeNode(new_value)
            else:
                self.right.add(new_value)

    def search(self, search_value):
        if search_value == self.value:
            return self.value
        elif (search_value < self.value) and (None is not self.left):
            return self.left.search(search_value)
        elif (search_value > self.value) and (None is not self.right):
            return self.right.search(search_value)
        else:
            return None

    def __str__(self, indent=0):
        buf = ""
        next_indent = indent + 4

        if None is not self.right:
            buf += self.right.__str__(next_indent)

        buf += "{}- {}".format(''.rjust(indent), self.value)

        if None is not self.left:
            buf += self.left.__str__(next_indent)

        return buf