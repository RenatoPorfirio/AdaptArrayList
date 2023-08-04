#ifndef ADAPT_ARRAY_LIST_HPP
#define ADAPT_ARRAY_LIST_HPP

#include <cassert>
#include <cstdlib>

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
  size_t ini;           // Índice do elemento inicial na lista (para adaptação)
  bool dynamic;         // Indica se a lista deve ser redimensionada dinamicamente
  float res_factor;     // Fator de redimensionamento para a lista

  // Função auxiliar que realiza o algoritmo de partição de Hoare para quicksort
  size_t __hoare(long long i, long long j, bool (*cmp)(T, T));

  // Função auxiliar que realiza o algoritmo de quicksort recursivamente
  void __quicksort(size_t i, size_t j, bool (*cmp)(T, T));

protected:
  // Função para redimensionar o array interno
  void resize();

public:
  // Construtor padrão
  AdaptArrayList();

  // Construtor com tamanho inicial e opções de redimensionamento
  AdaptArrayList(size_t size, bool is_dynamic=true, float resize_factor=1);

  // Destrutor
  ~AdaptArrayList();

  // Retorna o número de elementos na lista
  size_t size();

  // Retorna o tamanho máximo do array interno
  size_t max_size();

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
  void foreach(void* (*function)(T*));

  // Ordena a lista usando o algoritmo de quicksort e a função de comparação padrão
  void sort();

  // Ordena a lista usando o algoritmo de quicksort e uma função de comparação personalizada
  void sort(bool (*cmp)(T, T));

  // Retorna o ponteiro para o array interno
  T* data();
};

// Implementação dos métodos da classe

template <class T>
AdaptArrayList<T>::AdaptArrayList(){
  // Construtor padrão
  arr = new T[1];
  length = 0;
  max_length = 1;
  ini = 0;
  dynamic = true;
  res_factor = 1;
}

template <class T>
AdaptArrayList<T>::AdaptArrayList(size_t size, bool is_dynamic, float resize_factor){
  // Construtor com tamanho inicial e opções de redimensionamento
  arr = new T[size];
  length = 0;
  max_length = size;
  ini = 0;
  dynamic = is_dynamic;
  res_factor = resize_factor;
}

template <class T>
AdaptArrayList<T>::~AdaptArrayList(){
  // Destrutor
  delete [] arr;
}

template <class T>
void AdaptArrayList<T>::resize(){
  // Redimensiona o array interno quando necessário
  float factor = (float)length + res_factor * (float)length;
  size_t new_m_len = factor ? factor : 1;
  T* tmp = new T[new_m_len];
  for(size_t i = 0; i < length; i++){
    tmp[i] = arr[(i+ini) % max_length];
  }
  delete [] arr;
  arr = tmp;
  ini = 0;
  max_length = new_m_len;
}

template <class T>
size_t AdaptArrayList<T>::size(){
  // Retorna o número de elementos na lista
  return length;
}

template <class T>
size_t AdaptArrayList<T>::max_size(){
  // Retorna o tamanho máximo do array interno
  return max_length;
}

template <class T>
T& AdaptArrayList<T>::operator[](size_t index){
  // Sobrecarga do operador de acesso por índice
  assert(index < max_length);
  return arr[(ini+index) % max_length];
}

template <class T>
T AdaptArrayList<T>::get(size_t index){
  // Retorna o valor do elemento em um determinado índice (sem modificar o array interno)
  assert(index < max_length);
  return arr[(ini+index) % max_length];
}

template <class T>
AdaptArrayList<T>& AdaptArrayList<T>::push(T value){
  // Adiciona um elemento no inicio da lista
  if(length == max_length){
    assert(dynamic == true);
    resize();
  }
  ini = ini == 0 ? max_length-1 : ini-1;
  arr[ini] = value;
  length++;
  return *this;
}

template <class T>
AdaptArrayList<T>& AdaptArrayList<T>::push_back(T value){
  // Adiciona um elemento no final da lista
  if(length == max_length){
    assert(dynamic == true);
    resize();
  }
  arr[(ini+length) % max_length] = value;
  length++;
  return *this;
}

template <class T>
AdaptArrayList<T>& AdaptArrayList<T>::insert(T value, size_t index){
   // Insere um elemento em um índice específico na lista
  if(!index){
    return push(value);
  }
  assert(index <= length);
  if(length == max_length){
    assert(dynamic == true);
    resize();
  }
  for(size_t i = length; i  > index; i--){
    (*this)[i] = (*this)[i - 1];
  }
  (*this)[index] = value;
  length++;
  return *this;
}

template <class T>
T AdaptArrayList<T>::pop(){
  // Remove e retorna o elemento do início da lista
  if(length == 0){
    return (T)NULL;
  }
  T x = arr[ini];
  ini++;
  ini = ini % max_length;
  length--;
  if(3*length <= max_length && dynamic){
    resize();
  }
  return x;
}

template <class T>
T AdaptArrayList<T>::remove(size_t index){
  // Remove e retorna o elemento de um determinado índice
  if(!index){
    return pop();
  }
  assert(index <= length);
  T x = (*this)[index];
  for(size_t i = index; i < length - 1; i++){
    (*this)[i] = (*this)[i + 1];
  }
  length--;
  if(3*length <= max_length && dynamic){
    resize();
  }
  return x;
}

template <class T>
void AdaptArrayList<T>::fill(T value, size_t qnt){
  // Preenche a lista com o valor fornecido, opcionalmente aumentando o tamanho
  size_t n = qnt ? length + qnt : max_length;
  for(size_t i = length; i < n; i++){
    push_back(value);
  }
}

template <class T>
void AdaptArrayList<T>::foreach(void* (*function)(T*)){
  // Executa uma função para cada elemento da lista
  for(size_t i = 0; i < length; i++){
    function(&arr[(i+ini) % max_length]);
  }
}

template <class T>
size_t AdaptArrayList<T>::__hoare(long long i, long long j, bool (*cmp)(T, T)){
  // Função auxiliar que realiza o algoritmo de partição de Hoare para quicksort
  T p = (*this)[i];
  i--; j++;
  while(1){
    while(cmp((*this)[++i], p));
    while(cmp(p, (*this)[--j]));
    if(i >= j){
      return j;
    }
    T tmp = (*this)[i];
    (*this)[i] = (*this)[j];
    (*this)[j] = tmp;
  }
}

template <class T>
void AdaptArrayList<T>::__quicksort(size_t i, size_t j, bool (*cmp)(T, T)){
  // Função auxiliar que realiza o algoritmo de quicksort recursivamente
  if(i < j){
    size_t p = __hoare(i, j, cmp);
    __quicksort(i, p, cmp);
    __quicksort(p+1, j, cmp);
  }
}

template <class T>
void AdaptArrayList<T>::sort(){
  // Ordena a lista usando o algoritmo de quicksort e a função de comparação padrão
  __quicksort(0, length-1, __std_cmp<T>);
}

template <class T>
void AdaptArrayList<T>::sort(bool (*cmp)(T, T)){
  // Ordena a lista usando o algoritmo de quicksort e uma função de comparação personalizada
  __quicksort(0, length-1, cmp);
}

template <class T>
T* AdaptArrayList<T>::data(){
  // Retorna o ponteiro para o array interno
  if(!ini){
    return arr;
  }
  T* tmp = new T[max_length];
  for(size_t i = 0; i < length; i++){
    tmp[i] = arr[(i+ini) % max_length];
  }
  delete [] arr;
  arr = tmp;
  ini = 0;
  return arr;
}

#endif
