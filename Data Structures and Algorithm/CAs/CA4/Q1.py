from collections import deque
def BFS(start, n, adj):
    visited = [0 for i in range(n+1)]
    queue = deque([start])
    visited[start] = 1
    count = 1
    while queue:
        u = queue.popleft()
        for v in adj[u]:
            if not visited[v]:
               visited[v] = 1
               queue.append(v) 
               count += 1

    if count == n:
        return 1  
    else:
        return 0         

n, m = map(int, input().split())
adj_list = [[] for i in range(n+1)]
reversed_adj_list = [[] for i in range(n+1)]
for i in range(m):
    u, v = map(int, input().split())
    if (i == 0):
        start = u
    adj_list[u].append(v)
    reversed_adj_list[v].append(u)

if (BFS(start, n, adj_list) and BFS(start, n, reversed_adj_list)):
    print("YES")

else:
    print("NO")


