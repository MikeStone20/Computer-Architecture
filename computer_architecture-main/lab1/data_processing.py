import matplotlib.pyplot as plt
import os
import numpy as np

files = [f for f in os.listdir('.') if os.path.isfile(f) and 'txt' in f]
tick_avgs = []
sizes = []

def raw_print(f):	
	raw_data = open(f,'r')
	strip_newline = raw_data.read().split('\n')
	x_axis = []
	y_axis = []
	total = 0
	for point in strip_newline:
		if(len(point) > 0):
			split_cor = point.split(':')
			if('Total' in split_cor[0]):
				total = split_cor[1]
			else:
				x_axis.append(int(split_cor[0]))
				y_axis.append(int(split_cor[1]))
	plt.plot(x_axis,y_axis)
	plt.xlabel("cycle number")
	plt.ylabel("number of ticks");
	plt.title(f.split('.')[0])
	plt.show()
	clean_print(x_axis,y_axis,f.split('.')[0])

def clean_print(x_axis,y_axis,name):
	list_len = len(x_axis)
	tuple_vals = []
	for i in range(list_len):
		tuple_vals.append((x_axis[i],y_axis[i]))
	tuple_vals.sort(key=lambda tup: tup[1])

	x_axis_clean = []
	y_axis_clean = []
	total = 0

	for i in range(10):
		tuple_vals.pop(0)
	for i in range(10):
		tuple_vals.pop(len(tuple_vals)-1)

	y_largest = tuple_vals[len(tuple_vals)-1][1];
	y_largest_percent = int(y_largest / 10 )
	tuple_vals.sort(key=lambda tup: tup[0])
	for i in range(len(tuple_vals)):
		x_axis_clean.append(tuple_vals[i][0])
		y_axis_clean.append(tuple_vals[i][1])
		total = total + tuple_vals[i][1]

	tick_avgs.append(total/980)
	sizes.append(name.split("_")[0])		
	plt.scatter(x_axis_clean,y_axis_clean)
	plt.xlabel("cycle number clean")
	plt.ylabel("number of ticks");
	plt.xticks(np.arange(0,x_axis_clean[len(x_axis_clean)-1],50))
	plt.yticks(np.arange(0,y_largest,y_largest_percent))
	plt.title(name+" clean")
	plt.show()

			

for f in files:
	raw_print(f)

for i in range(len(tick_avgs)):
	print(str(sizes[i]) + ": " + str(tick_avgs[i]))

tuple_avgs = tuple(tick_avgs)
y_pos = np.arange(len(tick_avgs))
plt.bar(y_pos,tick_avgs,align='center',alpha=0.5)
plt.xticks(y_pos,sizes)
plt.ylabel("Average Ticks")
plt.title("Average Ticks Between Different Sizes")
plt.show()

