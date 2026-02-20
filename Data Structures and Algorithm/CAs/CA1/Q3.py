def isSymmetric(x):
    reverse_x = x[::-1]
    if x == reverse_x:
        return 1

    return 0

x = input()
if ( isSymmetric(x) ):
    print("YES")

else:
    isSy = False
    for i in range(1,len(x)+1):
        new_x = i*"0"+ x
        if isSymmetric(new_x) :
            print("YES")
            isSy = True
            break

        
    if not isSy :
        print("NO")
