#pragma once
#include "graph.h"

template <typename T>
class AdjacencyMatrixGraph :
	public Graph<T>
{
private:
	size_t m_Size;
	T** m_Matrix;
public:
	AdjacencyMatrixGraph(size_t n);
	~AdjacencyMatrixGraph(void);
	size_t getSize();
	void setEdge(size_t from, size_t to, T value);
	T getEdge(size_t from, size_t to);
};

template <typename T>
AdjacencyMatrixGraph<T>::AdjacencyMatrixGraph(size_t n)
{
	m_Size = n;
	m_Matrix = new T* [n];
	for (auto i = 0; i < n; i++)
	{
		m_Matrix[i] = new T [n];
	}
}

template <typename T>
AdjacencyMatrixGraph<T>::~AdjacencyMatrixGraph(void)
{
	for (auto i = 0; i < m_Size; i++)
	{
		delete m_Matrix[i];
	}
	delete m_Matrix;
}

template <typename T>
size_t AdjacencyMatrixGraph<T>::getSize() 
{
	return m_Size;
}

template <typename T>
void AdjacencyMatrixGraph<T>::setEdge(size_t from, size_t to, T value)
{
	// todo: check range
	m_Matrix[from][to] = value;
}

template <typename T>
T AdjacencyMatrixGraph<T>::getEdge(size_t from, size_t to)
{
	// todo: check range
	return m_Matrix[from][to];
}