#include "QuadTree.h"

inline const int NORTHWEST = 0;
inline const int NORTHEAST = 1;
inline const int SOUTHEAST = 2;
inline const int SOUTHWEST = 3;

QuadTree::QuadTree(Boundary boundary, int capacity)
	:m_boundary(boundary), m_capacity(capacity), m_subdivided(false)
{
}

QuadTree::~QuadTree()
{
}

void QuadTree::SetCapacity(int capacity)
{
	m_capacity = capacity;
}

bool QuadTree::Insert(const Boundary& circle, int index)
{
	if (!m_subdivided) {
		if (m_circles.size() < m_capacity) {
			if (m_boundary.ContainsCenter(circle)) {
				m_indexes.push_back(index);
				m_circles.emplace_back(Boundary(circle));
				return true;
			}
			return false;
		}
		else if (m_trees.size() == 0) {
			Subdivide();
		}
	}
	if (!m_boundary.ContainsCenter(circle)) {
		return false;
	}
	for (QuadTree& tree : m_trees) {
		if (tree.Insert(circle, index)) return true;
	}
}

void QuadTree::Subdivide()
{
	float width = m_boundary.x2 - m_boundary.x1;
	float height = m_boundary.y2 - m_boundary.y1;
	m_trees.emplace_back(QuadTree(Boundary(m_boundary.x1 + width / 4.0f, m_boundary.y2 - height / 4.0f,
										   width / 2.0f, height / 2.0f), m_capacity));
	m_trees.emplace_back(QuadTree(Boundary(m_boundary.x2 - width / 4.0f, m_boundary.y2 - height / 4.0f,
										   width / 2.0f, height / 2.0f), m_capacity));
	m_trees.emplace_back(QuadTree(Boundary(m_boundary.x2 - width / 4.0f, m_boundary.y1 + height / 4.0f,
										   width / 2.0f, height / 2.0f), m_capacity));
	m_trees.emplace_back(QuadTree(Boundary(m_boundary.x1 + width / 4.0f, m_boundary.y1 + height / 4.0f,
										   width / 2.0f, height / 2.0f), m_capacity));
	std::vector<int> indexesToErase;
	for (int i = 0; i < m_indexes.size(); i++) {
		for (QuadTree& tree : m_trees) {
			if (tree.Insert(m_circles[i], m_indexes[i])) 
			{
				indexesToErase.push_back(i);
				continue;
			}
		}
	}
	for (int i = indexesToErase.size() - 1; i >= 0; i--) {
		m_circles.erase(m_circles.begin() + i);
		m_indexes.erase(m_indexes.begin() + i);
	}
	m_subdivided = true;
}

void QuadTree::Clear()
{
	m_circles.clear();
	m_indexes.clear();
	m_trees.clear();
	m_subdivided = false;
}

std::vector<int> QuadTree::Query(Boundary range, std::vector<int>& found)
{
	if (!m_boundary.Intersects(range)) {
		return found;
	}
	for (int i = 0; i < m_circles.size(); i++) {
		if (range.ContainsCenter(m_circles[i])) {
			found.push_back(m_indexes[i]);
		}
	}
	if (m_trees.size() != 0) {
		for (QuadTree& tree : m_trees) {
			tree.Query(range, found);
		}
	}
	return found;
}

std::vector<Boundary> QuadTree::GetBoundaries(std::vector<Boundary>& boundaries)
{
	boundaries.push_back(m_boundary);
	for (QuadTree tree : m_trees) {
		tree.GetBoundaries(boundaries);
	}
	return boundaries;
}
