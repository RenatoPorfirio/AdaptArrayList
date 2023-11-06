#ifndef ADAPT_ARRAY_LIST_HPP
#define ADAPT_ARRAY_LIST_HPP

#include <cassert>
#include <cstdlib>
#include <string>
using std::string;

// Função de comparação padrão (comparação de menor) para o tipo T
template <class T>
bool __std_cmp(T a, T b){
  return a < b;
}

// Classe AdaptArrayList
template <class T>
class AdaptArrayList{
private:
  T* arr;               // Ponteiro para o array de elementos
  size_t length;        // Número atual de elementos na lista
  size_t max_length;    // Tamanho máximo do array
  size_t start;         // Índice do elemento inicial na lista (para adaptação)
  bool dynamic;         // Indica se a lista deve ser redimensionada dinamicamente
  float res_factor;     // Fator de redimensionamento para a lista
  bool uncaps;          // Indica se o método array_data foi chamado. Se verdadeiro, a memória do vetor de dados da lista deve ser desalocada manualmente utilizando delete.

  // Função auxiliar que realiza o algoritmo de partição de Hoare para quicksort
  size_t __hoare(long long i, long long j, bool (*cmp)(T, T));

  // Função auxiliar que realiza o algoritmo de quicksort recursivamente
  void __quicksort(size_t i, size_t j, bool (*cmp)(T, T));

  // Função auxiliar que ordena os arrays particionados no mergesort
  void __merge(size_t i, size_t m, size_t j, bool (*cmp)(T, T));

  // Função auxiliar que realiza o algoritmo de mergesort recursivamente
  void __mergesort(size_t i, size_t j, bool (*cmp)(T, T));

protected:
  // Função para redimensionar o array interno
  void resize();

public:
  // Construtor padrão
  AdaptArrayList();

  // Construtor para inicialização a partir de um array
  AdaptArrayList(T* c_array, size_t c_array_size, size_t c_array_max_size, bool is_dynamic=true, float resize_factor=1);

  // Construtor com tamanho inicial e opções de redimensionamento
  AdaptArrayList(size_t max_size, bool is_dynamic=true, float resize_factor=1);

  // Destrutor
  ~AdaptArrayList();

  // Retorna o número de elementos na lista
  size_t size();

  // Retorna o tamanho máximo do array interno
  size_t max_size();

  // Indica se a memória do array de dados será desalocada automaticamente
  bool self_cleaning();

  // Sobrecarga do operador de acesso por índice
  T& operator[](size_t index);

  // Retorna o valor do elemento em um determinado índice (sem modificar o array interno)
  T get(size_t index);

  // Adiciona um elemento no inicio da lista
  AdaptArrayList& push(T value);

  // Adiciona um elemento no final da lista
  AdaptArrayList& push_back(T value);

  // Insere um elemento em um índice específico na lista
  AdaptArrayList& insert(T value, size_t index);

  // Remove e retorna o elemento do início da lista (fila)
  T pop();

  // Remove e retorna o elemento de um determinado índice
  T remove(size_t index);

  // Preenche a lista com o valor fornecido, opcionalmente aumentando o tamanho
  void fill(T value, size_t qnt=0);

  // Executa uma função para cada elemento da lista
  void map(void* (*function)(T*));

  // Ordena a lista usando um algoritmo de ordenação e uma função de comparação
  void sort(string algorithm="quicksort", bool (*cmp)(T, T)=__std_cmp);

  // Retorna o ponteiro para o array interno
  T* array_data();
};

// Implementação dos métodos da classe

#include "AdaptArrayListImpl.hpp"

#endif
