class BIT:
    def __init__(self, n):
        self.n = n
        self.bit = [0]*(n+1)

    def add(self, i, v):
        while i <= self.n:
            self.bit[i] += v
            i += i & -i

    def sum(self, i):
        s = 0
        while i > 0:
            s += self.bit[i]
            i -= i & -i
        return s
    
    def range_sum(self, l, r):
        return self.sum(r) - self.sum(l-1)

line = input().split()
n = int(line[0])
q = int(line[1])

line = input().split()
Hashes = [0]
for i in range(n):
    xi = int(line[i])
    Hashes.append(xi)

queries = []
for qi in range(q):
    line = input().split()
    a, b = int(line[0]), int(line[1])
    queries.append((b, a, qi))

queries.sort()

bit = BIT(n)
last_occ = {}
answers = [0]*q

idx = 0
for i in range(1, n+1):
    val = Hashes[i]
    if val in last_occ:
        bit.add(last_occ[val], -1) 
    bit.add(i, 1)               
    last_occ[val] = i

    while idx < q and queries[idx][0] == i:
        b,a,qi = queries[idx]
        answers[qi] = bit.range_sum(a,b)
        idx += 1

print("\n".join(map(str, answers)))