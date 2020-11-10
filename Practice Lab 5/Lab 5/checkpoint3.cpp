#include <iostream>
#include <string>


// Note: It's ok that all the member variables are public for this
// tiny class.  We'll build up to a more robust and complete linked
// list implementation in lecture 11.
template <class T>
class Node {
public:
  T value;
  Node<T> *ptr;
};



template <class T>
void print(Node<T> *data, const std::string &label) {
  std::cout << label;
  Node<T> *tmp = data;
  while (tmp != NULL) {
    std::cout << " " << tmp->value;
    tmp = tmp->ptr;
  }
  std::cout << std::endl;
}



template <class T>
void reverse(Node<T>* &input) {

 /*   Node<T>* current = input;
    Node<T>* swap = input;

    int list_size = 0;
    while(current != NULL){
        current = current->ptr;
        list_size += 1;
    }

    int num_of_swap = 0;
    current = input;
    T temp = input->value;;
    if (list_size % 2 = 0) {
        num_of_swap = list_size / 2;
        list_size -= 1;
        while (number_of_swap > 0) {
            for (list_size; list_size > 0; list_size--) {
                swap = swap->ptr;
            }
            current->value = swap->value;
            swap = input;
        }
    }
    else{
        num_of_swap = (list_size - 1) / 2;
    }
    */

   T temp = input->value;
   input->value = input->ptr->ptr->ptr->value;
   input->ptr->ptr->ptr->value = temp;

   temp = input->ptr->value;
   input->ptr->value = input->ptr->ptr->value;
   input->ptr->ptr->value = temp;

}




int main() {

  // manually create a linked list of notes with 4 elements
  Node<int>* my_list = new Node<int>; 
  my_list->value = 1; 
  my_list->ptr = new Node<int>;
  my_list->ptr->value = 2;
  my_list->ptr->ptr = new Node<int>;
  my_list->ptr->ptr->value = 3;
  my_list->ptr->ptr->ptr = new Node<int>;
  my_list->ptr->ptr->ptr->value = 4;
  my_list->ptr->ptr->ptr->ptr = NULL;

  
  print(my_list,"my_list before");
  reverse(my_list);
  print(my_list,"my_list after ");


  // Note: We are not deleting any of the Nodes we created...  so this
  // program has memory leaks!  More on this in lecture 11.

}

// ===========================================================================
