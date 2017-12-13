#Exercise 3
#! /usr/bin/python
import os
import subprocess
import tempfile
commands =  ['./pocc-1.4/bin/pocc --verbose --pluto-fuse maxfuse --pluto-tile polybench-c-4.2.1-beta/stencils/heat-3d/heat-3d.c', 
	    './pocc-1.4/bin/pocc --verbose --pluto-fuse maxfuse --pluto-parallel --pluto-tile polybench-c-4.2.1-beta/stencils/heat-3d/heat-3d.c', 
	    './pocc-1.4/bin/pocc --verbose --pluto-fuse smartfuse --pluto-tile polybench-c-4.2.1-beta/stencils/heat-3d/heat-3d.c',
	    './pocc-1.4/bin/pocc --verbose --pluto-fuse smartfuse --pluto-parallel --pluto-tile polybench-c-4.2.1-beta/stencils/heat-3d/heat-3d.c',             
	    './pocc-1.4/bin/pocc --verbose --pluto-fuse nofuse --pluto-tile polybench-c-4.2.1-beta/stencils/heat-3d/heat-3d.c',
	    './pocc-1.4/bin/pocc --verbose --pluto-fuse nofuse --pluto-parallel --pluto-tile polybench-c-4.2.1-beta/stencils/heat-3d/heat-3d.c']
command2 = 'gcc -O3 polybench-c-4.2.1-beta/stencils/heat-3d/heat-3d.pocc.c polybench-c-4.2.1-beta/utilities/polybench.c -Ipolybench-c-4.2.1-beta/utilities -DPOLYBENCH_TIME -o heat-3d.transfo'
command3 = './heat-3d.transfo'
outputlist = []
inputlist = ['1 80 128', '50 80 64', '250 200 210', '300 210 220', '350 220 230', '400 625 900', '192 32 15', '100,100,100', '480 480 4800', '100 25 30','20 25 100','20 100 100', '64 450 400', '1000 250  500','45 50 47','50 400 47','50 50 250','220 50 48','220 210 250','275 480 438']
for y in range(len(commands)):
	for x in range(len(inputlist)):
			with open("tile.sizes.txt", "w") as output:
				output.write(str(inputlist[x]))
			os.system(commands[y])
			os.system(command2)
			with tempfile.TemporaryFile() as tempf:
				proc = subprocess.Popen(command3,stdout=tempf)
				proc.wait()
				tempf.seek(1)
				data = tempf.read()
				outputlist.append(data)
print "Tile sizes->", inputlist
print "execution times->", outputlist
pragma_list = ['./pocc-1.4/bin/pocc --verbose --pluto-pragmatizer polybench-c-4.2.1-beta/stencils/heat-3d/heat-3d.c',
	      './pocc-1.4/bin/pocc --verbose --pluto-fuse maxfuse --pragmatizer --pluto-tile polybench-c-4.2.1-beta/stencils/heat-3d/heat-3d.c',
	      './pocc-1.4/bin/pocc --verbose --pluto-fuse maxfuse --pragmatizer --pluto-parallel --pluto-tile polybench-c-4.2.1-beta/stencils/heat-3d/heat-3d.c',
	      './pocc-1.4/bin/pocc --verbose --pluto-fuse smartfuse --pragmatizer --pluto-tile polybench-c-4.2.1-beta/stencils/heat-3d/heat-3d.c',
	      './pocc-1.4/bin/pocc --verbose --pluto-fuse smartfuse --pragmatizer --pluto-parallel --pluto-tile polybench-c-4.2.1-beta/stencils/heat-3d/heat-3d.c',
	      './pocc-1.4/bin/pocc --verbose --pluto-fuse nofuse --pragmatizer --pluto-tile polybench-c-4.2.1-beta/stencils/heat-3d/heat-3d.c',
	      './pocc-1.4/bin/pocc --verbose --pluto-fuse nofuse --pragmatizer --pluto-parallel --pluto-tile polybench-c-4.2.1-beta/stencils/heat-3d/heat-3d.c']
command4 ='gcc -O3 -fopenmp polybench-c-4.2.1-beta/stencils/heat-3d/heat-3d.c polybench-c-4.2.1-beta/utilities/polybench.c -Ipolybench-c-4.2.1-beta/utilities -DPOLYBENCH_TIME -o heat-3d.transfo'
command5 = './heat-3d.par.transfo'
for z in range(len(pragma_list)):
	for m in range(len(inputlist)):
			with open("tile.sizes.txt", "w") as output:
				output.write(str(inputlist[m]))
			os.system(pragmalist[z])
			os.system(command4)
			with tempfile.TemporaryFile() as tempf:
				proc = subprocess.Popen(command5, stdout=tempf)
				proc.wait()
				tempf.seek(1)
				data = tempf.read()
				outputlist.append(data)
print "Tile sizes->", inputlist
print "execution times->", outputlist
print "min execution time-> ", min(outputlist)
		



