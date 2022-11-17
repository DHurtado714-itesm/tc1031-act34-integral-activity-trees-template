// =================================================================
//
// File: main.cpp
// Author: Daniel Hurtado - A01707774
// Date: 15 - 11 - 2022
//
// =================================================================
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "header.h"
#include "heap.h"


using namespace std;

int main(int argc, char* argv[]) {
	
	ifstream inputFile;
	ofstream outputFile;

	// Open file and read variables
	inputFile.open(argv[1]);
	if (inputFile.fail())
	{
		cout << "Error opening file" << endl;
		return 1;
	}

	outputFile.open(argv[2]);
	if (outputFile.fail())
	{
		cout << "Error opening file" << endl;
		return 1;
	}

	int n_list;
	
	inputFile >> n_list;
	
	Heap<int> Heap(n_list);
		for (int i = 0; i < n_list; i++)
		{
			int number;
			inputFile >> number;
			Heap.add(number);
		}

	// Sort the list
	for(int i = 0; i < n_list; i++)
	{
		Heap.pushDown(i);
	}

	int sum = 0, contador = 0;

	for(int i = 0; i < n_list && Heap.length() > 1; i++)
	{
		sum = Heap.remove() + Heap.remove();
		Heap.toString();
		Heap.add(sum);
		contador += sum - 1;
	}
	
	outputFile << contador << endl;
	
	return 0;
}

// =================================================================
// Comentarios
// =================================================================

/*

Objetivo: 
	- Desarrolla una solución que, dada un conjunto de pedidos y sus
	tamaños, calcule el menor número de comparaciones posibles.

Logica:
	(m + n) - 1
	- P1 y P2 -> Z1: (20 + 5) - 1 = 24
	- Z1 y P3 -> Z2: (24 + 8) - 1 = 31
	- Z2 y P4 -> Z3: (31 + 20) - 1 = 50
	- Z3 y P5 -> Z4: (50 + 7) - 1 = 56
	- Z4 y P6 -> Z5: (56 + 4) - 1 = 59

Inputs:
	- Número de listas (N)
	- Tamano de cada lista (N)

Outputs:
	- Número de comparaciones

*/
