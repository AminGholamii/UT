import heapq

n = int(input())
people = []
for i in range(n):
    line = input().split()
    people.append((int(line[0]), int(line[1]), i))

people.sort(key=lambda x: x[0])

pq = [] 
current_time = 0
max_wait = 0
idx = 0

while idx < n or pq:
    if not pq:
        current_time = max(current_time, people[idx][0])
        a, t, p = people[idx]
        heapq.heappush(pq, (p, a, t))
        idx += 1

    p, a, t = heapq.heappop(pq)
    start = max(current_time, a)
    wait = start - a
    max_wait = max(max_wait, wait)
    current_time = start + t

    while idx < n and people[idx][0] <= current_time:
        a2, t2, p2 = people[idx]
        heapq.heappush(pq, (p2, a2, t2))
        idx += 1

print(max_wait)