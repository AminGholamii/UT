from collections import deque
def hasCycle(n, adj):
    visited = [0 for i in range(n+1)]
    parent = [-1 for i in range(n+1)]

    for start in range(1, n+1):
        if not visited[start]:
            queue = deque([start])
            visited[start] = 1
            while queue:
                u = queue.popleft()
                for v in adj[u]:
                    if not visited[v]:
                        visited[v] = 1
                        parent[v] = u
                        queue.append(v)
                    elif v != parent[u]:
                        return 1
    return 0

n, m = map(int, input().split())
adj_list = [[] for i in range(n + 1)]
edge_set = set()
for i in range(m):
    u, v = map(int, input().split())
    if (u, v) in edge_set or (v, u) in edge_set:
        continue
    edge_set.add((u, v))
    adj_list[u].append(v)
    adj_list[v].append(u)

if n <= 2:
    print("NO")
elif hasCycle(n, adj_list):
    print("YES")
else:
    print("NO")
