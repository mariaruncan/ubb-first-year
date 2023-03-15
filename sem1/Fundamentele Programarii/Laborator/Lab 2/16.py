#numerele perfecte sunt de forma 2^(p-1)*(2^p-1), unde p este un nr prim
#nu se stie daca exista nr perfecte impare
#primele nr perfecte sunt 6, 28, 496, 8128, 33550336,...

def prim(n):
    if n<2:
        return 0
    if p==2:
        return 1
    for d in range(2,n,1):
        if n%d==0:
            return 0
    return 1

n=int(input("n="))
p=2
x=0
y=0
gasit=0
while gasit==0:
    if prim(p)==1:
        x=y
        y=2**(p-1)*(2**p-1)
        if x<n and y>n:
           gasit=1
    p+=1
if x==0:
    print("Nu exista")
else:
    print(x)
