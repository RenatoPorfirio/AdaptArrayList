#include "AdaptArrayList.hpp"
#include <iostream>

using namespace std;

template <class T>
void* print(T* x){
  cout << *x << " ";
  return NULL;
}

int main() {
  AdaptArrayList<string> l(1, true, 1.5);
  
  cout << "Estado inicial:\n[ ";
  l.map(print);
  cout << "], tam = " << l.size() << ", tam. máximo = " << l.max_size() << endl << endl;
  
l.push("melancia")
  .push("banana")
  .push_back("abacate")
  .push_back("jaca")
  .push("acerola");
  
  cout << "Após 5 itens adicionados:\n[ ";
  l.map(print);
  cout << "], tam = " << l.size() << ", tam. máximo = " << l.max_size() << endl << endl;
  
  l.pop();
  l.pop();

  cout << "Após 2 primeiros itens removidos:\n[ ";
  l.map(print);
  cout << "], tam = " << l.size() << ", tam. máximo = " << l.max_size() << endl << endl;

  l.sort();

  cout << "Após ordenar os itens:\n[ ";
  l.map(print);
  cout << "], tam = " << l.size() << ", tam. máximo = " << l.max_size() << endl << endl;

  l.fill("fruta");

  cout << "Após preencher com a string \"fruta\":\n[ ";
  l.map(print);
  cout << "], tam = " << l.size() << ", tam. máximo = " << l.max_size() << endl << endl;
  l.remove(3);

  cout << "Após remover o quarto item:\n[ ";
  l.map(print);
  cout << "], tam = " << l.size() << ", tam. máximo = " << l.max_size() << endl << endl;
  
  l.insert("Amora", 2).insert("mamão", 4);
  
  cout << "Após inserir itens nas posições 2 e 4:\n[ ";
  l.map(print);
  cout << "], tam = " << l.size() << ", tam. máximo = " << l.max_size() << endl << endl;

  AdaptArrayList<string> l2(l.array_data(), l.size(), l.size());

  cout << "Nova lista criada com base no vetor de dados da lista anterior:\n[ ";
  l2.map(print);
  cout << "], tam = " << l2.size() << ", tam. máximo = " << l2.max_size() << endl << endl;

  l2.push("acerola");
  cout << "Situação de erro: como o array da primeira lista agora faz parte da segunda lista, o mesmo será deletado com a operação de resize da segunda lista." << endl << endl;
  cout << "Após inserir um novo item no inicio da nova lista:\n Nova lista: [ ";
  l2.map(print);
  cout << "], tam = " << l2.size() << ", tam. máximo = " << l2.max_size() << endl << endl;
  //cout << "Lista antiga: [ ";
  //l.map(print);
  //cout << "], tam = " << l.size() << ", tam. máximo = " << l.max_size() << endl;
  
  return 0;
}
