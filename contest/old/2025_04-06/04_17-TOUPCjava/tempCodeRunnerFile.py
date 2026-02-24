import sys

# 入力
h, w = map(int, sys.stdin.readline().split())
a = [list(map(lambda x: float(x)/100.0, sys.stdin.readline().split())) for _ in range(h)]

# dpテーブル初期化
dp = [[0.0] * (1 << w) for _ in range(h + w - 1)]
dp[0][1] = 1.0 - a[0][0]

for i in range(h + w - 2):
    for b in range(1 << w):
        bbit = b | (b << 1)
        bbit &= (1 << w) - 1

        for c in range(1 << w):
            f = False
            for j in range(w):
                if (c & (1 << j)):
                    if i + 1 - j >= h or i + 1 - j < 0:
                        f = True
                        break
            if f:
                continue

            cbit = bbit & c
            tmp = 1.0

            for j in range(max(i + 2 - h, 0), min(i + 1, w - 1) + 1):
                if c & (1 << j):
                    tmp *= 1.0 - a[i + 1 - j][j]
                else:
                    tmp *= a[i + 1 - j][j]

            dp[i + 1][cbit] += tmp * dp[i][b]

print(f"{dp[h + w - 2][1 << (w - 1)]:.15f}")
