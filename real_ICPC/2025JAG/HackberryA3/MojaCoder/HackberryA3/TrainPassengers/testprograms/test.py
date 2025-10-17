N, M = map(int, input().split())
A = list(map(int, input().split()))

sum = 0
cnt = 0
for i in range(N):
    cnt += A[i]
    if M < cnt:
        sum += A[i] - (cnt - M)
        cnt = M
    elif 0 <= A[i]:
        sum += A[i]

print(sum)
