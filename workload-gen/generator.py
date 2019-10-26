import random

n_inserts = 100000
n_reads = 100000

filename = "workload6"
max_n = 2147483647
min_n = -max_n

f= open(filename+".txt","w+")
ns = []

for i in range(n_inserts):
	rand_n = int(random.triangular(min_n,max_n,10))
	ns.append(rand_n)
	text_i = "p "+str(rand_n)+" "+str(rand_n)+"\n"
	f.write(text_i)

for i in range(n_reads):
        text_g = "g "+str(ns[i])+"\n"
        f.write(text_g)


f.close()
