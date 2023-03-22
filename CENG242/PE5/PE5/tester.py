import subprocess
import os
import filecmp
input_directory = r'/home/aralyekta/Kod/Ceng242/PE/PE5/PE5/the5_test_cases'
output_directory = r'/home/aralyekta/Kod/Ceng242/PE/PE5/PE5/the5_test_cases/outs'

file = "the5_test_cases/"
outfile = "the5_test_cases/outs/"

for filename in os.listdir(input_directory):
    if filename[-4:] == ".cpp":
        f = open("tester.out", "w")
        testfile = file + filename
        subprocess.call("g++ -pedantic -ansi -o compile path_tracker.cpp " + testfile, shell=True)
        subprocess.call("./compile", stdout = f)
        f.close()
        if (filecmp.cmp("tester.out", outfile + filename[:-4] + ".out")):
            print(filename, ": True")
        else:
            print(filename, ": False")
