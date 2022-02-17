import matplotlib.pyplot as plt
import os
import numpy 



files = [f for f in os.listdir('.') if os.path.isfile(f) and 'txt' in f]
tick_avgs = []
x_axis = []
datatype = [('index',numpy.float32)]

for i in range(1,22804):
	x_axis.append(i)


def raw_print(f):	
	# raw_data = open(f,'r')
	# strip_newline = raw_data.read().split('\n')
	# x_axis = []
	# y_axis = []
	# total = 0
	# counter = 1
	# for point in strip_newline:
	# 	x_axis.append(counter)
	# 	y_axis.append(point)
	# 	counter += 1
	# plt.plot(x_axis,y_axis)
	# plt.xlabel("Test Number")
	# plt.ylabel("Number of Ticks");
	# plt.title(f.split('.')[0])
	# plt.show()
    data = numpy.memmap(f, datatype, 'r') 
    plt.plot(x_axis,data['index'],'r,')
    plt.title(f.split('.')[0])
    plt.xlabel("Test Number")
    plt.ylabel("Number of Ticks")
    plt.savefig('foo3.png')

for f in files:
	if 'base' in f:
		raw_print(f)