'''
    Nome: Ricardo Mendes Leal Junior
    RA: 562262
'''

import sys

def cifrador(content):
    l = ''

    for i in content:
        if i == '#':
            break

        res = ord(i) + 7

        if res > ord('z'):
            letter = res % ord('z')
            res = ord('a') + letter
            l += chr(res)
        else:
            l += chr(res)
    return l


# Se nao passar o nome do arquivo na linha de comando, encerra
if len(sys.argv) != 2:
    print ('USAGE:\npython3 cifrador.py <filename.txt>')
    exit()

# Lendo o arquivo
FILENAME = sys.argv[1]
fr = open(FILENAME, 'r')
content = fr.read()

l = cifrador(content)
l = str(l)

fw = open('cripto-' + FILENAME, 'w')
fw.write(l)