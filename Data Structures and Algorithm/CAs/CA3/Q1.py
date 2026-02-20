line_1 = input().split()
n = int(line_1[0])
k = int(line_1[1])

intervals = []
max_end = 0
min_start = 10**18
for i in range(k):
    interval = input().split()
    a, b = int(interval[0]), int(interval[1])
    intervals.append((a,b))
    max_end = max(max_end, b)
    min_start = min(min_start, a)
intervals.sort()

def can_place(intervals, n, d):
    count = 0
    last_pos = -10**19 

    for a, b in intervals:
        pos = max(a, last_pos + d)
        if pos > b:
            continue
        num = ((b - pos) // d) + 1
        count += num
        last_pos = pos + (num - 1) * d
        if count >= n:
            return True

    return False

low, high = 1, max_end - min_start
best = 1
while low <= high:
    mid = (low + high) // 2
    if can_place(intervals, n, mid):
        best = mid
        low = mid + 1
    else:
        high = mid - 1

print(best)
