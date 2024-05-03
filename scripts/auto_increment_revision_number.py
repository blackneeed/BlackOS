import sys

with open(sys.argv[1], 'r') as f:
    data = f.read()
    
revision_line = 0
foundRevisionLine = False

for i, line in enumerate(data.split('\n')):
    if line.split(" ")[0] != "#define":
        continue
    if line.split(" ")[1] != "REVISION_NUMBER":
        continue
    revision_line = i
    foundRevisionLine = True
    break

if foundRevisionLine:
    with open(sys.argv[1], 'w') as f:
        newLines = data.split('\n')
        newLines[revision_line] = newLines[revision_line].split(' ')
        newLines[revision_line][2] = str(int(newLines[revision_line][2]) + 1)
        newLines[revision_line] = ' '.join(newLines[revision_line])
        data = '\n'.join(newLines)
        f.write(data)