import subprocess
import json
from os import system


def msg(s):
    print('\033[1m\033[91m' + s + '\033[0m\033[0m')


def err(data_in, s):
    msg("Wrong on input " + str(data_in) + "\n" + s)
    exit(1)


input_list = subprocess.getoutput('find ./tests/*.cmm').split('\n')
for file_name in input_list:
    out_file_name = file_name[:-4]+'.json'
    irsim_out = file_name[:-4]+'.log'
    data_with_output = []
    with open(irsim_out, 'r') as from_irsim_r:
        output_lines = from_irsim_r.readlines()
        output_lines = list(map(int, output_lines))
        data_with_output.append([[], output_lines, 0])
    with open(out_file_name, "w") as out:
        json.dump(data_with_output, out)
    print("json file updated successfully")
