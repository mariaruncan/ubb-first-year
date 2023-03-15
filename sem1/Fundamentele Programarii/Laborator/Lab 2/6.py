n=int(input("n="))
a=1
b=1
aux=0
while n>b:
    aux=a+b
    a=b
    b=aux
print(b)
