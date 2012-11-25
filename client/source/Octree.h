#ifndef OCTREE_H
#define OCTREE_H

#include <array>
#include <memory>
#include <vector>

#include "math/Vector3.h"

#include "BoundingVolume.h"

namespace revel
{

template <typename T> class Octree;

template <typename T>
class OctNode
{
    friend class Octree<T>;

protected:
    std::array<std::unique_ptr<OctNode>, 8> m_Children;
    std::vector<T> m_NodeData;

public:
    OctNode() {}

    const std::vector<T>& data() const { return m_NodeData; }
    std::vector<T>& data() { return m_NodeData; }
};



template <typename T>
class Octree
{
    i32 m_MaxDepth;
    BBox m_BBox;

    OctNode<T> m_Root;

public:
    Octree() {}

    Octree& add(const OctNode<T>& item, const BBox& bbox)
    {
        //TODO: Implement
    }


    BBox octree_child_bound(i32 child, const BBox& bv, const point3& mid)
    {
        //TODO: Implement
    }

private:
    void add(OctNode<T>* node, const BBox& nbv, const T& data, const BBox& dbv, f32 diag2, i32 depth)
    {
        if (depth == m_MaxDepth || (nbv.p2() - nbv.p1()).length_squared() < diag2)
        {
            node->m_NodeData.push_back(data);
        }
        else
        {
            point3 mid = (nbv.p2() - nbv.p1()) * 0.5f;

            //Determine which children the item overlaps
            bool x[2] = { dbv.p1().x <= mid.x, dbv.p2().x > mid.x };
            bool y[2] = { dbv.p1().y <= mid.y, dbv.p2().y > mid.y };
            bool z[2] = { dbv.p1().z <= mid.z, dbv.p2().z > mid.z };
            bool over[8] = { x[0] & y[0] & z[0], x[0] & y[0] & z[1],
                             x[0] & y[1] & z[0], x[0] & y[1] & z[1],
                             x[1] & y[0] & z[0], x[1] & y[0] & z[1],
                             x[1] & y[1] & z[0], x[1] & y[1] & z[1] };

            for (i32 i = 0; i < 8; ++i)
            {
                if (over[i])
                {
                    if (!node->m_Children[i])
                    {
                        OctNode<T>* ptr = new OctNode<T>();

                        //auto ptr = std::unique_ptr<OctNode>(new OctNode<T>());
                        //node->m_Children[i] = ptr;
                    }

                    BBox cbv = octree_child_bound(i, nbv, mid);
                    add(node->m_Children[i], cbv, data, dbv, diag2, depth + 1);
                }


            }
        }

    }
};

}


#endif // OCTREE_H
