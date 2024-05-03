import sys

with open(sys.argv[1], 'r') as f:
    data = f.read()
    
for line in data.split('\n'):
    if line.split(" ")[0] != "#define":
        continue
    if line.split(" ")[1] != "REVISION_NUMBER":
        continue
    print(line.split(" ")[2])
    break