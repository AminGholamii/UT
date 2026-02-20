line_1 = input().split()
n = int(line_1[0])
w = int(line_1[1])

lib, ibn = [] , []
line = input().split()
for book in line:
    lib.append(int(book))

line = input().split()
for book in line:
    ibn.append(int(book))

txt = [lib[i]-lib[i-1] for i in range(1,n)]
patt = [ibn[i]-ibn[i-1] for i in range(1,w)]

def build_lps(patt):
    lps = [0] * len(patt)
    length = 0
    i = 1
    while i < len(patt):
        if patt[i] == patt[length]:
            length += 1
            lps[i] = length
            i += 1
        else:
            if length != 0:
                length = lps[length-1]
            else:
                lps[i] = 0
                i += 1
    return lps

def kmp_search(txt, patt):
    lps = build_lps(patt)
    count = 0
    i = j = 0 

    while i < len(txt):
        if txt[i] == patt[j]:
            i += 1
            j += 1
            if j == len(patt):
                count += 1
                j = lps[j - 1]
        else:
            if j > 0:
                j = lps[j - 1]
            else:
                i += 1
    return count

if ( w == 1 ):
    print(n)

else:
    print(kmp_search(txt, patt))