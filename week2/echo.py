__author__ = 'Parsa Bagheri'
'''
This is a generic implementation of the `echo' program in python

SYNOPSIS
python[3] echo.py [-n] [-e] [-E] [string ...]
'''
from sys import argv, stdout, stderr
# argv (stands for argument vector) is the arguments that are passed to a program in command line
# for example if I am calling the `echo' program with flags -n and -e, and string `this is CIS 212':
# the argv would be an array of strings {'echo', '-n', '-e', 'this is CIS 212'}
# or in case of python, a list of strings ['echo', '-n', '-e', 'this is CIS 212'] 

# note that the first argument is always the name of the program

e_flag = False #used to set -e or -E flags, e flag enables backslash interpretation, while E flag disables them
n_flag = False #used to set -n flag

def echo(strings):
    global e_flag, n_flag
    for string in strings:
        to_be_echoed = string
        if e_flag: 
            # if e_flag is set, we need to interpret backslash escapes
            # this is how it's done in python, you don't need to worry about the technicalities 
            # (you won't be doinng this in your project)
            to_be_echoed = to_be_echoed.encode().decode('unicode_escape')

        # every string echoed is seperated by a space
        stdout.write(to_be_echoed + ' ')

    # if the n flag is specified, we can't have a new line character, but if it's not specified, 
    # then we need to write a new line character in stdout
    if n_flag == False:
        stdout.write('\n')

def main():
    # since e_flag and n_flag are global, in order to change them within the scope of a function/class,
    # you need to specify them as global in your functions/classes
    global e_flag, n_flag
    argc = len(argv) # getting the count of arguments passed to the program
    i = 1 # start our index from 1, since index 0 (argv[0]) is the name of the program, i.e. `echo'
    while i < argc:
        # we need to look for flags
        # we know that the flags start with `-' and the length of these flags can't be longer that 2 characters
        # (at least in case of echo), i.e. `-n' or `-e' or `-E'
        # also note that the flags in echo can only be applied before the string
        if argv[i][0] == '-' and len(argv[i]) == 2:
            # now that we know the argument is a flag, we need to check to see which flag it is
            if argv[i][1] == 'n': 
                n_flag = True
            elif argv[i][1] == 'e':
                e_flag = True
            elif argv[i][1] == 'E':
                e_flag = False
        else:
            # now we are done parsing the flags
            break
        i += 1

    strings = []
    while i < argc:
        # now we need to parse the strings passed to our program
        strings.append(argv[i])
        i += 1

    # now that we have parsed all the command line arguments, we can write and call an echo function
    echo(strings)
        
if __name__ == "__main__":
    main()
