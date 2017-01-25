////////////////////////////////////////////////////////////////////////////////
#include "octree.hpp"
#include <algorithm>
////////////////////////////////////////////////////////////////////////////////
Octree::Octree(const AABB& box, Octree* parent)
    : m_parent(parent)
    , m_children{nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}
    , m_numElements(0)
    , m_bbox(box)
{

}
////////////////////////////////////////////////////////////////////////////////
Octree::~Octree()
{
    for (int i = 0; i < 8; ++i)
    {
        delete m_children[i];
    }
}
////////////////////////////////////////////////////////////////////////////////
size_t Octree::getDepth() const
{
    size_t res = 0ul;
    bool empty = true;
    for (int i = 0; i < 8; ++i)
    {
        if (!m_children[i]) continue;
        empty = false;
        res = std::max(m_children[i]->getDepth(), res);
    }

    return (empty?0:1+res);
}
////////////////////////////////////////////////////////////////////////////////
size_t Octree::getNumNodes() const
{
    size_t res = 0ul;
    for (int i = 0; i < 8; ++i)
    {
        if (!m_children[i])
        {
            continue;
        }
        res += m_children[i]->getNumNodes();
    }
    return (1 + res);
}
////////////////////////////////////////////////////////////////////////////////
size_t Octree::getNumElements() const
{
    size_t res = m_numElements; //m_elements.size();
    for (int i = 0; i < 8; ++i)
    {
        if (!m_children[i])
        {
            continue;
        }
        res += m_children[i]->getNumElements();
    }
    return res;
}
////////////////////////////////////////////////////////////////////////////////
size_t Octree::getMemSize() const
{
    size_t res = sizeof(*this);
    for (int i = 0; i < 8; ++i)
    {
        res += (m_children[i] ? m_children[i]->getMemSize() : 0);
    }
    return res;
}
////////////////////////////////////////////////////////////////////////////////
Octree* Octree::getChild(const Vec3& p)
{
    Vec3 len = (m_bbox.max - m_bbox.min)*0.5;

    /*
    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < 2; ++j)
        {
            for (int k = 0; k < 2; ++k)
            {
                size_t id = i + 2 * j + 4 * k;
                if (!m_children[id])
                {
                    Vec3 corner = m_bbox.min + Vec3(len.x * i, len.y * j, len.z * k);
                    m_children[id] = new Octree(AABB(corner, corner+len), this);
                }
            }
        }
    }//*/

    int i = 0;
    int j = 0;
    int k = 0;

    if (p.x > m_bbox.min.x + len.x) i = 1;
    if (p.y > m_bbox.min.y + len.y) j = 1;
    if (p.z > m_bbox.min.z + len.z) k = 1;

    size_t id = i + 2 * j + 4 * k;
    if (!m_children[id])
    {
        Vec3 corner = m_bbox.min + Vec3(len.x * i, len.y * j, len.z * k);
        m_children[id] = new Octree(AABB(corner, corner+len), this);
        //std::cout << std::fixed << id << " " << i << " " << j << " " << k << " -> " << m_children[id]->m_bbox << "\n";
    }
    return m_children[id];
}
////////////////////////////////////////////////////////////////////////////////
void Octree::insert(const Vec3& p)
{
    if (m_bbox.intersect(p))
    {
        if (m_bbox.max.x - m_bbox.min.x > 10.0f)
        {
            Octree* child = getChild(p);
            child->insert(p);
        }
        else
        {
            //std::cout << "inserted\n";
            //m_elements.push_back(p);
            ++m_numElements;
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
void Octree::traverse(const Frustum& frustum, std::vector<const Octree*>& res) const
{
    if (frustum.intersect(m_bbox))
    {
        //bool empty = true;
        for (int i = 0; i < 8; ++i)
        {
            if (m_children[i])
            {
                m_children[i]->traverse(frustum, res);
                //empty = false;
            }
        }
        //if (empty)
        if (m_numElements > 0)
        {
            res.push_back(this);
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
