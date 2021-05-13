import argparse
parser = argparse.ArgumentParser()
parser.add_argument("n", type=int)
parser.add_argument("m", type=int)
parser.add_argument("fn", type=str)
args = parser.parse_args()

import os
os.system("rm " + args.fn)
import numpy as np
matrix = np.random.rand(args.n * args.m).reshape(args.n, args.m)
with open(args.fn, mode='x') as f:
    f.write(str(args.n) + ' ' + str(args.m) + '\n')
    for line in matrix:
        for elem in line:
            f.write(str(elem) + ' ')
        f.write("\n")
