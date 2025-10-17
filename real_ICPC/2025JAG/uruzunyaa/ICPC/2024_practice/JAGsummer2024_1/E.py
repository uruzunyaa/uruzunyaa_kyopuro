import sys
input=sys.stdin.readline
B=int(input())
N=int(input())
A=[]
for i in range(N):
	A.append(int(input()))
dp=[[10**5 for _ in range(B+1)]for _ in range(N+1)]
A_=A[::]
for i in range(1,N):
	A_[i]+=A_[i-1]
A_.append(0)
A__=[a**2 for a in A]
for i in range(1,N):
	A__[i]+=A__[i-1]
A__.append(0)
dp[0][0]=0
for i in range(N):
	for j in range(i+1,N+1):
		a2sum=A__[j-1]-A__[i-1]
		asum=A_[j-1]-A_[i-1]
		count=j-i
		median=asum/(count)
		dp_d=a2sum-median**2*count
		for k in range(B+1):
			if k!=B:
				dp[j][k+1]=min(dp[j][k+1],dp[i][k]+dp_d)
print(dp[-1][-1])