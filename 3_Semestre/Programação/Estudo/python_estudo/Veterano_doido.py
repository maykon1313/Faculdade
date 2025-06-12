a = 12
b = 3

a > b and print("Olá matemática.")
a < b and print("Tchau matemática.")

v = [lambda: print("Arroz."), lambda: print("Feijão.")]

v[bool(a < b)]()
v[bool(a > b)]()


v_1 = [lambda x, y: x < y, lambda x, y: x > y]

v[v_1[0](a, b)]()
v[v_1[1](a, b)]()

