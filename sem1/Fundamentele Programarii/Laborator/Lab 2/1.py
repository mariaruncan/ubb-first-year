n=int(input())
n+=1
gasit=0
while gasit==0:
    nrdiv=0
    for d in range(1,n+1,1):
        if n%d==0:
            nrdiv+=1
    if nrdiv==2:
        gasit=1
    else:
        n+=1
print(n)
