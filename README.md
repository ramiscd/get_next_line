# 🧠 get_next_line

> Projeto da [42 School](https://42.fr) que implementa uma função capaz de ler uma linha completa de um descritor de arquivo (`fd`), independentemente do tamanho do buffer.

---

## 📜 Descrição

A função `get_next_line()` lê **uma linha por chamada** a partir de um arquivo, stdin ou qualquer outro descritor.  
Ela **mantém o estado entre chamadas**, permitindo continuar a leitura exatamente de onde parou.

Esse projeto treina conceitos fundamentais de:
- leitura de arquivos com `read()`;
- manipulação de buffers;
- gerenciamento de memória dinâmica;
- e uso de variáveis `static`.

---

## ⚙️ Protótipo

```c
char *get_next_line(i
📂 Estrutura dos Arquivosnt fd);

📦 get_next_line/
├── get_next_line.c
├── get_next_line_utils.c
├── get_next_line.h
├── main.c              # arquivo opcional para testes
└── README.md
🧩 Arquivos e Funções
get_next_line.c

Contém a lógica principal da função:

Lê do descritor usando read();

Junta o conteúdo lido ao que restou da chamada anterior;

Retorna uma linha completa quando encontra \n ou EOF.

get_next_line_utils.c

Funções auxiliares de manipulação de strings:

Função	Descrição
ft_strdup()	Duplica uma string usando malloc().
ft_strlcpy()	Copia uma string com limite de tamanho seguro.
ft_substr()	Cria uma substring a partir de um índice inicial.
ft_strchr()	Procura o primeiro caractere c em uma string.
ft_strjoin()	Junta duas strings em uma nova alocação.
get_next_line.h

Declaração das funções;

Includes necessários (unistd.h, stdlib.h);

Definição do BUFFER_SIZE.

🧠 Lógica de Funcionamento

A função lê o arquivo em blocos de tamanho BUFFER_SIZE;

Armazena os dados lidos em um buffer estático para manter o estado entre chamadas;

Quando encontra um \n, retorna a linha completa;

O conteúdo após o \n é mantido para a próxima execução;

Quando o read() retorna 0 (EOF), a função retorna NULL.

⚠️ Detalhes Importantes

Variável estática: mantém o que sobrou do buffer entre as chamadas.

Gerenciamento de memória: cada malloc() deve ter um free() correspondente.

Vários descritores: o projeto deve funcionar com múltiplos fd ao mesmo tempo.

Retorno ao EOF: deve retornar a última linha mesmo que não termine com \n.

BUFFER_SIZE: o código precisa funcionar com qualquer valor (>0).

🧪 Como Testar o Projeto

Crie um arquivo main.c para testar a função:

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd = open("file.txt", O_RDONLY);
    char *line;

    if (fd < 0)
        return (1);

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }

    close(fd);
    return (0);
}

📌 Passo a passo:

Crie um arquivo de texto para testar:

echo -e "Linha 1\nLinha 2\nLinha 3" > file.txt


Compile o projeto:

cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl


Execute o programa:

./gnl


Saída esperada:

Linha 1
Linha 2
Linha 3


Teste com diferentes valores de BUFFER_SIZE:

cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 get_next_line.c get_next_line_utils.c main.c -o gnl_small
./gnl_small

🧰 Funções Permitidas

Apenas as seguintes funções da biblioteca padrão são permitidas:

read();
malloc();
free();

🧾 Exemplo de Fluxo Interno
[fd -> read()] --> [buffer temporário]
        ↓
[concatena com resto da leitura anterior]
        ↓
[encontra '\n'] → [retorna linha]
        ↓
[o resto é guardado para a próxima chamada]
