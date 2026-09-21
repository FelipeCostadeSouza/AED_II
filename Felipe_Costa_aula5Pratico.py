import os
import time
import heapq
import struct
import tempfile
import random

INT64_SIZE = 8
STRUCT_FMT = 'q'

def ler_int(f):
    buf = f.read(INT64_SIZE)
    return struct.unpack(STRUCT_FMT, buf)[0] if buf else None

def escrever_int(f, val):
    f.write(struct.pack(STRUCT_FMT, val))

def criar_arquivo_teste(caminho, quantidade):
    with open(caminho, 'wb') as f:
        for _ in range(quantidade):
            escrever_int(f, random.randint(-1_000_000, 1_000_000))

def verificar_ordenacao(caminho):
    with open(caminho, 'rb') as f:
        prev = ler_int(f)
        if prev is None:
            return True
        while True:
            curr = ler_int(f)
            if curr is None:
                return True
            if curr < prev:
                return False
            prev = curr
    return True

def intercalacao_balanceada(path_in, ram_limit=100):
    total_elems = os.path.getsize(path_in) // INT64_SIZE
    if total_elems <= ram_limit:
        _ordenar_ram_direto(path_in)
        return

    runs = []
    with open(path_in, 'rb') as f:
        while True:
            bloco = []
            for _ in range(ram_limit):
                val = ler_int(f)
                if val is None:
                    break
                bloco.append(val)
            if not bloco:
                break
            bloco.sort()
            t_file = tempfile.NamedTemporaryFile(delete=False)
            for item in bloco:
                escrever_int(t_file, item)
            t_file.close()
            runs.append(t_file.name)

    while len(runs) > 1:
        novos_runs = []
        for i in range(0, len(runs), 2):
            if i + 1 < len(runs):
                f_out = tempfile.NamedTemporaryFile(delete=False)
                _merge_2_arquivos(runs[i], runs[i+1], f_out.name)
                f_out.close()
                os.remove(runs[i])
                os.remove(runs[i+1])
                novos_runs.append(f_out.name)
            else:
                novos_runs.append(runs[i])
        runs = novos_runs

    _copiar_arquivo(runs[0], path_in)
    os.remove(runs[0])


def _merge_2_arquivos(p1, p2, p_out):
    with open(p1, 'rb') as f1, open(p2, 'rb') as f2, open(p_out, 'wb') as fout:
        v1, v2 = ler_int(f1), ler_int(f2)
        while v1 is not None and v2 is not None:
            if v1 <= v2:
                escrever_int(fout, v1)
                v1 = ler_int(f1)
            else:
                escrever_int(fout, v2)
                v2 = ler_int(f2)
        while v1 is not None:
            escrever_int(fout, v1)
            v1 = ler_int(f1)
        while v2 is not None:
            escrever_int(fout, v2)
            v2 = ler_int(f2)


def quicksort_externo(path_in, ram_limit=100):
    total_elems = os.path.getsize(path_in) // INT64_SIZE
    if total_elems <= ram_limit:
        _ordenar_ram_direto(path_in)
        return

    buf_size = max(1, ram_limit // 2)
    pilha_arquivos = [path_in]
    arquivos_finais = []

    while pilha_arquivos:
        curr_path = pilha_arquivos.pop()
        t_bytes = os.path.getsize(curr_path)
        c_elems = t_bytes // INT64_SIZE

        if c_elems == 0:
            if curr_path != path_in and os.path.exists(curr_path):
                os.remove(curr_path)
            continue

        if c_elems <= ram_limit:
            _ordenar_ram_direto(curr_path)
            arquivos_finais.append(curr_path)
            continue

        f_menores = tempfile.NamedTemporaryFile(delete=False)
        f_maiores = tempfile.NamedTemporaryFile(delete=False)
        buffer_pivos = []

        with open(curr_path, 'rb') as f_in:
            for _ in range(buf_size):
                v = ler_int(f_in)
                if v is not None:
                    buffer_pivos.append(v)
            buffer_pivos.sort()

            while True:
                item = ler_int(f_in)
                if item is None:
                    break

                if item < buffer_pivos[0]:
                    escrever_int(f_menores, item)
                elif item > buffer_pivos[-1]:
                    escrever_int(f_maiores, item)
                else:
                    escrever_int(f_menores, buffer_pivos[0])
                    buffer_pivos.pop(0)
                    buffer_pivos.append(item)
                    buffer_pivos.sort()

        f_menores.close()
        f_maiores.close()

        f_buffer = tempfile.NamedTemporaryFile(delete=False)
        for val in buffer_pivos:
            escrever_int(f_buffer, val)
        f_buffer.close()

        if curr_path != path_in and os.path.exists(curr_path):
            os.remove(curr_path)

        
        pilha_arquivos.append(f_maiores.name)
        pilha_arquivos.append(f_buffer.name)
        pilha_arquivos.append(f_menores.name)

   
    with open(path_in, 'wb') as f_dest:
        for p in arquivos_finais:
            _copiar_conteudo_stream(p, f_dest)
            if p != path_in and os.path.exists(p):
                os.remove(p)

def _ordenar_ram_direto(path):
    dados = []
    with open(path, 'rb') as f:
        while True:
            v = ler_int(f)
            if v is None:
                break
            dados.append(v)
    dados.sort()
    with open(path, 'wb') as f:
        for v in dados:
            escrever_int(f, v)

def _copiar_arquivo(origem, destino):
    with open(origem, 'rb') as f_in, open(destino, 'wb') as f_out:
        _copiar_conteudo_stream_from_f(f_in, f_out)

def _copiar_conteudo_stream(path_origem, stream_dest):
    if os.path.exists(path_origem):
        with open(path_origem, 'rb') as f_in:
            _copiar_conteudo_stream_from_f(f_in, stream_dest)

def _copiar_conteudo_stream_from_f(f_in, f_out, chunk_size=65536):
    while True:
        buf = f_in.read(chunk_size)
        if not buf:
            break
        f_out.write(buf)

if __name__ == '__main__':
    QTD_ELEMENTOS = 10_000   
    LIMITE_RAM = 200         

    print(f"({QTD_ELEMENTOS} registros | RAM = {LIMITE_RAM} items)")
    

    
    arq_base = "dados_desordenados.bin"
    criar_arquivo_teste(arq_base, QTD_ELEMENTOS)

    algoritmos = [
        ("Intercalação Balanceada", intercalacao_balanceada),
        ("Quicksort Externo", quicksort_externo)
    ]

    for nome, algo_fn in algoritmos:
        
        arq_teste = f"teste_{random.randint(1000, 9999)}.bin"
        _copiar_arquivo(arq_base, arq_teste)

        inicio = time.perf_counter()
        algo_fn(arq_teste, ram_limit=LIMITE_RAM)
        fim = time.perf_counter()

        duracao_ms = (fim - inicio) * 1000
        valido = verificar_ordenacao(arq_teste)

        print(f"-> {nome}")
        print(f"   Tempo decorrido: {duracao_ms:.2f} ms\n")

        if os.path.exists(arq_teste):
            os.remove(arq_teste)

    if os.path.exists(arq_base):
        os.remove(arq_base)
