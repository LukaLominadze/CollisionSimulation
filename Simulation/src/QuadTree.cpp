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
	if (m_trees[NORTHWEST].Insert(circle, index)) return true;
	if (m_trees[NORTHEAST].Insert(circle, index)) return true;
	if (m_trees[SOUTHEAST].Insert(circle, index)) return true;
	if (m_trees[SOUTHWEST].Insert(circle, index)) return true;
}

void QuadTree::Subdivide()
{
	m_trees.emplace_back(QuadTree(Boundary(m_boundary.x1 + m_boundary.width / 4.0f, m_boundary.y2 - m_boundary.height / 4.0f,
										   m_boundary.width / 2.0f, m_boundary.height / 2.0f), m_capacity));
	m_trees.emplace_back(QuadTree(Boundary(m_boundary.x2 - m_boundary.width / 4.0f, m_boundary.y2 - m_boundary.height / 4.0f,
										   m_boundary.width / 2.0f, m_boundary.height / 2.0f), m_capacity));
	m_trees.emplace_back(QuadTree(Boundary(m_boundary.x2 - m_boundary.width / 4.0f, m_boundary.y1 + m_boundary.height / 4.0f,
										   m_boundary.width / 2.0f, m_boundary.height / 2.0f), m_capacity));
	m_trees.emplace_back(QuadTree(Boundary(m_boundary.x1 + m_boundary.width / 4.0f, m_boundary.y1 + m_boundary.height / 4.0f,
										   m_boundary.width / 2.0f, m_boundary.height / 2.0f), m_capacity));
	std::vector<int> circlesToErase;
	for (int i = 0; i < m_indexes.size(); i++) {
		if (m_trees[NORTHWEST].Insert(m_circles[i], m_indexes[i])) { circlesToErase.push_back(i); continue; }
		if (m_trees[NORTHEAST].Insert(m_circles[i], m_indexes[i])) { circlesToErase.push_back(i); continue; }
		if (m_trees[SOUTHEAST].Insert(m_circles[i], m_indexes[i])) { circlesToErase.push_back(i); continue; }
		if (m_trees[SOUTHWEST].Insert(m_circles[i], m_indexes[i])) { circlesToErase.push_back(i); continue; }
	}
	for (int i = circlesToErase.size() - 1; i >= 0; i--) {
		m_circles.erase(m_circles.begin() + circlesToErase[i]);
		m_indexes.erase(m_indexes.begin() + circlesToErase[i]);
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
		m_trees[NORTHWEST].Query(range, found);
		m_trees[NORTHEAST].Query(range, found);
		m_trees[SOUTHEAST].Query(range, found);
		m_trees[SOUTHWEST].Query(range, found);
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
