import sys

class Letra:
    def __init__(self, letra, qtdd):
        self.letra = letra
        self.qtdd = qtdd

if len(sys.argv) != 2:
    print ('USAGE:\npython3 cont.py <filename.txt>')
    sys.exit()

FILENAME = sys.argv[1]

abc = []
for i in range(ord('a'), ord('z')):
    abc.append(Letra(chr(i), 0))

f = open(FILENAME, 'r')

content = f.read()

for i in content:
    if i != '#':
        abc[ord(i) - ord('a')].qtdd += 1
    else:
        break

print ('Ordem alfabética')
for i in range(ord('a'), ord('z')):
    print (str(chr(i)) + ' = ' + str(abc[i - ord('a')].qtdd))

abc.sort(key=lambda obj: obj.qtdd, reverse=True)

print ('\nOrdem incidência')
for i in abc:
    print (i.letra + ' = ' + str(i.qtdd))
