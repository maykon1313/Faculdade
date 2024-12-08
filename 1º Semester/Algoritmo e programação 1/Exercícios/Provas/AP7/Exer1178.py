num = float(input())

x = 0
while x < 100:
    if x >= 1:
        num = num / 2
    format_num = "{:.4f}".format(num)
    print("N[" + str(x) + "] = " +str(format_num))
    x += 1