#verificare ipoteza lui Goldbach
#exista solutie pentru numerele n pare(n>2) sau cele de forma n=2+p, unde p este nr prim

def prim(p):
    if p<2:
        return 0
    if p==2:
        return 1
    for d in range(2,p,1):
        if p%d==0:
            return 0
    return 1


n=int(input("n="))
if n<2:
    print("Nu exista")
else:
    p1=2
    p2=n-2
    gasit=0
    while gasit==0:
        if prim(p1)==1 and prim(p2)==1:
            gasit=1
        else:
            p1+=1
            p2-=1
    print("p1=",p1,"\np2=",p2)
    
