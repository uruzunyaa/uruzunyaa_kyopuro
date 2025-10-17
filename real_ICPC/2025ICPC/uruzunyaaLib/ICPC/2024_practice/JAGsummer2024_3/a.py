N,M,H=map(int,input().split())
cells=[0 for _ in range(M+2)]
for i in range(N):
	L,R=map(int,input().split())
	cells[L]+=1
	cells[R+1]-=1
for i in range(1,M+2):
	cells[i]+=cells[i-1]
for i in range(M+1,0,-1):
	H-=cells[i]
	if H<=0:
		print(i)
		exit(0)
print(-1)