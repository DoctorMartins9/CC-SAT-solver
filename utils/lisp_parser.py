import sys

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

def parse_equal(s):
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
    return string

def parse_nequal(s):
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
    return string


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

def parse_and(s):
    string = ""
    if type(s[1]) is list :
        string += to_string(s[1])
    else :
        string += s[1]
    string += '&'
    if type(s[2]) is list :
        string += to_string(s[2])
    else :
        string += s[2]
    return string

def parse_or(s):
    string = ""
    if type(s[1]) is list :
        string += to_string(s[1])
    else :
        string += s[1]
    string += '|'
    if type(s[2]) is list :
        string += to_string(s[2])
    else :
        string += s[2]
    return string

def to_string(s):
    string = ""
    # Case: string
    if type(s) is not list:
        return s
    # Case: assert
    if len(s) == 1 and s[0][0] == 'assert':
        s = s[0][1]
    # Case: equal
    if(s[0] == '='):
        string += parse_equal(s)
    elif(s[0] == 'not'):
        string += parse_nequal(s)
    elif(s[0] == 'and'):
        string += parse_and(s)
    elif(s[0] == 'or'):
        string += parse_or(s)
    # Function
    else:
        string += parse_function(s)
    return string



def main():
    input_str = """(assert (and (and (and (and (and (and (and (and (and (not (= e0 e1)) (not (= e0 e2))) (not (= e0 e3))) (not (= e0 e4))) (not (= e1 e2))) (not (= e1 e3))) (not (= e1 e4))) (not (= e2 e3))) (not (= e2 e4))) (not (= e3 e4))))"""
    list_str = input_str.split('\n')
    out = ""
    for l in list_str:
        input_norm = normalize_str(l)
        ast = get_ast(input_norm)
        out += to_string(ast)
        if l != list_str[len(list_str)-1]:
            out += "&"
    print(out)

if __name__ == '__main__':
    main()