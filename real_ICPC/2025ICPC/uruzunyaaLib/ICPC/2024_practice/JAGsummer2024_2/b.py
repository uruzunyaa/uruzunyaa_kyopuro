import math
from bisect import bisect_left,bisect_right
from typing import Generic,Iterable,Iterator,List,Tuple,TypeVar,Optional
T=TypeVar('T')

class SortedSet(Generic[T]):
	BUCKET_RATIO=16
	SPLIT_RATIO=24
	def __init__(self,a:Iterable[T] = []) -> None:
		a=list(a)
		n=self.size=len(a)
		if any(a[i]>a[i+1] for i in range(n-1)):
			a.sort()
		num_bucket=int(math.ceil(math.sqrt(n/self.BUCKET_RATIO)))
		self.a=[a[n*i//num_bucket:n*(i+1)//num_bucket] for i in range(num_bucket)]
	def _position(self,x:T)->Tuple[List[T],int,int]:
		for i , a in enumerate(self.a):
			if x<=a[-1]: break
		return (a,i,bisect_left(a,x))
	
	def __len__(self)->int:
		return self.size
	
	def add(self,x:T)->bool:
		if self.size==0:
			self.a=[[x]]
			self.size=1
			return True
		a,b,i=self._position(x)
		if i!=len(a) and a[i] == x:
			return False
		a.insert(i,x)
		self.size+=1
		if len(a)>len(self.a)*self.SPLIT_RATIO:
			mid=len(a)>>1
			self.a[b:b+1]=[a[:mid],a[mid:]]
		return True
	
	def _pop(self,a:List[T],b:int,i:int)->T:
		ans=a.pop(i)
		self.size-=1
		if not a:del self.a[b]
		return ans
	
	def discard(self,x:T) -> bool:
		if self.size==0:return False
		a,b,i=self._position(x)
		if i==len(a) or a[i]!=x:return False
		self._pop(a,b,i)
		return True
	
	def __getitem__(self,i:int) -> T:
		if i<0:
			for a in reversed(self.a):
				i+=len(a)
				if i>=0: return a[i]
		else:
			for a in self.a:
				if i<len(a):return a[i]
				i-=len(a)
N=int(input())
S=input()
S=S[::-1]
high=[0 for i in range(N)]
tmp=0
for i in range(N):
	if S[i] == "(":
		tmp+=1
	else:
		tmp-=1
	high[i]=tmp
print(high)
smt=SortedSet(high)
tmp=0
ans=[min(high)]
for i in range(N):
	smt.discard(high[i])
	if S[i]=="(":
		tmp+=1
		tmp=min(tmp,0)
	else:
		tmp-=1
		tmp=min(tmp,0)
	if len(smt)>0:
		# print(smt[0],tmp)
		ans.append(min(tmp,smt.__getitem__(0)))
	else:
		ans.append(tmp)
# print(S,ans)
print(*[2*(-(a//2)) for a in ans[::-1]],sep="\n")