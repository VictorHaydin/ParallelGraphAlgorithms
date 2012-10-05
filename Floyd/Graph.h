#pragma once

template<typename T>
class Graph
{
public:
	Graph(void);
	~Graph(void);
	virtual size_t getSize() = 0;
	virtual void setEdge(size_t from, size_t to, T value) = 0;
	virtual T getEdge(size_t from, size_t to) = 0;
};

template <typename T>
Graph<T>::Graph(void)
{
}

template <typename T>
Graph<T>::~Graph(void)
{
}
