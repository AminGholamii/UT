txt = input()
n = len(txt)
lengths = []
for i in range(1, n+1):
    patt = txt[0:i]
    matchs = True
    for j in range(n):
        if txt[j] != patt[j%i]:
            matchs = False
            break

    if matchs:
        lengths.append(i)

print(*lengths)
