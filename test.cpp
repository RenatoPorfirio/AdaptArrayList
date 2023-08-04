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
  l.foreach(print);
  cout << "], tam = " << l.size() << ", tam. máximo = " << l.max_size() << endl << endl;
  
l.push("melancia")
  .push("banana")
  .push_back("abacate")
  .push_back("jaca")
  .push("acerola");
  
  cout << "Após 5 itens adicionados:\n[ ";
  l.foreach(print);
  cout << "], tam = " << l.size() << ", tam. máximo = " << l.max_size() << endl << endl;
  
  l.pop();
  l.pop();

  cout << "Após 2 primeiros itens removidos:\n[ ";
  l.foreach(print);
  cout << "], tam = " << l.size() << ", tam. máximo = " << l.max_size() << endl << endl;

  l.sort();

  cout << "Após ordenar os itens:\n[ ";
  l.foreach(print);
  cout << "], tam = " << l.size() << ", tam. máximo = " << l.max_size() << endl << endl;

  l.fill("fruta");

  cout << "Após preencher com a string \"fruta\":\n[ ";
  l.foreach(print);
  cout << "], tam = " << l.size() << ", tam. máximo = " << l.max_size() << endl << endl;

  l.remove(3);
  
  cout << "Após remover o terceiro item:\n[ ";
  l.foreach(print);
  cout << "], tam = " << l.size() << ", tam. máximo = " << l.max_size() << endl << endl;
  
  l.insert("Amora", 2).insert("Mamão", 4);

  cout << "Após inserir itens nas posições 2 e 4:\n[ ";
  l.foreach(print);
  cout << "], tam = " << l.size() << ", tam. máximo = " << l.max_size() << endl << endl;
  
  return 0;
}
