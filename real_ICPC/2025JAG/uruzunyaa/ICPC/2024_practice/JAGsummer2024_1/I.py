lis=[]
N=int(input())
for i in range(N):
	p,q,r,s=map(int,input().split())
	lis.append((q*r*s,q+r+s,p))
lis.sort()
ans=[]
for i in range(3):
	ans.append(lis[i][2])
print(*ans)