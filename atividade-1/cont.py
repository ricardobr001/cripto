import sys

# Definicao do obj Letra
class Letra:
    def __init__(self, letra, qtdd):
        self.letra = letra
        self.qtdd = qtdd

# Calcula a ordem de incidencia
def incidencia(content, primeiro):
    # Inicializando a lista
    abc = []
    for i in range(ord('a'), ord('z')):
        abc.append(Letra(chr(i), 0))

    for i in content:
        if i != '#':
            abc[ord(i) - ord('a')].qtdd += 1
        else:
            break

    if (primeiro):
        print ('Ordem alfabética')
        for i in range(ord('a'), ord('z')):
            print (str(chr(i)) + ' = ' + str(abc[i - ord('a')].qtdd))

    abc.sort(key=lambda obj: obj.qtdd, reverse=True)

    print ('\nOrdem incidência')
    for i in abc:
        print (i.letra + ' = ' + str(i.qtdd))

# Se nao passar o nome do arquivo na linha de comando, encerra
if len(sys.argv) != 2:
    print ('USAGE:\npython3 cont.py <filename.txt>')
    exit()

# Lendo o arquivo
FILENAME = sys.argv[1]
f = open(FILENAME, 'r')
content = f.read()
modified = ''

# Calculando a incidencia
incidencia(content, True)

print ('\nPara trocar alguma letra')
print ('Primeiro insira a letra que deseja substituir')
print ('Em seguida insira a letra pela qual a anterior será substítuida')
print ('\n1 - Imprime Frase original')
print ('2 - Imprime Frase trocada')
print ('3 - Trocar letra')
print ('Pressione CTRL+C para finalizar o programa')

while True:
    try:
        opc = str(input())
        if opc == '1':
            print (content)
        elif opc == '2':
            print (modified)
        else:
            letra1 = str(input())
            letra2 = str(input())
            modified = content.replace(letra1, letra2)
            incidencia(modified, False)
    except:
        print ('Bye')
        exit()
