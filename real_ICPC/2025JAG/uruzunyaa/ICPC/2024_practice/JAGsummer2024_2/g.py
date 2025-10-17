T=int(input())
for _ in range(T):
	A1,A2,A3=map(int,input().split())
	ans=A1//3
	A1=A1%3
	if A1==0:
		ans+=(A2+A3)//3
	elif A1==1 and (A2>=2 or A3>=2):
		ans+=(A1+A2+A3)//3
	elif A1==2:
		for _ in range(2):
			if A2>=2:
				A2-=2
				ans+=1
			elif A3>=2:
				A3-=2
				ans+=1
		ans+=(A2+A3)//3
	print(ans)