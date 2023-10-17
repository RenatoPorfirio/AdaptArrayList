# AdaptArrayList
Implementação de uma lista versátil baseada em Array **(ainda em desenvolvimento)**.

<details><summary><h2>Descrição</h2></summary>
  
A classe `AdaptArrayList` possui a opção de operar tanto em modo dinâmico quanto estático, o que pode trazer benefícios em diferentes cenários, dependendo dos requisitos do programa. Vamos explicar como funciona a troca entre esses modos e seus benefícios:

### Modo Dinâmico

No modo dinâmico, a lista pode crescer e encolher dinamicamente conforme novos elementos são adicionados ou removidos. Para permitir esse comportamento, a lista utiliza um array interno que é redimensionado automaticamente quando necessário. A taxa de redimensionamento é controlada pelo fator de redimensionamento (`resize_factor`) passado ao construtor ou definido como valor padrão.

Quando a lista está em modo dinâmico e atinge seu tamanho máximo, ela redimensiona o array interno para aumentar sua capacidade em `resize_factor` vezes o tamanho atual, permitindo que novos elementos sejam adicionados sem que seja necessário copiar todos os elementos antigos. Da mesma forma, quando a lista fica significativamente menor em relação ao seu tamanho máximo, ela redimensiona o array para economizar espaço.

#### Benefícios do Modo Dinâmico:

1. **Uso eficiente de memória:** A lista consome memória apenas para os elementos que realmente contém, e não para a capacidade máxima alocada. Isso pode ser vantajoso quando a quantidade de elementos varia ao longo do tempo, economizando memória.

2. **Flexibilidade:** A lista pode crescer e encolher conforme necessário, adaptando-se às mudanças no número de elementos. Isso pode ser útil quando o tamanho da lista é imprevisível ou quando são necessárias operações frequentes de inserção e remoção.

### Modo Estático

No modo estático, a lista possui um tamanho fixo que é determinado durante a sua criação. Nesse caso, não é possível adicionar mais elementos do que o tamanho máximo especificado. Se a lista estiver cheia e for necessário adicionar um novo elemento, ocorrerá um erro de estouro.

#### Benefícios do Modo Estático:

1. **Performance previsível:** No modo estático, não há necessidade de redimensionar o array interno, o que pode levar a melhor previsibilidade do tempo de execução e evita possíveis custos de redimensionamento.

2. **Segurança:** Em alguns cenários, ter um tamanho fixo pode ser uma vantagem, garantindo que a lista não cresça além de um limite pré-definido, o que poderia causar problemas de uso excessivo de memória.

### Troca entre Modo Dinâmico e Estático

A troca entre os modos dinâmico e estático é realizada durante a criação da lista ou por meio da chamada do construtor com diferentes parâmetros. Se o tamanho inicial especificado for maior que zero (e a opção de redimensionamento dinâmico estiver desativada), a lista será criada no modo estático com o tamanho fornecido. Caso contrário, a lista será criada no modo dinâmico, com tamanho inicial de 1 elemento (modo padrão).

Durante a execução do programa, é possível alterar o modo da lista criando uma nova instância com o tamanho desejado e copiando os elementos da lista original para a nova. No entanto, isso pode ser um processo ineficiente, pois envolve a realocação de memória e a cópia dos elementos. Portanto, a escolha do modo mais adequado deve ser feita de acordo com os requisitos específicos do programa.
</details><details>
<summary><h2>Métodos e Complexidade Algorítmica</h2></summary>

### AdaptArrayList\<T>::AdaptArrayList()

- **Complexidade:** O(1)
- **Descrição:** Construtor padrão que cria uma lista vazia com tamanho inicial de 1 elemento.

### AdaptArrayList\<T>::AdaptArrayList(size_t size, bool is_dynamic=true, float resize_factor=1)

- **Complexidade:** O(size)
- **Descrição:** Construtor que cria uma lista com um tamanho inicial especificado, podendo ser redimensionada dinamicamente ou não.

### AdaptArrayList\<T>::AdaptArrayList(T* c_array, size_t c_array_size, size_t c_array_max_size, bool is_dynamic=true, float resize_factor=1)

- **Complexidade:** O(1)
- **Descrição:** Construtor que cria uma lista a partir de um array.
- **OBS:** O array recebido é utilizado como o array base da lista, e isso leva para algumas implicações:
  1. Se a lista for dinâmica, o array passado como argumento deve ser alocado dinamicamente;
  2. Qualquer alteração na lista causará alteração direta no array;
  3. Chamadas de resize farão com que a memória desse mesmo array seja desalocada;

