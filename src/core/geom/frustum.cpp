////////////////////////////////////////////////////////////////////////////////
#include "frustum.hpp"
////////////////////////////////////////////////////////////////////////////////
Frustum::Frustum(const Mat4& p)
: planes{Plane(p[3]+p[0], p[7]+p[4], p[11]+p[8], p[15]+p[12]), // Left clipping plane
         Plane(p[3]-p[0], p[7]-p[4], p[11]-p[8], p[15]-p[12]), // Right clipping plane
         Plane(p[3]-p[1], p[7]-p[5], p[11]-p[9], p[15]-p[13]), // Top clipping plane
         Plane(p[3]+p[1], p[7]+p[5], p[11]+p[9], p[15]+p[13]), // Bottom clipping plane
         Plane(p[3]+p[2], p[7]+p[6], p[11]+p[10], p[15]+p[14]), // Near clipping plane
         Plane(p[3]-p[2], p[7]-p[6], p[11]-p[10], p[15]-p[14])  // Far clipping plane
        }
{
    // normalize if we want to be able to compute the distance from planes
    // for frustum culling, often, the sign of the test with the plane is enough
    /*for(int i=0; i<6; ++i)
    {
        planes[i] = planes[i].normalize();
    }*/
}
////////////////////////////////////////////////////////////////////////////////
bool Frustum::intersect(const AABB& box) const
{
    // check box outside/inside of frustum
    for(int p=0; p<6; ++p)
    {
        int out = 0;
        for(int i=0; i<2; ++i)
        {
            for(int j=0; j<2; ++j)
            {
                for(int k=0; k<2; ++k)
                {
                    out += ((planes[p].m_coeffs.dot(Vec4(box[i].x, box[j].y, box[k].z, 1.0)) < 0.0 )?1:0);
                }
            }
        }
        if( out==8 ) return false;
    }

    return true;
}
////////////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& o, const Frustum& frustum)
{
    const char* names[] = {"left  ", "right ", "top   ", "bottom", "near  ", "far   "};
    for(int i=0; i<6; ++i)
    {
        o << names[i] << " : " << frustum.planes[i] << std::endl;
    }
    return o;
}
////////////////////////////////////////////////////////////////////////////////
