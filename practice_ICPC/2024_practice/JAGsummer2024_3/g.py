import random
print('?','a',flush=True)
R=input()
str="a"
if R=="No":
	str="b"
#右側に追加していく
No_count=0
limit=23
max_length=1000
while True:
	add='ab'[random.randint(0,1)]
	if len(str+add)>max_length:
		R="No"
	else:
		print('?',str+add,flush=True)
		R=input()
	if R=="Invalid":
		assert 1==0
	if R=="No":
		No_count+=1
		if add=="a":
			str+="b"
		else:
			str+="a"
	else:
		No_count=0
		str+=add
	if No_count==limit:
		while True:
			str=str[:-1]
			if len(str)>max_length:
				R="No"
			else:
				print('?',str,flush=True)
				R=input()
			if R=="Yes":
				break
			elif R!="No":
				assert 1==0
		break

No_count=0
while True:
	add='ab'[random.randint(0,1)]
	if len(add+str)>max_length:
		R="No"
	else:
		print('?',add+str,flush=True)
		R=input()
	if R=="Invalid":
		assert 1==0
	if R=="No":
		No_count+=1
		if add=="a":
			str="b"+str
		else:
			str="a"+str
	else:
		No_count=0
		str=add+str
	if No_count==limit:
		while True:
			str=str[1:]
			if len(str)>max_length:
				R="No"
			else:
				print('?',str,flush=True)
				R=input()
			if R=="Yes":
				break
			elif R!="No":
				assert 1==0
		break
print('!',str,flush=True)