### AdaptArrayList\<T>::~AdaptArrayList()

- **Complexidade:** O(1)
- **Descrição:** Destrutor que libera a memória alocada para o array interno da lista.

### AdaptArrayList\<T>::resize() (Privado)

- **Complexidade:** O(length)
- **Descrição:** Redimensiona o array interno da lista para aumentar seu tamanho conforme necessário.

### AdaptArrayList\<T>::size()

- **Complexidade:** O(1)
- **Descrição:** Retorna o número de elementos atualmente na lista.

### AdaptArrayList\<T>::max_size()

- **Complexidade:** O(1)
- **Descrição:** Retorna o tamanho máximo do array interno.

### AdaptArrayList\<T>::operator[]

- **Complexidade:** O(1)
- **Descrição:** Sobrecarga do operador de acesso por índice, permite acessar um elemento específico na lista.

### bool AdaptArrayList\<T>::self_cleaning()

- **Complexidade:** O(1)
- **Descrição:** Retorna `true` se a lista estiver configurada para deletar o array de dados automaticamente. Essa configuração é feita automaticamente ao inicializar a lista, e é desabilitada ao utilizar o método `array_data`. Caso essa configuração se desabilite, é necessário deletar a lista utilizando ```delete [] <ponteiro para o array>```.

### AdaptArrayList\<T>::get(size_t index)

- **Complexidade:** O(1)
- **Descrição:** Retorna o valor do elemento em um determinado índice sem modificar o array interno.

### AdaptArrayList\<T>::push(T value)

- **Complexidade:** O(1) amortizado, O(length) quando há necessidade de redimensionamento
- **Descrição:** Adiciona um elemento na frente da lista. A operação é O(1) na maioria dos casos, mas pode ser O(length) quando é necessário redimensionar o array.

### AdaptArrayList\<T>::push_back(T value)

- **Complexidade:** O(1) amortizado, O(length) quando há necessidade de redimensionamento
- **Descrição:** Adiciona um elemento no final da lista. A operação é O(1) na maioria dos casos, mas pode ser O(length) quando é necessário redimensionar o array.

### AdaptArrayList\<T>::insert(T value, size_t index)

- **Complexidade:** O(length)
- **Descrição:** Insere um elemento em um índice específico na lista. A complexidade é O(length) porque a operação requer a realocação dos elementos para acomodar o novo valor.

### AdaptArrayList\<T>::pop()

- **Complexidade:** O(1) amortizado
- **Descrição:** Remove e retorna o elemento do início da lista (fila). A operação é O(1) na maioria dos casos, mas pode ser O(length) quando é necessário redimensionar o array.

### AdaptArrayList\<T>::remove(size_t index)

- **Complexidade:** O(length)
- **Descrição:** Remove e retorna o elemento de um determinado índice. A complexidade é O(length) porque a operação requer a realocação dos elementos para preencher o espaço vazio.

### AdaptArrayList\<T>::fill(T value, size_t qnt)

- **Complexidade:** O(qnt) amortizado, O(qnt * length) quando há necessidade de redimensionamento
- **Descrição:** Preenche a lista com o valor fornecido, opcionalmente aumentando o tamanho. A complexidade é O(qnt) na maioria dos casos, mas pode ser O(qnt * length) quando é necessário redimensionar o array.

### AdaptArrayList\<T>::foreach(void* (*function)(T*))

- **Complexidade:** O(length)
- **Descrição:** Executa uma função para cada elemento da lista.

### AdaptArrayList\<T>::sort(string algorithm="quicksort", bool (*cmp)(T, T)=__std_cmp)

- **Complexidade:** A mesma do algoritmo de ordenação escolhido.
- **Descrição:** Ordena a lista usando um algoritmo de ordenação e uma função de comparação. Por padrão, o algoritmo de comparação é o quicksort e a função de comparação é a do maior número, portanto, a chamada da função sem parâmetros resulta num quicksort em ordem crescente.

### AdaptArrayList\<T>::array_data()

- **Complexidade:** O(length)
- **Descrição:** Retorna o ponteiro para o array interno. A complexidade é O(length) porque a operação requer a realocação dos elementos para criar um novo array com o início da lista no índice 0.
  
</details>
