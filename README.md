# Recommendation System ADS

TODO:
- Improve the topK definition (give more weight to items that have a higher number of ratings even if their average rating is lower)
- Rehashing in the hash function
- Try to implement rehashing in the Cuckoo Filter or something equivalent like Dynamic Cuckoo Filter and run the benchmarks again to check for any improvement

## Integrantes do grupo
- Érico Meger
- Eros Henrique Lunardon Andrade

## Estrutura de arquivos 

### `main/include/`
- `recommender.hpp`: configuração e interface da classe `Recommender`.
- `cuckoo/`: headers do Cuckoo Filter.
- `cuckooFilter/`: headers relacionados ao filtro (estrutura auxiliar/legada).
- `factory/`: headers da fábrica de componentes (RNG/hash/estruturas).
- `hash/`: interfaces e tipos de hash/tabelas.
- `heap/`: interfaces e tipos de heap.
- `rng/`: interfaces e tipos de geradores/distribuições.

### `main/src/`
- `main.cpp`: parsing de argumentos e inicialização da aplicação.
- `recommender.cpp`: fluxo do sistema (geração, ranking, métricas).
- `cuckoo/`: implementação do Cuckoo Filter.
- `factory/`: implementação da fábrica.
- `hash/`: implementações de tabelas e funções hash.
- `heap/`: implementação do heap (Floyd).
- `rng/`: implementações dos geradores RNG.

### `main/tests/`
- `test_rng.cpp`: reprodutibilidade, reset e sanidade de distribuições.
- `test_hash.cpp`: inserção, busca, colisões e agregação por item.
- `test_heap.cpp`: ordem de heap, `push/pop/top`, `topK`.
- `test_cuckoo.cpp`: insert/query/delete e taxa de falso positivo.
- `run_tests.sh`: execução dos testes.
- `makefile`: compilação dos testes.

### `main/benchmarks/`
- `benchmark_rng.cpp`: benchmark de RNG.
- `benchmark_hash.cpp`: benchmark de hash table/colisões/fator de carga.
- `benchmark_cuckoo.cpp`: benchmark de Cuckoo Filter.
- `benchmark_system.cpp`: benchmark do sistema completo.
- `run_benchmarks.sh`: compila e executa benchmarks.

## Como compilar e executar o programa principal

### 1) Compilar
```bash
make
```

### 2) Executar (configuração padrão)
```bash
make run
```

### 3) Executar com Cuckoo Filter
```bash
make run-cuckoo
```

### 4) Executar manualmente com parâmetros
```bash
./recsys --seed 67 --users 100 --items 50 --ratings 1000 --topk 5
```

Exemplo com cuckoo:
```bash
./recsys --seed 67 --users 100 --items 50 --ratings 1000 --topk 5 --cuckoo
```

## Como executar os testes

### Opção A (script)
```bash
cd main/tests
bash run_tests.sh
```

### Opção B (make dos testes)
```bash
cd main/tests
make
./test_rng
./test_hash
./test_heap
./test_cuckoo
```

## Como executar benchmarks
```bash
cd main/benchmarks
bash run_benchmarks.sh
```

