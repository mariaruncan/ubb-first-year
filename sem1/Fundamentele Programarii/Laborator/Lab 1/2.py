n=int(input("n="))
nrdiv=0
for i in range(2,n,1):
    if n%i==0:
        nrdiv=nrdiv+1
if nrdiv>0:
    print("nu este nr prim")
else:
    print("este nr prim")
