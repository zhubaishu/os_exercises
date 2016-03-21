
import random

blockNum = 16
T = 1000
window = 10
work = []
mem = set([])
miss = 0

for i in range(0, T) :
   
    block = random.randint(0, blockNum)
    
    if not (block in mem) :
        miss = miss + 1
        
    mem.add(block)
    work.append(block)
    
    if len(work) > window :
        removedBlock = work[0]
        if work.count(removedBlock) == 1 :
            mem.remove(removedBlock)    
        work = work[1:]

print "miss ratio : "
print miss * 1.0 / n
