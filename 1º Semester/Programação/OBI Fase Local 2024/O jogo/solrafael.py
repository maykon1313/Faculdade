#!/usr/bin/env python3

MAX = 55

mat = [[0] * MAX for _ in range(MAX)]
[N,Q] = [int(x) for x in input().split()]

for i in range(1, N + 1):
    s = input()
    for j in range(1, N + 1):
        if s[j - 1] == '1':
            mat[i][j] = 1

for _ in range(Q):
    viz = [[0] * MAX for _ in range(MAX)]
    for i in range(1, N + 1):
        for j in range(1, N + 1):
            viz[i][j] += mat[i + 1][j]
            viz[i][j] += mat[i - 1][j]
            viz[i][j] += mat[i + 1][j + 1]
            viz[i][j] += mat[i - 1][j - 1]
            viz[i][j] += mat[i + 1][j - 1]
            viz[i][j] += mat[i - 1][j + 1]
            viz[i][j] += mat[i][j + 1]
            viz[i][j] += mat[i][j - 1]

    for i in range(1, N + 1):
        for j in range(1, N + 1):
            if mat[i][j]:
                if viz[i][j] < 2 or viz[i][j] > 3:
                    mat[i][j] = 0
            else:
                if viz[i][j] == 3:
                    mat[i][j] = 1
                    
for i in range(1, N + 1):
    for j in range(1, N + 1):
        print(chr(ord('0') + mat[i][j]), end='')
    print()
