////////////////////////////////////////////////////////////////////////////////
#include "frustum.hpp"
#include <iostream>
////////////////////////////////////////////////////////////////////////////////
Frustum::Frustum(const Mat4& p)
    : planes{SurfacePlane(p[3] + p[0], p[7] + p[4], p[11] + p[8],  p[15] + p[12]), // Left clipping SurfacePlane
             SurfacePlane(p[3] - p[0], p[7] - p[4], p[11] - p[8],  p[15] - p[12]), // Right clipping SurfacePlane
             SurfacePlane(p[3] - p[1], p[7] - p[5], p[11] - p[9],  p[15] - p[13]), // Top clipping SurfacePlane
             SurfacePlane(p[3] + p[1], p[7] + p[5], p[11] + p[9],  p[15] + p[13]), // Bottom clipping SurfacePlane
             SurfacePlane(p[3] + p[2], p[7] + p[6], p[11] + p[10], p[15] + p[14]), // Near clipping SurfacePlane
             SurfacePlane(p[3] - p[2], p[7] - p[6], p[11] - p[10], p[15] - p[14])  // Far clipping SurfacePlane
            }
    , corners{SurfacePlane::intersect(planes[4], planes[0], planes[3]), // near left bottom
              SurfacePlane::intersect(planes[4], planes[1], planes[3]), // near right bottom
              SurfacePlane::intersect(planes[4], planes[1], planes[2]), // near right top
              SurfacePlane::intersect(planes[4], planes[0], planes[2]), // near left top
              SurfacePlane::intersect(planes[5], planes[0], planes[2]), // far left top
              SurfacePlane::intersect(planes[5], planes[1], planes[2]), // far right top
              SurfacePlane::intersect(planes[5], planes[1], planes[3]), // far right bottom
              SurfacePlane::intersect(planes[5], planes[0], planes[3])  // far left bottom
             }
{
    // normalize if we want to be able to compute the distance from SurfacePlanes
    // for frustum culling, often, the sign of the test with the SurfacePlane is enough
    /*
    for (int i = 0; i < 6; ++i)
    {
        SurfacePlanes[i] = SurfacePlanes[i].normalize();
    }//*/

    // compute corners
    /*
    corners[0] = SurfacePlane::intersect(SurfacePlanes[4], SurfacePlanes[0], SurfacePlanes[3]); // near left bottom
    corners[1] = SurfacePlane::intersect(SurfacePlanes[4], SurfacePlanes[1], SurfacePlanes[3]); // near right bottom
    corners[2] = SurfacePlane::intersect(SurfacePlanes[4], SurfacePlanes[1], SurfacePlanes[2]); // near right top
    corners[3] = SurfacePlane::intersect(SurfacePlanes[4], SurfacePlanes[0], SurfacePlanes[2]); // near left top
    corners[4] = SurfacePlane::intersect(SurfacePlanes[5], SurfacePlanes[0], SurfacePlanes[2]); // far left top
    corners[5] = SurfacePlane::intersect(SurfacePlanes[5], SurfacePlanes[1], SurfacePlanes[2]); // far right top
    corners[6] = SurfacePlane::intersect(SurfacePlanes[5], SurfacePlanes[1], SurfacePlanes[3]); // far right bottom
    corners[7] = SurfacePlane::intersect(SurfacePlanes[5], SurfacePlanes[0], SurfacePlanes[3]); // far left bottom
    //*/
}
////////////////////////////////////////////////////////////////////////////////
bool Frustum::intersect(const Vec3& pt) const
{
    // check box outside/inside of frustum
    for (int p = 0; p < 6; ++p)
    {
        if (((planes[p].getCoeffs().dot(Vec4(pt, 1.0))) < 0.0 ) ? 1:0)
            return false;
    }

    return true;
}
////////////////////////////////////////////////////////////////////////////////
bool Frustum::intersect(const AABB& box) const
{
    // check box outside/inside of frustum
    for (int p = 0; p < 6; ++p)
    {
        int out = 0;
        for (int i = 0; i < 2; ++i)
        {
            for (int j = 0; j < 2; ++j)
            {
                for (int k = 0; k < 2; ++k)
                {
                    //std::cout << "(" << i << "," << j << "," << k << ") : " << Vec4(box[i].x, box[j].y, box[k].z, 1.0) << std::endl;
                    out += ((planes[p].getCoeffs().dot(Vec4(box[i].x, box[j].y, box[k].z, 1.0)) < 0.0 ) ? 1:0);
                }
            }
        }
        if (out == 8)
        {
            return false;
        }
    }

    return true;
}
////////////////////////////////////////////////////////////////////////////////
Logger& operator<<(Logger& o, const Frustum& frustum)
{
    const char* names[] = {"left  ", "right ", "top   ", "bottom", "near  ", "far   "};
    for (int i = 0; i < 6; ++i)
    {
        o << names[i] << " : " << frustum.planes[i] << "\n";
    }
    for (int i = 0; i < 8; ++i)
    {
        o << frustum.corners[i] << "\n";
    }
    o << std::flush;
    return o;
}
////////////////////////////////////////////////////////////////////////////////

