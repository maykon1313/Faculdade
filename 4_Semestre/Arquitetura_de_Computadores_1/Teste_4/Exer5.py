from dataclasses import dataclass
from typing import List
from collections import deque
import math

@dataclass
class CacheBlock:
    # Representa um bloco individual da cache
    valid: bool = False  # Bit de validade
    tag: int = 0  # Tag do endereço
    data: List[int] = None  # Dados armazenados (palavras)
    
    def __post_init__(self):
        if self.data is None: self.data = []

class CacheSet:
    # Representa um conjunto (set) na cache associativa
    def __init__(self, associativity, words_per_block):
        self.blocks = [CacheBlock(data=[0] * words_per_block) for _ in range(associativity)]
        self.lru_queue = deque(range(associativity))  # Para política LRU
        
    def find_block(self, tag):
        # Procura um bloco com a tag especificada
        for i, block in enumerate(self.blocks):
            if block.valid and block.tag == tag: return i
        return None
    
    def get_lru_block(self):
        # Retorna o índice do bloco menos recentemente usado
        return self.lru_queue[0]
    
    def update_lru(self, block_index):
        # Atualiza a fila LRU após um acesso
        if block_index in self.lru_queue: self.lru_queue.remove(block_index)
        self.lru_queue.append(block_index)

class CacheSimulator:
    # Simulador de memória cache
    
    # Tamanho total em bytes, N-way (1=direct-mapped, total_blocks=fully-associative), Tamanho do bloco em bytes, Tamanho da palavra em bytes.
    def __init__(self, cache_size, associativity, block_size, word_size = 4):        
        self.word_size = word_size
        self.block_size = block_size
        self.words_per_block = block_size // word_size
        self.associativity = associativity
        
        # Calcula número de conjuntos
        total_blocks = cache_size // block_size
        self.num_sets = total_blocks // associativity
        
        # Calcula bits para offset, index e tag
        self.offset_bits = int(math.log2(block_size))
        self.index_bits = int(math.log2(self.num_sets))
        self.tag_bits = 32 - self.offset_bits - self.index_bits
        
        # Cria a estrutura da cache
        self.cache = [CacheSet(associativity, self.words_per_block) for _ in range(self.num_sets)]
        
        # Estatísticas
        self.hits = 0
        self.misses = 0
        self.accesses = 0
        
    def parse_address(self, address):
        # Decompõe o endereço em tag, index e offset
        offset = address & ((1 << self.offset_bits) - 1)
        index = (address >> self.offset_bits) & ((1 << self.index_bits) - 1)
        tag = address >> (self.offset_bits + self.index_bits)
        return tag, index, offset
    
    def access(self, address, operation = 'read'):
        # Simula um acesso à cache
        self.accesses += 1
        tag, index, offset = self.parse_address(address)
        
        cache_set = self.cache[index]
        block_index = cache_set.find_block(tag)
        
        # HIT
        if block_index is not None:
            self.hits += 1
            cache_set.update_lru(block_index)
            return True
        
        # MISS
        else:
            self.misses += 1
            # Seleciona bloco para substituição (LRU)
            victim_index = cache_set.get_lru_block()
            
            # Carrega novo bloco
            cache_set.blocks[victim_index].valid = True
            cache_set.blocks[victim_index].tag = tag
            cache_set.update_lru(victim_index)
            
            return False
    
    def get_statistics(self):
        # Retorna estatísticas da simulação
        hit_rate = (self.hits / self.accesses * 100) if self.accesses > 0 else 0
        miss_rate = (self.misses / self.accesses * 100) if self.accesses > 0 else 0
        return {'total_accesses': self.accesses, 'hits': self.hits, 'misses': self.misses, 'hit_rate': hit_rate, 'miss_rate': miss_rate}
    
    def print_configuration(self):
        # Imprime a configuração da cache
        print(f"Configuração da Cache")
        print(f"Tamanho total: {self.num_sets * self.associativity * self.block_size} bytes")
        print(f"Número de conjuntos: {self.num_sets}")
        print(f"Associatividade: {self.associativity}-way")
        print(f"Tamanho do bloco: {self.block_size} bytes")
        print(f"Palavras por bloco: {self.words_per_block}")
        print(f"Bits - Tag: {self.tag_bits}, Index: {self.index_bits}, Offset: {self.offset_bits}")
        print()

############################################################

def simulator(cache, addresses=None, trace=None):
    if (addresses != None):
        print("Simulando acessos:")
        for addr in addresses:
            result = cache.access(addr)
            status = "HIT" if result else "MISS"
            print(f"Endereço 0x{addr:04X}: {status}")

    else:
        print(f"Processando {len(trace)} acessos do trace...\n")
        for line in trace:
            addr = int(line.strip(), 16)
            cache.access(addr)
    
    print()
    stats = cache.get_statistics()
    print(f"Total de acessos: {stats['total_accesses']}")
    print(f"Hits: {stats['hits']}")
    print(f"Misses: {stats['misses']}")
    print(f"Taxa de acerto: {stats['hit_rate']:.2f}%")
    print(f"Taxa de falha: {stats['miss_rate']:.2f}%")
    print()

def exemplo_direct_mapped():
    print("EXEMPLO 1: Cache diretamente mapeada\n")
    
    # Cache de 1KB, direct-mapped, blocos de 64 bytes
    cache = CacheSimulator(cache_size=1024, associativity=1, block_size=64)
    
    cache.print_configuration()
    
    # Sequência de endereços de memória
    addresses = [0x0000, 0x0040, 0x0080, 0x0000, 0x0040, 0x1000, 0x1040, 0x0000]
    
    simulator(cache=cache, addresses=addresses)

# Exemplo 2: Cache 4-Way Set Associative
def exemplo_set_associative():
    print("EXEMPLO 2: 4-Way Set Associative Cache\n")
    
    # Cache de 2KB, 4-way, blocos de 32 bytes
    cache = CacheSimulator(cache_size=2048, associativity=4, block_size=32)
    
    cache.print_configuration()
    
    # Sequência de endereços com padrão de conflito
    addresses = [0x0000, 0x0800, 0x1000, 0x1800, 0x2000, 0x0000, 0x0800]
    
    simulator(cache=cache, addresses=addresses)

# Exemplo 3: Leitura de trace de arquivo
def exemplo_trace_file():
    print("EXEMPLO 3: Simulação com Arquivo de Trace\n")
    
    cache = CacheSimulator(cache_size=4096, associativity=2, block_size=64)
    
    # Simula leitura de arquivo de trace
    trace = """
    0x00001000
    0x00001040
    0x00002000
    0x00001000
    0x00003000
    0x00001040
    0x00002000
    """.strip().split('\n')
    
    simulator(cache=cache, trace=trace)

if __name__ == "__main__":
    exemplo_direct_mapped()
    exemplo_set_associative()
    exemplo_trace_file()
