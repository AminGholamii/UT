from collections import deque
def bfs(A, B, grid, n, m):
    visited = [[0 for j in range(m)] for i in range(n)]
    queue = deque([A])
    visited[A[0]][A[1]] = 1

    directions = [(-1,0), (1,0), (0,1), (0,-1)]
    while queue:
        x, y = queue.popleft()
        if (x,y) == B :
            return 1
        for dx, dy in directions:
            new_x = x + dx
            new_y = y + dy
            if 0<=new_x<n and 0<=new_y<m:
                if not visited[new_x][new_y] and grid[new_x][new_y] != '#':
                    visited[new_x][new_y] = 1
                    queue.append((new_x, new_y))

    return 0

n, m = map(int, input().split())
grid = [['#' for j in range(m)] for i in range(n)]
for i in range(n):
    row = input()
    for j in range(m):
        grid[i][j] = row[j]
        if row[j] == 'A':
            A = (i, j)
        elif row[j] == 'B':
            B = (i, j)

if bfs(A, B, grid, n, m):
    print("YES")
else:
    print("NO")
