from collections import deque
import sys
input=sys.stdin.readline
N=int(input())
A=list(map(int,input().split()))
edge=[[] for _ in range(N)]
dq=deque()
for i in range(N-1):
	u,v,c=map(int,input().split())
	edge[u-1].append((v-1,c))
	edge[v-1].append((u-1,c))
dq.append(0)
way=[]
use=[False for _ in range(N)]
use[0]=True
tree_edge=[[] for _ in range(N)]
while len(dq)!=0:
	p=dq.popleft()
	way.append(p)
	for e,c in edge[p]:
		if not use[e]:
			tree_edge[p].append([e,c])
			use[e]=True
			dq.append(e)
dp=[[A[i],A[i]] for _ in range(N)]
for i in range(N-1,-1,-1):
	pos=way[i]
	not_use=[]
	use=[0]
	for e,c in tree_edge[pos]:
		not_use.append(min(dp[e][0],c))
		use.append(max(min(dp[e][1],c),dp[e][0])-min(dp[e][0],c))
	dp[pos][0]=A[pos]+sum(not_use)
	dp[pos][1]=dp[pos][0]+max(use)
print(max(dp[0]))