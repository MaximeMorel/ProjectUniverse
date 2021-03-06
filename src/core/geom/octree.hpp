#ifndef __OCTREE_HPP__
#define __OCTREE_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/geom/frustum.hpp"
#include "core/geom/boundingVolume/aabb.hpp"
#include "core/entity/entity.hpp"
#include <vector>
////////////////////////////////////////////////////////////////////////////////
class Octree
{
public:
    Octree(const AABB& box, Octree* parent=nullptr);

    ~Octree();

    size_t getDepth() const;

    size_t getNumNodes() const;

    size_t getNumElements() const;

    size_t getMemSize() const;

    Octree* getChild(const Vec3& p);

    void insert(const Vec3& p);

    void traverse(const Frustum& frustum, std::vector<const Octree*>& res) const;

private:
    Octree* m_parent;
    Octree* m_children[8];
    std::vector<Entity> m_elements;
    int m_numElements;

    AABB m_bbox;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __OCTREE_HPP__
