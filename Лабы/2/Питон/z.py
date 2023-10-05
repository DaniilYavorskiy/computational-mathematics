import math

eps = 0.0001

f = open('1.txt', 'r')
string_arr = []
for line in f:
    string_arr.append(line.split(" "))
    
string_num = len(string_arr)
for i in range(0, string_num):
    for q in range(0, string_num+1):
        string_arr[i][q]= int(string_arr[i][q])
for i in range(0, string_num):
    for q in range(0, string_num+1):
        print(str(string_arr[i][q]) + "    " , end=" ")
    print(" ")
    print(" ")



for i in range(0, string_num):
    w = string_arr[i][i]
    for q in range(0, string_num+1):
        string_arr[i][q] = string_arr[i][q] / w
for i in range(0, string_num):
    for q in range(0, string_num+1):
        print(str(string_arr[i][q]) + "    " , end=" ")
    print(" ")
    print(" ")


E = [0] * string_num
for i in range(string_num):
    E[i] = [0] * string_num
    E[i][i] = 1
for i in range(0, string_num):
    for q in range(0, string_num):
        print(str(E[i][q]) + "    " , end=" ")
    print(" ")
    print(" ")

C = [0] * string_num
for i in range(string_num):
    C[i] = [0] * string_num
    for q in range(string_num):
        C[i][q] = string_arr[i][q]
    C[i][i] = 0
for i in range(0, string_num):
    for q in range(0, string_num):
        print(str(C[i][q]) + "    " , end=" ")
    print(" ")
    print(" ")

B = []
for i in range(string_num):
    B.append(string_arr[i][string_num])
for i in range(0, string_num):

    print(str(B[i]))

ArrCS = []
for i in range(string_num):
    ArrCS.append(0)
    for q in range(string_num):
        ArrCS[i] = ArrCS[i] + abs(C[i][q])
Cm = max(ArrCS)
print(Cm)
Bm = max(B)
print(Bm)

N=(math.log(((eps)*(1-Cm))/(Bm))/ math.log(Cm)) + 1
print(N)

x = []
y = []
for i in range(0, len(B)):
    y.append(B[i])
x.append(y)



for i in range(1,math.ceil(N)):
    x.append([[i * j for j in range(string_num)]])
    for v in range(0, string_num):
        x[i].append(0)
        m = 0
        for h in range(0, string_num):
            m = m + C[v][h]*x[i-1][h] 
        x[i][v] = B[v] - m
    print("шаг номер " + str(i) + " :" , end="    ")
    for t in range(0, string_num):
        print(x[i-1][t]-x[i][t], end=" ")
    print("   переменные: ", end=" ")
    for t in range(0, string_num):
        print(x[i][t], end=" ")
    print("")
for i in range(0, string_num):
    print("x" + str(i+1) + " = " + str(x[math.ceil(N)-1][i])    )
