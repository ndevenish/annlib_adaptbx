import math
from annlib_ext import AnnAdaptor
from scitbx.array_family import flex

data = flex.double()
query = flex.double()

D = open("../tests/data.pts")
for line in D.xreadlines():
  point = line.strip().split(" ")
  data.push_back(float(point[0]))
  data.push_back(float(point[1]))

Q = open("../tests/query.pts")
for line in Q.xreadlines():
  point = line.strip().split(" ")
  query.push_back(float(point[0]))
  query.push_back(float(point[1]))

A = AnnAdaptor(data,2)

A.query(query)

for i in xrange(len(A.nn)):
  break
  print query[2*i],query[2*i+1]
  print A.nn[i]
  print math.sqrt(A.distances[i])
