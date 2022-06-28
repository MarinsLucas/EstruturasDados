#ifndef MANAGER
#define MANAGER

#include "config.h"
#include <string.h>
#include <vector>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <algorithm>
#include "hash.h"


using namespace std;

typedef enum
{
    INSERTIONSORT,
    MERGESORT,
    QUICKSORT,
    TIMSORT
} sorting_method;

class manager
{
public:
    manager();
    void read_index_file(vector<string> &nomes_arquivos);                     // leitura do arquivo com os nomes dos arquivos
    int return_n_words() {return n_words;}
    Hash* return_hash() {return &hashmp;}
    ~manager();                                                                 // destrutor

    void mainGutemberg(sorting_method method, vector<string> nomes_arquivos,    // função que chama a openFile e efetua a indexação na tabela hash
    int indice, int (*hash)(string key, int tam));                                                               

private:
    Hash hashmp = Hash(2073);       // tabela hash
    vector<hashVec> words;          // vetor de palavras
    vector<string> ignore_array;    // vetor de palavras ignoradas
    int n_words = 0; 

    bool search_ignored_words(string x);                                      // colocando palavras a serem ignoradas num vetor
    void read_ignore_file();                                                  // leitura do arquivo com as palavras a serem ignoradas
    void searchFiles(string file_name);                                       // Anotando nomes dos arquivos da pasta input
    string tratamento(string word);                                           // Função de tratamento de palavras
    bool compare(string &a, string &b);                                       // função de comparação
    void openFile(string nome_arquivo, int (*hash)(string key, int tam));     // função que abre o arquivo e lê as palavras
    void write50(int indice);                                                 // função que esreve as 50 palavras mais repetidas em um arquivo
    template <typename T>
    void sort_words_by_repeat(vector<T> &arrayPalavras, sorting_method method);// função que chama a ordenação das palavras que mais repetem
};

#endif