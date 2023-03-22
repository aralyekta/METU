import subprocess
import os
import filecmp
input_directory = r'/home/aralyekta/Kod/Ceng242/PE/PE6/PE6/templates_and_tests'

file = "templates_and_tests/"
outfile = "templates_and_tests/outs/"

errors = 0
for filename in os.listdir(input_directory):
    if filename[-4:] == ".cpp":
        f = open("tester.out", "w")
        testfile = file + filename
        subprocess.call("g++ -pedantic -ansi -o compile apartment.cpp corporation.cpp office.cpp owner.cpp person.cpp property.cpp villa.cpp " + testfile, shell=True)
        subprocess.call("./compile", stdout = f)
        f.close()
        if (filecmp.cmp("tester.out", outfile + filename[:-4] + ".out")):
            print(filename, ": True")
        else:
            print(filename, ": False")
            errors += 1

if errors == 0:
    print("SUCCESSFUL, no errors")
else:
    print("FAILED, number of errors:", errors)