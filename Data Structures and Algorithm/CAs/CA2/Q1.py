from collections import deque

N = int(input())
cards = []
for n in input().split():
    cards.append(int(n))
cards.sort()

dq = deque()
for card in reversed(cards):
    if dq:
        dq.appendleft(dq.pop())

    dq.appendleft(card)


print(*list(dq))
