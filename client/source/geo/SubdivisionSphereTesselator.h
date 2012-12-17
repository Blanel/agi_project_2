#ifndef SUBDIVISIONSPHERETESSELATOR_H
#define SUBDIVISIONSPHERETESSELATOR_H

#include "Types.h"
#include "math/Vector3.h"
#include "geo/Mesh.h"
#include <memory>
#include <vector>

namespace revel
{
namespace geo
{

class SubdivisionSphereTesselator
{
    void subdivide(std::vector<point3>& pos, const IndicesPtr& indices, u32 i0, u32 i1, u32 i2, i32 level);
public:
    SubdivisionSphereTesselator();

    std::shared_ptr<Mesh> compute(i32 subdivisions);
};

}
}

#endif // SUBDIVISIONSPHERETESSELATOR_H
