# exemplu gr 216/1

#print("grupa 216 este cea mai tare")


# se citeste un numar n; se citesc n numere naturale; sa se numere cate numere pare s-au citit
n=int(input("n="))
count=0

for i in range(n):
    val=int(input("val="))

    if val % 2 == 0:
        #count = count + 1
        count += 1


print("S-au citit ", count, " numere pare")

