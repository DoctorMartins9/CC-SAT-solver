import os 
import re
import parse
sat = []
info = []
string_final = ""

def get_args(input):
    par = 0
    first = ""
    second = ""
    for i in range(0,len(input)):
        if input[i] == '(':
            par += 1
        elif input[i] == ')':
            par -= 1
        elif input[i] == ',' and par == 0:
            first = input[0:i]
            second = input[i+1:len(input)]
    return [first, second]

def parse_e(array):
    global string_final
    for i in range(0,len(array)-1):
        r = get_args(array[i])
        r[1] =r[1].replace('),','')
        string_final += r[0] + "=" + r[1] + "&"

def parse_n(array):
    global string_final
    for i in range(0,len(array)-1):
        rip = array[i].split(',')
        string_final += rip[0] + "!=" + rip[1] + "&"
    last = array[len(array)-1].split(',select')
    string_final += last[0] + "!=select" + last[1]

def single_parser(path):
    x = []
    file = open(path, "r")
    for f in file:
        x.append(f)
    file.close()
    screm = []
    for i in range(0,len(x)):
        x[i] = x[i].replace(' ','')
        x[i] = x[i].replace('\n','')
        x[i] = x[i].replace('\t','')
        if x[i][0] == '[':
            x[i] = x[i].replace(')]).','')
            x[i] = x[i].replace('[','')
            screm.append(x[i])
    
    eq = []
    neq = []
    for i in range(0,len(x)):
        if x[i][0] == '+':
            x[i] = x[i].replace('++equal(','')
            eq.append(x[i])
        elif x[i][0] == '-':
            x[i] = x[i].replace('--equal(','')
            neq.append(x[i])
    parse_e(eq)
    parse_n(neq)
    print(string_final)

def main():
    single_parser("../benchmarks/array_benchmarks/storecomm_invalid_t1_pp_nf_ai_00010_009.tptp")


if __name__ == '__main__':
    main()