#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Graph.h"
#include "AdjacencyMatrixGraph.h"
using namespace std;

#define INFINITY 1 << 31;

void fillGraph(Graph<int>* g, bool directed = false) 
{
	size_t n = g->getSize();
	if(directed) 
	{
		for (size_t i = 0; i < n; i++)
		{
			for (size_t j = 0; j < n; j ++)
			{
				if(i != j) g->setEdge(i, j, rand());
				else g->setEdge(i, j, 0);
			}
		} 
	}
	else 
	{
		for (size_t i = 0; i < n; i++)
		{
			g->setEdge(i, i, 0);
			for (size_t j = 0; j < i; j ++)
			{
				auto val = rand() % 100;
				g->setEdge(i, j, val);
				g->setEdge(j, i, val);
			}
		} 
	}
}

void printGraph(Graph<int>* g)
{
	int n = g->getSize();
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << g->getEdge(i,j) << ' ';
		}
		cout << endl;
	}
}

void printMatrix(int ** m, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << m[i][j] << ' ';
		}
		cout << endl;
	}
}


int ** calculateAllDistancesSingleThread(Graph<int>* g)
{
	int n = g->getSize();
	int ** d = new int*[n];
	for(int i=0;i<n;i++)
	{
		d[i] = new int[n];
		for(int j=0;j<n;j++)
		{
			d[i][j] = g->getEdge(i,j);
		}
	}
	
	// Floyd algorithm
	for(int k=0;k<n;k++)
	{
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
			}
		}
	}
	return d;
}

int ** calculateAllDistancesSingleOpenMP(Graph<int>* g)
{
	int n = g->getSize();
	int ** d = new int*[n];
	for(int i=0;i<n;i++)
	{
		d[i] = new int[n];
		for(int j=0;j<n;j++)
		{
			d[i][j] = g->getEdge(i,j);
		}
	}
	
	// Floyd algorithm
	for(int k=0;k<n;k++)
	{
		int i,j;
		#pragma omp parallel shared(d,k) private(i,j)
		{
			#pragma omp for schedule(static) 
			for(i=0;i<n;i++)
			{
				for(j=0;j<n;j++)
				{
					d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
				}
			}
		}
	}
	return d;
}

int main()
{
	auto g = new AdjacencyMatrixGraph<int>(600);
	cout << g->getSize() << endl;
	fillGraph(g);
	//printGraph(g);
	
	cout << "Starting single thread..." << endl;
	auto start = clock();
	auto d = calculateAllDistancesSingleThread(g);
	cout << "Time of execution: " << clock() - start << endl;

	cout << "Starting OpenMP..." << endl;
	start = clock();
	d = calculateAllDistancesSingleOpenMP(g);
	cout << "Time of execution: " << clock() - start << endl;
	
	//cout << endl;
	//printMatrix(d, g->getSize());
	return 0;
}
