page = []
for i in range(3):
    line = input()
    page.append(line)

single_wins = set()
double_wins = set()

lines = []
lines.extend(page)
for c in range(3):
    lines.append(''.join(page[r][c] for r in range(3)))
lines.append(''.join(page[i][i] for i in range(3)))
lines.append(''.join(page[i][2 - i] for i in range(3)))

for line in lines:
    unique = set(line)
    if ( len(unique) == 1 ):
        single_wins.add(list(unique)[0])

    elif ( len(unique) == 2 ):
        a, b = sorted(list(unique))
        double_wins.add((a, b))

print(len(single_wins))
print(len(double_wins))
