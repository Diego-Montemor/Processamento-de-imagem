#include <iostream>
#include <fstream>
#include <string>

using namespace std;
/*
Autor: Diego Vianna leite Montemor
Matricula: 2025.1.08.023

Professor: Paulo Alexandre Bressan
Materia: AEDs 1(pratica)

Objetivo: Implementar um sistema de processamento de imagens em C++ utilizando ponteiros,
          com as funções de ler imagem, salvar imagem, ajustar brilho, rotacionar imagem,
          inverter cores, binarizar imagem e iconizar imagem.
*/

// Função para ler uma imagem PGM (formato P2) e retornar um vetor de pixels
int* lerImagem(string caminhoDoArquivo, int* linhas, int* colunas) {
    ifstream arquivo(caminhoDoArquivo);
    string linha;
    // Descarta a primeira linha e verifica se é do tipo P2
    arquivo >> linha;
    if (linha != "P2") {
        cout << "A imagem não é P2" << endl;
        exit(1);
    }

    int valorMaximoDePixel;
    arquivo >> (*colunas);
    arquivo >> (*linhas);
    arquivo >> valorMaximoDePixel;

    int* imagem = new int[(*colunas) * (*linhas)];
    int* ponteiro = imagem;
    int pixel;
    
    // Lê todos os pixels da imagem e armazena no vetor
    while (arquivo >> pixel) {
        if (pixel < 0 or pixel > valorMaximoDePixel) { // Verifica se o pixel está dentro do intervalo válido
            cout << "A imagem contém pixels inválidos" << endl;
            exit(1);
        }
        *ponteiro = pixel;
        ponteiro++;
    }

    return imagem;
}

// Função para salvar uma imagem PGM (formato P2) a partir de um vetor de pixels
void salvarImagem(string caminhoDoArquivo, int* imagem, int* linhas, int* colunas) {
    ofstream arquivo(caminhoDoArquivo);

    arquivo << "P2" << endl;
    arquivo << *colunas << " " << *linhas << endl;
    arquivo << "255" << endl;

    int* fim = imagem + ((*linhas) * (*colunas));
    int* p = imagem;
    // Escreve todos os pixels no arquivo
    while (p < fim) {
        arquivo << *p << " ";
        p++;
    }
}

// Função para ajustar o brilho da imagem, criando uma nova imagem ajustada
int* ajustarBrilho(int* imagem, int* linhas, int* colunas, int ajuste) {
    int* novaImagem = new int[(*linhas) * (*colunas)];
    int* pxOriginal = imagem;
    int* pxNovo = novaImagem;
    int* fim = imagem + ((*linhas) * (*colunas));
    // Percorre todos os pixels, ajustando o brilho e limitando entre 0 e 255
    while (pxOriginal < fim) {
        *pxNovo = min(max(*pxOriginal + ajuste, 0), 255); // Garante que o valor esteja entre 0 e 255
        pxOriginal++;
        pxNovo++;
    }
    return novaImagem;
}

// Função para rotacionar a imagem 90 graus para a direita
int* rotacionarImagem(int* imagem, int* linhas, int* colunas) {
    int* novaImagem = new int[(*linhas) * (*colunas)];
    int* pxOriginal = imagem;
    int* pxNovo = novaImagem;

    int* pxColuna = colunas;
    int* pxLinha = linhas;
    int novaLinhas = *pxColuna;
    int novaColunas = *pxLinha;

    // Percorre as colunas e linhas para rotacionar a imagem
    int* i = new int(0);
    while (*i < *pxColuna) {
        int* j = new int(*pxLinha - 1);
        while (*j >= 0) {
            *pxNovo = *(pxOriginal + (*j) * (*pxColuna) + (*i));
            pxNovo++;
            (*j)--;
        }
        (*i)++;
        delete j;
    }
    // Troca os valores das linhas e colunas após rotacionar
    int temp = *pxLinha;
    *pxLinha = *pxColuna;
    *pxColuna = temp;
    delete i;
    return novaImagem;
}

// Função para inverter as cores da imagem (negativo)
int* inverterCores(int* imagem, int* linhas, int* colunas) {
    int* novaImagem = new int[(*linhas) * (*colunas)];
    int* pxOriginal = imagem;
    int* pxNovo = novaImagem;
    int* fim = imagem + ((*linhas) * (*colunas));

    // Para cada pixel, faz 255 - valor (inversão)
    while (pxOriginal < fim) {
        *pxNovo = 255 - *pxOriginal;
        pxOriginal++;
        pxNovo++;
    }
    
    return novaImagem;
}

// Função para binarizar a imagem (preto e branco)
int* binarizarImagem(int* imagem, int* linhas, int* colunas) {
    int* novaImagem = new int[(*linhas) * (*colunas)];
    int* pxOriginal = imagem;
    int* pxNovo = novaImagem;
    int* fim = imagem + ((*linhas) * (*colunas));

    // Para cada pixel, se maior que 127 vira 255, senão vira 0
    while (pxOriginal < fim) {// percorre todos os pixels trocando os valores
        if(*pxOriginal > 127) { // Se o pixel for maior que 127, deixa o pixel branco
            *pxNovo = 255;
        } else { // senao, deixa o pixel preto
            *pxNovo = 0;
        }
        pxOriginal++;
        pxNovo++;
    }

    return novaImagem;
}

