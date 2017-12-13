#Exercise 2 Question 4
#! /usr/bin/python2
import numpy as np
import os
import sys
import subprocess
tile_size = ["1 80 128", "50 80 64", "4 4 1", "8 8 1", "4 4 8", "4 2 4", "4 2 2", "4 8 16", "8 4 16", "8 4 8", "4 2 8", "4 4 2", "4 4 4", "32 64 8", "32 64 16", "16 32 8", "128 224 32", "192 160 32", "48 72 12", "64 96 16"]
command1 = "./pocc-1.4/bin/pocc --verbose --pluto --pluto-fuse maxfuse --pluto-tile  polybench-c-4.2.1-beta/linear-algebra/blas/gemm/gemm.c" 
command2 = "gcc -O3 polybench-c-4.2.1-beta/linear-algebra/blas/gemm/gemm.pocc.c polybench-c-4.2.1-beta/utilities/polybench.c -Ipolybench-c-4.2.1-beta/utilities -DPOLYBENCH_TIME -o gemm.transfo"
command3 = "./gemm.transfo | awk '{print $1}'"
if(os.path.isfile('opfile.txt')):
    os.remove('opfile.txt')
for i in range(len(tile_size)):
    with open('tile.sizes', 'w') as inp:
        inp.write(str(tile_size[i]))
    print tile_size[i]
    os.system(command1)
    os.system(command2)
    with open('opfile.txt','a') as out:
            x = subprocess.check_output(command3,shell = True)
            out.write(str(tile_size[i])+ '->'+x)
d = {}
with open ('opfile.txt', 'r') as op:
    for line in op:
        (key,val) = line.split('->')
        d[key] = float(val.replace('\n', ''))
a =  sorted(d.iteritems(),key = lambda (k,v):(v,k))
for key,val in a:
	print "%s: %f"% (key,val)
print a[0]


    	  
