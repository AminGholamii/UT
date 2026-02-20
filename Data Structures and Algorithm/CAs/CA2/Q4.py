class Node:
    def __init__(self, val):
        self.val = val
        self.prev = None
        self.next = None

class LinkedList:
    def __init__(self, values):
        self.nodes = {}
        self.head = Node(values[0])
        self.nodes[values[0]] = self.head
        curr = self.head
        for v in values[1:]:
            new_node = Node(v)
            curr.next = new_node
            new_node.prev = curr
            curr = new_node
            self.nodes[v] = new_node
        self.tail = curr

    def insert_after(self, x, y):
        node_x = self.nodes[x]
        new_node = Node(y)
        next = node_x.next
        new_node.prev = node_x
        new_node.next = next
        node_x.next = new_node
        if next:
            next.prev = new_node
        else:
            self.tail = new_node
        self.nodes[y] = new_node

    def delete(self, x):
        node_x = self.nodes[x]
        if node_x.prev:
            node_x.prev.next = node_x.next
        else:
            self.head = node_x.next
        if node_x.next:
            node_x.next.prev = node_x.prev
        else:
            self.tail = node_x.prev
        del self.nodes[x]

    def to_list(self):
        res = []
        curr = self.head
        while curr:
            res.append(curr.val)
            curr = curr.next
        return res

N = int(input())
A = [int(i) for i in input().split()]
Q = int(input())
linked_list = LinkedList(A)

for i in range(Q):
    query = input().split()
    command = int(query[0])
    if ( command == 1 ):
        x = int(query[1])
        y = int(query[2])
        linked_list.insert_after(x,y)

    elif ( command == 2 ):
        x = int(query[1])
        linked_list.delete(x)

print(*(linked_list.to_list()))
