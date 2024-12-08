print("Qual a idade?")
i = int(input())
print("Qual o peso?")
p = int(input())

if i < 20:
    fi = 0
elif 20 <= i <= 50:
    fi = 1
else:
    fi = 2


if p < 60:
    fp = 0
elif 60 <= i <= 90:
    fp = 1
else:
    fp = 2

if fi == 0 and fp == 0:
    print("Grupo de risco: 9.")
elif fi == 0 and fp == 1:
    print("Grupo de risco: 8.")
elif fi == 0 and fp == 2:
    print("Grupo de risco: 7.")
elif fi == 1 and fp == 0:
    print("Grupo de risco: 6.")
elif fi == 1 and fp == 1:
    print("Grupo de risco: 5.")
elif fi == 1 and fp == 2:
    print("Grupo de risco: 4.")
elif fi == 2 and fp == 0:
    print("Grupo de risco: 3.")
elif fi == 2 and fp == 1:
    print("Grupo de risco: 2.")
else:
    print("Grupo de risco: 1.")