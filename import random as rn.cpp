import random as rn
import sys

adj_mat = [[0,1,1,1,0,0,0,0,0,0,0,0],[0,0,0,0,1,1,1,0,0,0,0],[0,0,0,0,1,1,1,0,0,0,0],[0,0,0,0,1,1,1,0,0,0,0],[0,0,0,0,0,0,0,1,1,1,0],[0,0,0,0,0,0,0,1,1,1,0],[0,0,0,0,0,0,0,1,1,1,0],[0,0,0,0,0,0,0,0,0,0,1],[0,0,0,0,0,0,0,0,0,0,1],[0,0,0,0,0,0,0,0,0,0,1],[0,0,0,0,0,0,0,0,0,0,0]]
#adj_mat = 2 * adj_mat
t = [[5,6,7,5,5],[3,2,2,2,3],[4,3,3,2,3],[9,8,8,8,9],[3,3,3,3,3],[7,6,6,7,6],[4,3,3,4,3],[8,7,7,6,8],[3,2,3,2,3],[3,4,3,4,4],[5,5,5,5,5]]


# 	print P[i],
# print "\n"



for i in range(len(adj_mat)):
	for j in range(len(adj_mat)):
		adj_mat[i][j] *= 2
	# 	print adj_mat[i][j],
	# print "\n"



PRED = [[]]
for i in range(11):
	for j in range(11):
		if (adj_mat[j][i] > 0):
			PRED[i].append(j)
	PRED.append([])
PRED.pop()

# for i in range(len(PRED)):
# 	print PRED[i]


SUCC = [[]]
for i in range(11):
	for j in range(11):
		if (adj_mat[i][j] > 0):
			SUCC[i].append(j)
	SUCC.append([])
SUCC.pop()

# for i in range(len(SUCC)):
# 	print SUCC[i]


fproc = []
dummy = t[0][:]
dummy2 = []
for i in range(len(t[0])):
	min = 0
	for j in range(len(dummy)):
		if (dummy[min] > dummy[j]):
			min = j
	dummy[min] = sys.maxint
	dummy2.append(min)
fproc.append(dummy2)


est = [0]
est1 = [[0,0,0,0,0]]
ect = [est[0] + t[0][fproc[0][0]]]
for i in range(1,11):
	favpre = PRED[i][:]
	esti = []
	max1 = 0
	for k in range(len(t[i])):
		for j in range(len(favpre)):
			if (fproc[favpre[j]][0] == k):
				if (max1 < ect[favpre[j]]):
					max1 = ect[favpre[j]]
			else:
				if (max1 < ect[favpre[j]] + adj_mat[j][i]):
					max1 = ect[favpre[j]] + adj_mat[j][i]
		esti.append(max1)
	est1.append(esti)
	favpro = []
	for k in range(len(t[i])):
		favpro.append(est1[i][k] + t[i][k])
	favpro1 = []

	for k in range(len(favpro)):
		min1 = sys.maxint
		min2 = 0
		for j in range(len(favpro)):
			if (favpro[j] < min1):
				min2 = j
		favpro[min2] = sys.maxint
		favpro1.append(min2)

	fproc.append(favpro1)
	har = est1[i][fproc[i][0]]
	est.append(est1[i][fproc[i][0]])
	ect.append(har + t[i][fproc[i][0]])



lact = [0,0,0,0,0,0,0,0,0,0,ect[10]]
last = [0,0,0,0,0,0,0,0,0,0,lact[10] - t[10][fproc[10][0]]]

fpred = [[],[],[],[],[],[],[],[],[],[],[]]

for i in range(1,11):
	favpre = PRED[i][:]
	
	val = []
	for k in range(len(favpre)):
		max1 = -(sys.maxint - 1)
		ind = 0
		for j in range(len(favpre)):
			if (max1 < ect[favpre[j]] + adj_mat[favpre[j]][i]):
				val.append(favpre[j])
				ind = j
				max1 = ect[favpre[j]] + adj_mat[favpre[j]][i]
		del(favpre[ind])
	fpred[i] = val



i = 9
while (i>=0):
	favsuc = SUCC[i][:]
	min1 = sys.maxint
	for j in range(len(favsuc)):
		if (i == fpred[favsuc[j]]):
			if (min1 > last[favsuc[j]]):
				min1 = last[favsuc[j]]
			else:
				min1 = last[favsuc[j]] - adj_mat[i][favsuc[j]]
	lact[i] = min1
	last[i] = lact[i] - t[i][fproc[i][0]]
	i = i - 1









level = [0,0,0,0,0,0,0,0,0,0,0]
sum = 0
for i in range(11):
	val = max(t[10-i])
	max1 = 0
	for j in range(len(SUCC[10-i])):
		if (max1 < level[SUCC[10-i][j]]):
			max1 = level[SUCC[10-i][j]]
	level[10-i] = val + max1



level_copy = level[:]
queue = []

for i in range(len(level)):
	min = 0
	for j in range(len(level_copy)):
		if (level_copy[min] > level_copy[j]):
			min = j
	queue.append(min)
	# print level_copy
	level_copy[min] = sys.maxint


P_Flag = []
P = []
for i in range(5):
	P.append([]);
	P_Flag.append(0)

print "Time table where t(i,j) is time taken by ith task if it runs on jth processor."
print "Prcr/Tsk 1  2  3  4  5"
for i in range(len(t)):
	print i,"\t",t[i]
print "\n\n\n"

print "Earliest starting time of ith task:"

print est
print "\n\n\n"

print "Earliest completion time of ith task:"

print ect
print "\n\n\n"

print "Favourite Processer order of ith task:"
for i in range(len(t)):
	print fproc[i]
print "\n\n\n"

print "Level of each task:"

print level
print "Queue of tasks:"
print queue
print "\n\n\n"


while (len(queue) > 1):
	x = queue.pop(0)
	cur_proc = fproc[x][0]
	i = 0
	while (i<5):
		if (P_Flag[fproc[x][i]] == 0):
			cur_proc = fproc[x][i]
			break;
		else:
			i += 1
	P_Flag[cur_proc] = 1
	h = 0 
	for i in range(5):
		if (P_Flag[i] == 1):
			h += 1
	if (h == 5):
		break;
	# print P_Flag
	# print cur_proc
	# for i in range(t[x][cur_proc]):
	P[cur_proc].append(x)
	while (x is not 0):
		y = fpred[x][0]
		for i in range(len(fpred[x])):
			if (y not in queue):
				y = fpred[x][i]
		# for i in range(t[y][cur_proc]):
		int2 = []
		for i in range(len(queue)):
			if (y == queue[i]):
				int2.append(i)
		for i in range(len(int2)):
			del(queue[int2[i]])
		P[cur_proc].append(y)
		x = y
	# for i in range(t[x][cur_proc]):
	# P[cur_proc].append(x)

R = P[:]

for i in range(len(P)):
	R[i] = []
	print P[i],"  ",i
	for k in range(len(P[i])):
		for m in range(t[P[i][k]][i]):
			R[i].append(P[i][k])


for i in range(len(R)):
	R[i].reverse()
	print i, "th Processor: ",R[i]
