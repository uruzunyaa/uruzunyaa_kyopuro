N = int(input())

digitCnt = len(str(N))
MOD = 998244353
p10 = pow(10, digitCnt, MOD)

ans = N * (pow(p10, N, MOD) - 1) * (pow(p10 - 1, -1, MOD))
ans %= MOD

print(int(ans))

ans = N * (pow(p10, N, MOD) - 1) / (p10 - 1)
ans %= MOD

print(int(ans))
