a=int(input("a="))
b=int(input("b="))
while b!=0:
    r=a%b
    a=b
    b=r
print(a)
