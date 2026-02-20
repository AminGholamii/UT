from collections import deque
N, M = input().split()
N = int(N)
M = int(M)

F = []
S = []
for i in range(N):
    line = input().split()
    F.append(int(line[0]))
    S.append(int(line[1]))

left = 0
f_sum = 0
ans = 10**10

dq = deque()
for right in range(N):
    f_sum += F[right]
    while dq and S[dq[-1]] <= S[right]:
        dq.pop()
    dq.append(right)

    while f_sum >= M:
        ans = min(ans, S[dq[0]])
        f_sum -= F[left]
        if dq[0] == left:
            dq.popleft()
        left += 1

print(ans)





