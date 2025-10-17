def solve():
    n = int(input())
    if n == 0:
        return 1

    a = list(map(int,input().split()))
    
    ans = 0
    for i in range(n):
        if abs(a[ans] - 2023) > abs(a[i] - 2023):
            ans = i
    
    print(ans + 1)
    return 0

while solve()==0:
    pass