// Função para reduzir a imagem para 64x64 pixels (iconizar)
int* iconizarImagem(int* imagem, int* linhas, int* colunas) {
    int* novaImagem = new int[64 * 64];
    // calcula os fatores de escala para linhas e colunas
    float fatorLinha = (float)(*linhas) / 64;
    float fatorColuna = (float)(*colunas) / 64;

    int* pxNova = novaImagem;
    int* pxI = new int(0);
    while (*pxI < 64) { // percorre as linhas da nova imagem
        // calcula a linha original correspondente na imagem original
        float linhaOriginalF = (*pxI) * fatorLinha;
        int linhaOriginal = (int)(linhaOriginalF);

        int* pxJ = new int(0);
        while (*pxJ < 64) { // percorre as colunas da nova imagem
            // calcula a coluna original correspondente na imagem original
            float colunaOriginalF = (*pxJ) * fatorColuna;
            int colunaOriginal = (int)(colunaOriginalF);

            int* pxOriginal = imagem + linhaOriginal * (*colunas) + colunaOriginal; // Pega o pixel original da imagem
            // Copia o valor do pixel original para a nova imagem
            *pxNova = *pxOriginal;
            pxNova++;
            (*pxJ)++;
        }
        delete pxJ;
        (*pxI)++;
    }
    delete pxI;

    return novaImagem;
}

int main() {
    int linhas, colunas;
    // Lê a imagem do arquivo e armazena as dimensões
    int* imagem = lerImagem("converted_image.pgm", &linhas, &colunas);

    int opcao;
    cout << "Digite a opção desejada:\n" 
         << "1. ajustar o brilho da imagem\n"
         << "2. rotacionar a imagem\n"
         << "3. inverter as cores da imagem\n"
         << "4. binarizar a imagem\n"
         << "5. iconizar a imagem\n"
         << "0. Sair\n"
         << "R: ";
    cin >> opcao;
    while(opcao != 0){
        switch (opcao) {
            case 1: {
                // Ajuste de brilho
                int ajuste;
                cout << "Digite o valor de ajuste de brilho (positivo para aumentar, negativo para diminuir): ";
                cin >> ajuste;
                int* imagemAjustada = ajustarBrilho(imagem, &linhas, &colunas, ajuste);
                salvarImagem("ImagemComBrilhoAjustado.pgm", imagemAjustada, &linhas, &colunas);
                cout << "brilho ajustado comm sucesso!" << endl;
                delete[] imagemAjustada;
                break;
            }
            case 2:{// Rotacionar imagem
                int angulo;
                cout << "Digite a rotação desejada\n1. 90°    2. 180°     3. -90°\nR: ";
                cin >> angulo;
                while (angulo < 1 and angulo > 3){ // Verifica se a opção é válida
                    cout << "Opção inválida, digite uma opção válida(1-3): ";
                    cin >> angulo;
                }
                int* imagemTemp = imagem; // Cria uma cópia da imagem original para rotacionar
                while(angulo > 0) { // Rotaciona a imagem 90 graus no sentido horário até o ângulo desejado
                    angulo--;
                    // Rotaciona a imagem 90 graus no sentido horário
                    int* imagemRotacionada = rotacionarImagem(imagemTemp, &linhas, &colunas);
                    delete[] imagemTemp; // Libera a memória da imagem anterior
                    imagemTemp = imagemRotacionada; // Atualiza a imagem para a nova imagem rotacionada
                }
                cout << "Imagem rotacionada com sucesso!" << endl;
                salvarImagem("ImagemRotacionada.pgm", imagemTemp, &linhas, &colunas);
                delete[] imagemTemp;
                break;}
            case 3:{// Inverter cores
                int* imagemInversa = inverterCores(imagem, &linhas, &colunas);
                cout << "cores invertidas com sucesso!" << endl;
                salvarImagem("ImagemInversa.pgm", imagemInversa, &linhas, &colunas);
                delete[] imagemInversa;
                break;
            }
            case 4:{// Binarizar imagem
                int* imagemBinarizada = binarizarImagem(imagem, &linhas, &colunas);
                cout << "imagem binarizada com sucesso!" << endl;
                salvarImagem("ImagemBinarizada.pgm", imagemBinarizada, &linhas, &colunas);
                delete[] imagemBinarizada;
                break;
            }
            case 5:{// Iconizar imagem para 64 x 64 pixels
                int* imagemIconizada = iconizarImagem(imagem, &linhas, &colunas);
                cout << "imagem iconizada com sucesso!" << endl;
                int tempLinhas = linhas; // Guarda o tamanho original das linhas
                int tempColunas = colunas; // Guarda o tamanho original das colunas
                linhas = 64; // Atualiza o tamanho das linhas
                colunas = 64; // Atualiza o tamanho das colunas
                salvarImagem("ImagemIconizada.pgm", imagemIconizada, &linhas, &colunas);
                linhas = tempLinhas; // Restaura o tamanho original das linhas
                colunas = tempColunas; // Restaura o tamanho original das colunas
                delete[] imagemIconizada;
                break;
            }
            case 0:// Sai do programa
                cout << "Saindo do programa..." << endl;
                break;
        }
        // Mostra o menu novamente
        cout << "Digite a opção desejada:\n" 
             << "1. ajustar o brilho da imagem\n"
             << "2. rotacionar a imagem\n"
             << "3. inverter as cores da imagem\n"
             << "4. binarizar a imagem\n"
             << "5. iconizar a imagem\n"
             << "0. Sair\n"
             << "R: ";
        cin >> opcao;
        while(0 > opcao and opcao > 5) { // Verifica se a opção é válida
            cout << "Opção inválida, digite uma opção válida (0-5): ";
            cin >> opcao;
        }
    }
    delete[] imagem; // Libera a memória da imagem original ao sair
    return 0;
}