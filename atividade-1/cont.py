import sys

# Definicao do obj Letra
class Letra:
    def __init__(self, letra, qtdd):
        self.letra = letra
        self.qtdd = qtdd

def menu():
    print ('\nPara trocar alguma letra')
    print ('Primeiro insira a letra que deseja substituir')
    print ('Em seguida insira a letra pela qual a anterior será substítuida')
    print ('\n0 - Zera a frase trocada')
    print ('1 - Imprime Frase original')
    print ('2 - Imprime Frase trocada')
    print ('3 - Trocar letra')
    print ('4 - Ver incidência frase original')
    print ('5 - Ver incidência frase trocada')
    print ('6 - Ver trocas realizadas')
    print ('Pressione CTRL+C para finalizar o programa')

#
def substui(content, letra1, letra2):
    l = []

    for i in content:
        if i == letra1:
            l.append(letra2)
        elif i == letra2:
            l.append(letra1)
        else:
            l.append(i)
    return l

# Calcula a ordem de incidencia
def incidencia(content, primeiro):
    # Inicializando a lista
    abc = []
    for i in range(ord('a'), ord('z') + 1):
        abc.append(Letra(chr(i), 0))

    for i in content:
        if i != '#':
            abc[ord(i) - ord('a')].qtdd += 1
        else:
            break

    if (primeiro):
        print ('Ordem alfabética')
        l = []
        for i in range(ord('a'), ord('z')):
            print (str(chr(i)) + ' = ' + str(abc[i - ord('a')].qtdd))
        abc.sort(key=lambda obj: obj.qtdd, reverse=True)
        return abc

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
content = list(f.read())
modified_flag, modified = False, ''

menu()
trocas = []

while True:
    try:
        opc = str(input())

        if opc == '0':
            modified_flag, modified, trocas = False, '', []
        elif opc == '1':
            for i in content:
                print (i, end='')
            print ('')
        elif opc == '2':
            for i in modified:
                print (i, end='')
            print ('')
        elif opc == '3':
            letra1 = str(input('Letra 1: '))
            letra2 = str(input('Letra 2: '))
            trocas.append([letra1, letra2])

            if not modified_flag:
                modified_flag, modified = True, substui(content, letra1, letra2)
            else:
                modified = substui(modified, letra1, letra2)
        elif opc == '4':
            incidencia(content, False)
        elif opc == '5':
            incidencia(modified, False)
        elif opc == '6':
            print ('Trocas realizadas:')
            for i in trocas:
                print (i[0] + ' -> ' + i[1])
        else:
            menu()
    except KeyboardInterrupt:
        print ('Bye')
        exit()
