#include "SubdivisionSphereTesselator.h"

#include "geo/VertexAttribute.h"
#include "renderer/Indices.h"

#include "Log.h"

using namespace std;
using namespace revel::math;
using namespace revel::renderer;

namespace revel
{
namespace geo
{

SubdivisionSphereTesselator::SubdivisionSphereTesselator()
{
}

std::shared_ptr<Mesh>
SubdivisionSphereTesselator::compute(i32 subdivisions)
{
    auto mesh = make_shared<Mesh>();
    auto pos = mesh->create_vertex_attrib<point3>("position");
    auto indices = mesh->indices<u32>();

    pos->data().push_back(point3(0, 0, 1));
    pos->data().push_back(point3(0, 2.0 * sqrt(2.0) / 3.0, -1.0/3.0));
    pos->data().push_back(point3(-sqrt(6.0)/3.0, -sqrt(2.0)/3.0, -1.0/3.0));
    pos->data().push_back(point3(sqrt(6.0)/3.0, -sqrt(2.0)/3.0, -1.0/3.0));

    indices->add_triangle(0, 1, 2);
    indices->add_triangle(0, 2, 3);
    indices->add_triangle(0, 3, 1);
    indices->add_triangle(1, 3, 2);

    subdivide(pos->data(), indices, 0, 1, 2, subdivisions);
    subdivide(pos->data(), indices, 0, 2, 3, subdivisions);
    subdivide(pos->data(), indices, 0, 3, 1, subdivisions);
    subdivide(pos->data(), indices, 1, 3, 2, subdivisions);

    return mesh;
}

void
SubdivisionSphereTesselator::subdivide(std::vector<point3> &pos, const IndicesPtr& indices, u32 i0, u32 i1, u32 i2, i32 level)
{
    if (level > 0)
    {
        pos.push_back((static_cast<vec3>(pos[i0]) + static_cast<vec3>(pos[i1])).normalized());
        pos.push_back((static_cast<vec3>(pos[i1]) + static_cast<vec3>(pos[i2])).normalized());
        pos.push_back((static_cast<vec3>(pos[i2]) + static_cast<vec3>(pos[i0])).normalized());

        i32 next_i01 = pos.size() - 3;
        i32 next_i12 = pos.size() - 2;
        i32 next_i20 = pos.size() - 1;

        --level;

        subdivide(pos, indices, i0, next_i01, next_i20, level);
        subdivide(pos, indices, next_i01, i1, next_i12, level);
        subdivide(pos, indices, next_i01, next_i12, next_i20, level);
        subdivide(pos, indices, next_i20, next_i12, i2, level);
    }
    else
    {
        indices->add_triangle(i0, i1, i2);
    }
}

}
}


