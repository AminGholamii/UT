def dfs_visit(start, adj, visited):
    stack = [start]
    visited[start] = 1
    while stack:
        u = stack.pop()
        for v in adj[u]:
            if not visited[v]:
                visited[v] = 1
                stack.append(v)

def connectedComponentsCount(n, adj):
    count = 0
    visited = [0 for i in range(n+1)]
    for i in range(1, n+1):
        if not visited[i]:
            dfs_visit(i, adj, visited)
            count += 1
    return count

n, m = map(int, input().split())
adj_list = [[] for i in range(n+1)]
edge_set = set()
for i in range(m):
    u, v = map(int, input().split())
    if (u, v) in edge_set or (v, u) in edge_set:
        continue
    edge_set.add((u, v))
    adj_list[u].append(v)
    adj_list[v].append(u)

components = connectedComponentsCount(n, adj_list)
print(components - 1)
