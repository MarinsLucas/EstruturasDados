#include <string.h>
#include <vector>
#include <dirent.h>
#include <iostream>
#include <sstream>
#include <algorithm>

#include "manager.h"
#include "sort.h"
#include "hash.h"
#include "config.h"

using namespace std;
namespace fs = std::filesystem;

manager::manager(){        };
manager::~manager(){        };

bool compare_alf_ordem(string& a, string& b)
{
    return a < b;
}

bool compare_freq_palavra(hashVec& a, hashVec& b){
    return a.c > b.c;
}

void manager::read_ignore_file(){
    fstream ignore_file(OUTPUT_DIR + (string)"ignore.csv", ios::out | ios::in);
    string *aux = new string;

    if(!ignore_file.is_open()){
        cout<<"Erro ao abrir o ignore.csv"<<endl;
    }

    while(!ignore_file.eof()){
        getline(ignore_file, *aux, ';');
        ignore_array.push_back(*aux);
    } 

    quick_sort<string>(&ignore_array[0], ignore_array.size(), compare_alf_ordem);
    delete aux;
    ignore_file.close();      
};

void manager::read_index_file(vector<string> &nomes_arquivos){
     string *name = new string;
    
    string index_file_name = OUTPUT_DIR;
    index_file_name += "/nome_arquivos.txt";
    searchFiles(index_file_name); //chamando função de leitura de diretório

    ifstream index_file;
    index_file.open(index_file_name, ios::in);

    while(getline(index_file, *name))
        nomes_arquivos.push_back(*name);
    delete name;
};

bool manager::search_ignored_words(string x){
    return binary_search(ignore_array.begin(), ignore_array.end(), x);
};

template <typename T>
void manager::sort_words_by_repeat(vector<T> &arrayPalavras, sorting_method method){
    switch(method){
        case INSERTIONSORT:
            insertion_sort(&arrayPalavras[0], 0, arrayPalavras.size()-1, compare_freq_palavra);
            break;
        case MERGESORT:
            merge_sort(&arrayPalavras[0], arrayPalavras.size()-1, compare_freq_palavra);
            break;
        case QUICKSORT:
            quick_sort(&arrayPalavras[0], arrayPalavras.size()-1, compare_freq_palavra);
            break;
        case TIMSORT:
            timSort(&arrayPalavras[0], arrayPalavras.size()-1, compare_freq_palavra);    
            break;
        default:
            cout<<"ERRO NA ORDENAÇÃO: TIPO INVÁLIDO"<<endl;
            return;
            break;
    }
};

void manager::searchFiles(string file_name){
    ofstream listaArquivos;
    listaArquivos.open(file_name, ios::trunc | ios::out);
    
    string path = INPUT_DIR;
    for (const auto & entry : fs::directory_iterator(path)){
        listaArquivos << entry.path().string() << endl;
    }
    
    listaArquivos.close();
};

string manager::tratamento(string word){
    int char_especiais[] = {'!', '.', ',', '?', '(', ')', '{', '}',' ', '>', '<', ';',':' -62, -85, '"', '"'};
    for(int i = 0; i<17; i++)
        word.erase(remove(word.begin(), word.end(), char_especiais[i]), word.end());

    for(int i=0; i<word.size(); i++)
        word[i] = tolower(word[i]);

    return word;
};

void manager::openFile(string nome_arquivo, int (*hash)(string key, int tam)) {
    ifstream file(nome_arquivo, ios::in);
    string sentence, word;

    if(!file.is_open()){
        cout<<"ERRO AO ABRIR O ARQUIVO: "<< nome_arquivo << endl; 
        return;
    }

    //Leitura do texto e passando para a Hash
    while(!file.eof()){
        getline(file , sentence);
        stringstream sentence_stream(sentence);

        while(getline(sentence_stream, word, ' ')){
            word = tratamento(word.c_str());
            
            if(!search_ignored_words(word) && word.size()>1){
                hashmp.insere(word, hash);
                n_words++;
            }
        }
    }
    
    file.close();
}

void manager::write50(int indice) {  
    ofstream output_file(OUTPUT_DIR + (string)"output" + to_string(indice) + (string)".txt", ios::trunc);
    for(int i = 0; i<50; i++)
        output_file<<i+1<<"º - "<<words[i].palavra<<" (" << words[i].c << ")"<<endl;

    output_file.close();
}

void manager::mainGutemberg(sorting_method method, vector<string>nomes_arquivos, int indice, int (*hash)(string key, int tam)){
    //anexando palavras a serem ignoradas
    read_ignore_file(); 

    //abrindo arquivos a serem lidos
    for(auto file_name : nomes_arquivos){
        cout << "\n" << file_name << endl;
        openFile(file_name, hash);
    }

    hashmp.copyToVector(words);
    sort_words_by_repeat(words, method);
    write50(indice);
};

