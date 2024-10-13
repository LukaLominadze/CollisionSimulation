#pragma once

#include "Boundary.h"
#include <unordered_map>

class QuadTree {
public:
	QuadTree(Boundary boundary, int capacity);
	~QuadTree();

	void SetCapacity(int capacity);

	bool Insert(const Boundary& circle, int index);
	void Subdivide();
	void Clear();
	
	std::vector<int> Query(Boundary range, std::vector<int>& found);
	std::vector<Boundary> GetBoundaries(std::vector<Boundary>& boundaries);
private:
	std::vector<QuadTree> m_trees;
private:
	Boundary m_boundary;
	int m_capacity;
	std::vector<int> m_indexes;
	std::vector<Boundary> m_circles;

	bool m_subdivided;
};