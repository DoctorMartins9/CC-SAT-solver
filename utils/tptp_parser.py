import os 
import re
sat = []
info = []
string_final = ""

def single_parser(path):
    x = []
    file = open(path, "r")
    for f in file:
        x.append(f)
    file.close()
    input_string = ""
    for row in x:
        input_string += row
    print(input_string)
    
    '''
    input_string = input_string.replace('\t','')
    input_string = input_string.replace('\n','')
    array = re.split('\[|\]',input_string)
    eq_div = []
    neq_div = []
    eq_parser = []
    neq_parser = []
    for a in array:
        if a[0] == '+':
            eq_div.append(a.split('++equal'))
        elif a[0] == '-':
            neq_div.append(a.split('++equal'))
    for i in eq_div:
        for j in range (1, len(i)):
            eq_parser.append(i[j])
    for i in neq_div:
        for j in range (1, len(i)):
            neq_parser.append(i[j])
    print(eq_parser)
        

     out = open("benchmarks_info.txt",'a')
    for i in range(len(info)):
        out.write(info[i]+'\n')
    out.close()
    out = open("benchmarks_formula.txt",'a')
    for i in range(len(sat)):
        out.write(sat[i]+'\n')
    out.close()
    '''

def main():
    single_parser("../benchmarks/array_benchmarks/storeinv_invalid_t1_pp_sf_ai_00002_001.cvc")


if __name__ == '__main__':
    main()