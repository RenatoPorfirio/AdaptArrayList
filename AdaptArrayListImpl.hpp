#ifdef ADAPT_ARRAY_LIST_HPP

template <class T>
AdaptArrayList<T>::AdaptArrayList(){
  // Construtor padrão
  arr = new T[1];
  length = 0;
  max_length = 1;
  start = 0;
  dynamic = true;
  res_factor = 1;
  uncaps = false;
}

template <class T>
AdaptArrayList<T>::AdaptArrayList(T* c_array, size_t c_array_size, size_t c_array_max_size, bool is_dynamic, float resize_factor){
  // Construtor para inicialização a partir de um array
  assert(c_array_size <= c_array_max_size);
  arr = c_array;
  length = c_array_size;
  max_length = c_array_max_size;
  this->start = 0;
  dynamic = is_dynamic;
  res_factor = resize_factor;
  uncaps = false;
}

template <class T>
AdaptArrayList<T>::AdaptArrayList(size_t max_size, bool is_dynamic, float resize_factor){
  // Construtor com tamanho inicial e opções de redimensionamento
  arr = new T[max_size];
  length = 0;
  max_length = max_size;
  start = 0;
  dynamic = is_dynamic;
  res_factor = resize_factor;
  uncaps = false;
}

template <class T>
AdaptArrayList<T>::~AdaptArrayList(){
  // Destrutor
  if(!uncaps){
    delete [] arr;
  }
}

template <class T>
void AdaptArrayList<T>::resize(){
  // Redimensiona o array interno quando necessário
  float factor = (float)length + res_factor * (float)length;
  size_t new_m_len = factor ? factor : 1;
  T* tmp = new T[new_m_len];
  for(size_t i = 0; i < length; i++){
    tmp[i] = arr[(i+start) % max_length];
  }
  delete [] arr;
  arr = tmp;
  start = 0;
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
bool AdaptArrayList<T>::self_cleaning(){
  return !uncaps;
}

template <class T>
T& AdaptArrayList<T>::operator[](size_t index){
  // Sobrecarga do operador de acesso por índice
  assert(index < max_length);
  return arr[(start+index) % max_length];
}

template <class T>
T AdaptArrayList<T>::get(size_t index){
  // Retorna o valor do elemento em um determinado índice (sem modificar o array interno)
  assert(index < max_length);
  return arr[(start+index) % max_length];
}

template <class T>
AdaptArrayList<T>& AdaptArrayList<T>::push(T value){
  // Adiciona um elemento no inicio da lista
  if(length == max_length){
    assert(dynamic == true);
    resize();
  }
  start = start == 0 ? max_length-1 : start-1;
  arr[start] = value;
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
  arr[(start+length) % max_length] = value;
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
  T x = arr[start];
  start++;
  start = start % max_length;
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
    function(&arr[(i+start) % max_length]);
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
void AdaptArrayList<T>::__merge(size_t i, size_t m, size_t j, bool(*cmp)(T,T)){
  // Função auxiliar que ordena os arrays particionados no mergesort
  size_t left_size = m + 1 - i, right_size = j - m, k;
  T left[left_size];
  T right[right_size];
  size_t left_index = 0, right_index = 0;
  for(k = 0; k < left_size; k++)
    left[k] = (*this)[i + k];
  for(k = 0; k < right_size; k++)
    right[k] = (*this)[m + 1 + k];
  for(k = i; k <= j; k++){
    if(left_index < left_size){
      if(right_index < right_size){
        if(cmp(left[left_index], right[right_index])){
            (*this)[k] = left[left_index++];
        }
        else{
          (*this)[k] = right[right_index++];
        }
      }
      else{
        (*this)[k] = left[left_index++];
      }
    }
    else{
      (*this)[k] = right[right_index++];
    }
  }
}

template <class T>
void AdaptArrayList<T>::__mergesort(size_t i, size_t j, bool(*cmp)(T,T)){
  // Função auxiliar que realiza o algoritmo de mergesort recursivamente
  if(i < j){
    size_t m = (i + j) / 2;
    __mergesort(i, m, cmp);
    __mergesort(m+1, j, cmp);
    __merge(i, m, j, cmp);
  }
}

template <class T>
void AdaptArrayList<T>::sort(string algorithm, bool (*cmp)(T, T)){
  // Ordena a lista usando um algoritmo de ordenação e uma função de comparação
  if(algorithm == "mergesort")
    __mergesort(0, length-1, cmp);
  else
    __quicksort(0, length-1, cmp);
}

template <class T>
T* AdaptArrayList<T>::array_data(){
  // Retorna o ponteiro para o array interno
  uncaps = true;
  if(!start){
    return arr;
  }
  T* tmp = new T[max_length];
  for(size_t i = 0; i < length; i++){
    tmp[i] = arr[(i+start) % max_length];
  }
  delete [] arr;
  arr = tmp;
  start = 0;
  return arr;
}

#endif