import math
ans=20
for a in range(1,1001):
	for b in range(1,1001):
		ans=max(ans,20+(1000-a-b+2)*(math.log(a,2)+math.log(b,2))/2)
print(ans)