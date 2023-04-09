// By: Gonçalo Leão
// Based on MutablePriorityQueue.h

#include "Heap.h"

// Index calculations
#define parent(i) ((i) / 2)
#define leftChild(i) ((i) * 2)
/**
 * Contrutor da classe Heap
 */
Heap::Heap() {
    elems.push_back(0);
	// indices will be used starting in 1
	// to facilitate parent/child calculations
}
/**
 * Construtor da classe Heap tendo como parâmetro um vector
 * @param v vector, vector de inteiros
 */
Heap::Heap(std::vector<int> v): Heap() {
    // Add the elements to the vector without respecting the heap property
    elems.insert(elems.end(),v.begin(),v.end());

    // Index of the last non-leaf node of vector v
    unsigned int startIdx = v.size() / 2;

    // Move the elements around so that the heap property is respected
    // There is no need to heapify the elements with higher indices since they are leaf nodes
    for(unsigned int i = startIdx; i > 0; i--) {
        heapifyDown(i);
    }
}
/**
 * Função que verifica se o vector está vazio
 * Complexidade: O(1)
 * @return bool, true se o vector estiver vazio, false caso contrário
 */

bool Heap::empty() {
	return elems.size() == 1;
}
/**
 * Função que extrai o menor elemento do vector
 * Complexidade: O(log n)
 * @return int, menor elemento do vector
 */
int Heap::extractMin() {
	auto x = elems[1];
    elems[1] = elems.back();
    elems.pop_back();
	if(elems.size() > 1) heapifyDown(1);
	return x;
}
/**
 * Função que insere um elemento no vector
 * Complexidade: O(log n)
 * @param x int, elemento a inserir
 */
void Heap::insert(int x) {
	elems.push_back(x);
	heapifyUp(elems.size()-1);
}
/**
 * Função que diminui a chave de um elemento
 * Complexidade: O(log n)
 * @param i unsigned int, índice do elemento a diminuir a chave
 */
void Heap::heapifyUp(unsigned int i) {
	auto x = elems[i];
	while (i > 1 && x < elems[parent(i)]) {
        elems[i] = elems[parent(i)];
		i = parent(i);
	}
    elems[i] = x;
}
/**
 * Função que aumenta a chave de um elemento
 * Complexidade: O(log n)
 * @param i unsigned int, índice do elemento a aumentar a chave
 */
void Heap::heapifyDown(unsigned int i) {
	auto x = elems[i];
	while (true) {
		unsigned k = leftChild(i);
		if (k >= elems.size())
			break;
		if (k+1 < elems.size() && elems[k+1] < elems[k])
			++k; // right child of i
		if ( ! (elems[k] < x) )
			break;
        elems[i] = elems[k];
		i = k;
	}
    elems[i] = x;
}