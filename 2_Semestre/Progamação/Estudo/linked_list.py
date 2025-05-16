class Node:
    def __init__(self, data):
        self.data = data
        self.next = None
        
class LinkedList:
    def __init__(self):
        self.head = None
        self._size = 0
    
    def __append__(self, elem):
        if self.head:
            pointer = self.head
            while (pointer.next):
                pointer = pointer.next
            
            pointer.next = Node(elem)
        else:
            self.head = Node(elem)
        self._size += 1
    
    def __len__(self):
        return self._size

    def __getitem__(self, index):
        pointer = self.head
        for i in range(index):
            if pointer:
                pointer = pointer.next
            else:
                raise IndexError("Tá indo longe de mais.")
        if pointer:
            return pointer.data
        else:
            raise IndexError("Tá indo longe de mais.")
    
    def __setitem__(self, index, elem):
        pointer = self.head
        for i in range(index):
            if pointer:
                pointer = pointer.next
            else:
                raise IndexError("Tá indo longe de mais.")
        if pointer:
            pointer.data = elem
        else:
            raise IndexError("Tá indo longe de mais.")
    
    def index(self, elem):
        pointer = self.head
        i = 0
        while(pointer):
            if pointer.data == elem:
                return i
            pointer = pointer.next
            i += 1
        raise ValueError("Tá aqui não.")



lista = LinkedList()

while True:
    print("1 - Append.")
    print("2 - Len.")
    print("3 - Get item.")
    print("4 - Set Item.")
    print("5 - Index.")
    print("6 - Sair.")

    escolha = int(input())

    match escolha:
        case 1:
            elem = int(input("Adicionar elemento:\n"))
            lista.__append__(elem)
        
        case 2:
            print("O tamanho do vetor é: {}.".format(lista.__len__()))
        
        case 3:
            index = int(input("Qual o index?\n"))
            elem = lista.__getitem__(index)
            print("O valor nesse index é: {}.".format(elem))
        
        case 4:
            index = int(input("Qual o index?\n"))
            elem_novo = int(input("Qual o novo elemento?\n"))
            lista.__setitem__(index, elem_novo)
        
        case 5:
            elem = int(input("Qual o elemento?\n"))
            index = lista.index(elem)
            print("O index desse valor é: {}.".format(index))
        
        case 6:
            break

