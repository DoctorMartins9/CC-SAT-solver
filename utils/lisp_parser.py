import sys
from sympy import *
from typing import Any, List

# Parse input string into a list of all parentheses and atoms (int or str),
# exclude whitespaces.
def normalize_str(string: str) -> List[str]:
    str_norm = []
    last_c = None
    for c in string:
        if c.isalnum():
            if last_c.isalnum():
                str_norm[-1] += c
            else:
                str_norm.append(c)
        elif not c.isspace():
            str_norm.append(c)
        last_c = c
    return str_norm

# Generate abstract syntax tree from normalized input.
def get_ast(input_norm: List[str]) -> List[Any]:
    ast = []
    # Go through each element in the input:
    # - if it is an open parenthesis, find matching parenthesis and make recursive
    #   call for content in-between. Add the result as an element to the current list.
    # - if it is an atom, just add it to the current list.
    i = 0
    while i < len(input_norm):
        symbol = input_norm[i]
        if symbol == '(':
            list_content = []
            match_ctr = 1 # If 0, parenthesis has been matched.
            while match_ctr != 0:
                i += 1
                if i >= len(input_norm):
                    raise ValueError("Invalid input: Unmatched open parenthesis.")
                symbol = input_norm[i]
                if symbol == '(':
                    match_ctr += 1
                elif symbol == ')':
                    match_ctr -= 1
                if match_ctr != 0:
                    list_content.append(symbol)             
            ast.append(get_ast(list_content))
        elif symbol == ')':
                raise ValueError("Invalid input: Unmatched close parenthesis.")
        else:
            try:
                ast.append(int(symbol))
            except ValueError:
                ast.append(symbol)
        i += 1
    return ast


translate = {}
names = 0

def parse_equal(s):
    global names
    string = ""
    if type(s[1]) is list :
        string += to_string(s[1])
    else :
        string += s[1]
    string += '='
    if type(s[2]) is list :
        string += to_string(s[2])
    else :
        string += s[2]
    names += 1
    translate['A' + str(names)]=string
    return 'A' + str(names)

def parse_nequal(s):
    global names
    string = ""
    s = s[1]
    if type(s[1]) is list :
        string += to_string(s[1])
    else :
        string += s[1]
    string += '!='
    if type(s[2]) is list :
        string += to_string(s[2])
    else :
        string += s[2]
    names += 1
    translate['A' + str(names)]=string
    return 'A' + str(names)


def parse_function(s):
    string = ""
    string += s[0] + "("
    for i in range(len(s)):
        if i is len(s)-1:
            string += to_string(s[i])
        elif i is not 0:
            string += s[i] + ","
    string += ")"
    return string

def to_string(s):
    string = ""
    # Case: string
    if type(s) is not list:
        return s
    if(s[0] == '='):
        string += "("
        string += parse_equal(s)
        string += ")"
    elif(s[0] == 'not'):
        string += "("
        string += parse_nequal(s)
        string += ")"
    elif(s[0] == 'and'):
        string += "("
        for i in range(1,len(s)):
            string += to_string(s[i])
            if i != len(s)-1:
                string += "&"
        string += ")"
    elif(s[0] == 'or'):
        string += "("        
        for i in range(1,len(s)):
            string += to_string(s[i])
            if i != len(s)-1:
                string += "|"
        string += ")"
    # Function
    else:
        print("Function")
        string += "("
        string += parse_function(s)
        string += ")"
    return string

def dnf(s):
    input_norm = normalize_str(s)
    ast = get_ast(input_norm)
    ast = ast[0]
    string = to_string(ast[1])
    to_replace =  str(to_dnf(string,simplify=False))
    to_replace = to_replace.replace('(','( ')
    to_replace = to_replace.replace(')',' )')
    array = to_replace.split()
    for i in range(len(array)):
        if array[i] != '&' and array[i] != '|' and array[i] != '(' and array[i] != ')':
            array[i] = translate[array[i]]
    result = ""
    for i in range(len(array)):
        result+=array[i]
    return result
    
def main():
    sat = []
    info = []
    for i in range(1,10):
        x = []
        file = open("../benchmarks/eq_diamond/eq_diamond" + str(i) + ".smt2", "r")
        for f in file:
            x.append(f)
        file.close()
        sat.append(dnf(x[len(x)-3]))
        info.append(x[9])
    out = open("benchmarks_info.txt",'a')
    for i in range(len(info)):
        out.write(info[i]+'\n')
    out.close()
    
    out = open("benchmarks_formula.txt",'a')
    for i in range(len(sat)):
        out.write(sat[i]+'\n')
    out.close()

if __name__ == '__main__':
    main()