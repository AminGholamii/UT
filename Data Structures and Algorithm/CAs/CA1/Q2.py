n = int(input())
if n == 1:
    print(1)
elif n == 2 or n == 3:
    print("NO SOLUTION")
else:
    first = True
    for i in range(2, n+1, 2):
        if not first:
            print(' ', end='')
        print(i, end='')
        first = False
        
    for j in range(1, n+1, 2):
        if not first:
            print(' ', end='')
        print(j, end='')
        first = False
    print()

