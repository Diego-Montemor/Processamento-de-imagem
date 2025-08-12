# Processamento de Imagem

Sistema de processamento de imagens desenvolvido em C++ que permite manipular imagens no formato PGM (Portable Gray Map) utilizando ponteiros para operações eficientes de memória.

## 📋 Descrição

Este projeto implementa um sistema completo de processamento de imagens com as seguintes funcionalidades:

- ✅ Leitura de imagens no formato PGM (P2)
- ✅ Ajuste de brilho
- ✅ Rotação de imagem (90°, 180°, -90°)
- ✅ Inversão de cores (negativo)
- ✅ Binarização (preto e branco)
- ✅ Iconização (redimensionamento para 64x64 pixels)
- ✅ Salvamento de imagens processadas

## 🎯 Objetivo Acadêmico

**Disciplina:** AEDs 1 (Prática)  
**Professor:** Paulo Alexandre Bressan  
**Autor:** Diego Vianna Leite Montemor  
**Matrícula:** 2025.1.08.023

O projeto visa implementar conceitos de:

- Manipulação de ponteiros em C++
- Alocação dinâmica de memória
- Processamento de arquivos
- Algoritmos de processamento de imagens

## 🚀 Como Usar

### Pré-requisitos

- Compilador C++ (g++, Visual Studio, etc.)
- Imagem no formato PGM (P2) chamada `converted_image.pgm` no diretório do projeto

### Compilação

```bash
g++ -o processamento main.cpp
```

### Execução

```bash
./processamento
```

### Menu de Opções

Ao executar o programa, você verá o seguinte menu:

```
Digite a opção desejada:
1. ajustar o brilho da imagem
2. rotacionar a imagem
3. inverter as cores da imagem
4. binarizar a imagem
5. iconizar a imagem
0. Sair
```

## 📁 Estrutura do Projeto

```
Processamento-de-imagem/
├── main.cpp              # Código fonte principal
├── converted_image.pgm   # Imagem de entrada (formato PGM P2)
├── README.md            # Este arquivo
└── [arquivos gerados]   # Imagens processadas
```

## 🔧 Funcionalidades Detalhadas

### 1. Ajuste de Brilho

- **Arquivo gerado:** `ImagemComBrilhoAjustado.pgm`
- **Descrição:** Aumenta ou diminui o brilho da imagem
- **Entrada:** Valor numérico (positivo para clarear, negativo para escurecer)

### 2. Rotação de Imagem

- **Arquivo gerado:** `ImagemRotacionada.pgm`
- **Opções:** 90°, 180°, -90° (sentido horário)
- **Descrição:** Rotaciona a imagem no ângulo especificado

### 3. Inversão de Cores

- **Arquivo gerado:** `ImagemInversa.pgm`
- **Descrição:** Cria o negativo da imagem (255 - valor_pixel)

### 4. Binarização

- **Arquivo gerado:** `ImagemBinarizada.pgm`
- **Descrição:** Converte para preto e branco usando threshold 127
- **Lógica:** pixel > 127 → branco (255), caso contrário → preto (0)

### 5. Iconização

- **Arquivo gerado:** `ImagemIconizada.pgm`
- **Descrição:** Redimensiona a imagem para 64x64 pixels
- **Método:** Amostragem por fator de escala

## 📝 Formato de Arquivo Suportado

O programa trabalha exclusivamente com imagens no formato **PGM P2**:

```
P2
[largura] [altura]
255
[valores dos pixels separados por espaço]
```

### Exemplo de arquivo PGM:

```
P2
4 4
255
0 50 100 150
200 255 200 150
100 50 0 50
150 200 255 200
```

## ⚠️ Limitações e Considerações

- Formato suportado: apenas PGM P2
- Valores de pixel válidos: 0-255
- Arquivo de entrada deve se chamar `converted_image.pgm`
- Gerenciamento manual de memória (uso de `new` e `delete`)

## 🛠️ Implementação Técnica

### Estruturas de Dados

- Uso intensivo de ponteiros para manipulação eficiente de memória
- Arrays dinâmicos para armazenamento de pixels
- Ponteiros para controle de dimensões da imagem

### Algoritmos Implementados

- **Rotação:** Mapeamento de coordenadas com transformação matricial
- **Brilho:** Adição/subtração com clamp (0-255)
- **Binarização:** Threshold simples
- **Iconização:** Amostragem por fator de escala

## 📊 Exemplo de Uso

```cpp
// Leitura da imagem
int* imagem = lerImagem("converted_image.pgm", &linhas, &colunas);

// Ajuste de brilho (+50)
int* imagemClara = ajustarBrilho(imagem, &linhas, &colunas, 50);

// Salvamento do resultado
salvarImagem("resultado.pgm", imagemClara, &linhas, &colunas);
```

## 🔍 Validações Implementadas

- Verificação do formato PGM (P2)
- Validação de valores de pixel (0-255)
- Verificação de opções de menu válidas
- Controle de limites para ajuste de brilho

## 📝 Licença

Este projeto é desenvolvido para fins acadêmicos como parte da disciplina AEDs 1.
