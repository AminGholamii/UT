n = int(input())
heights = []
for h in input().split():
    heights.append(int(h))
    
stack = []
max_area = 0

for i in range(n):
    while stack and heights[i] < heights[stack[-1]]:
        h = heights[stack.pop()]
        if stack:
            width = i-stack[-1]-1
        else:
            width = i
            
        max_area = max(max_area, h * width)
        
    stack.append(i)

while stack:
    h = heights[stack.pop()]
    if stack:
        width = n-stack[-1]-1
    else:
        width = n
    max_area = max(max_area, h * width)

print(max_area)
            
    
