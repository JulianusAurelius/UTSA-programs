hexV = input("Enter hex value value: ")

binary = bin(int(hexV, 16))

big_endian = 0
little_endian = 0

binary = binary[2:]

while len(binary) < len(hexV)*4:
    binary = "0" + binary


print("Binary: ", binary)
binary = "0b" + binary


l = len(binary)-1
lp = len(binary)-3
l2 = 0
while (l>1):
    # print("big:",int(binary[l])*(2**(l2)), end="    ")
    # print("little:",int(binary[l])*(2**(lp)))

    if (l != 2):
        big_endian += int(binary[l])*(2**(l2))
    else:
        big_endian -= int(binary[l])*(2**(l2)) 
    if (l != len(binary)-1):
        little_endian += int(binary[l])*(2**(lp))
    else:
        little_endian -= int(binary[l])*(2**(lp))
    l -= 1
    l2 += 1
    lp -= 1

print("Big Endian: ", big_endian)
print("Little Endian: ", little_endian)