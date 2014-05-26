////////////////////////////////////////////////////////////////////////////////
#include "core/math/vec2.hpp"
#include "core/math/vec3.hpp"
#include "core/math/mat3.hpp"
#include "core/math/mat4.hpp"
#include "core/tests/tests.hpp"
#include "core/render/windowContext/windowContextSDL2/windowContextSDL2.hpp"
//#include "core/script/lua/testlua.hpp"
#include <iostream>
#include <thread>
#include <limits>
#include <cmath>
////////////////////////////////////////////////////////////////////////////////
//namespace
////////////////////////////////////////////////////////////////////////////////
int universalExperiment()
{
    std::cout << "sizeof(int32_t) : " <<  sizeof(int32_t) << std::endl;
    std::cout << "sizeof(int64_t) : " <<  sizeof(int64_t) << std::endl;

    std::cout << "sizeof(float) : " <<  sizeof(float) << std::endl;
    std::cout << "sizeof(double) : " <<  sizeof(double) << std::endl;

    unsigned long long int c = 299792458ull;
    unsigned long long int au = 149597870700ull;
    unsigned long long int al = 9460730472580800ull;
    unsigned long long int almm = 9460730472580800000ull;
    unsigned long long int pc = 30856775814671916ull;


    // std::cout << "1 au : " << 149597870700ll << " m" << std::endl;
    // std::cout << "c : " << 299792458ll << " m / s" << std::endl;
    // std::cout << "1 al : " << 299792458ll*3600ll*24ll*365ll + 299792458ll*3600ll*6ll << " m" << std::endl;
    // std::cout << "1 al : " << static_cast<long long int>(299792458ll*3600ll*24ll*365.25) << " m" << std::endl;
    // std::cout << "1 pc : " << static_cast<long long int>(149597870700ll / tan(1.0/3600.0*M_PI/180.0)) << " m" << std::endl;

    std::cout << "1 au : " << au << " m" << std::endl;
    std::cout << "c : " << c << " m / s" << std::endl;
    std::cout << "1 al : " << al << " m" << std::endl;
    std::cout << "1 pc : " << pc << " m" << std::endl;

    std::cout << "10 al       : " << 10ull*al << " m" << std::endl;
    std::cout << "100 al      : " << 100ull*al << " m" << std::endl;
    std::cout << "1000 al     : " << 1000ull*al << " m" << std::endl;
    std::cout << "10000 al    : " << 10000ull*al << " m" << std::endl;
    std::cout << "100000 al   : " << 100000ull*al << " m" << std::endl;
    std::cout << "1000000 al  : " << 1000000ull*al << " m" << std::endl;
    std::cout << "10000000 al : " << 10000000ull*al << " m" << std::endl;

    std::cout << "1 al        : " << 1ull*almm << " mm" << std::endl;
    std::cout << "10 al       : " << 10ull*almm << " mm" << std::endl;
    std::cout << "100 al      : " << 100ull*almm << " mm" << std::endl;
    std::cout << "1000 al     : " << 1000ull*almm << " mm" << std::endl;
    std::cout << "10000 al    : " << 10000ull*almm << " mm" << std::endl;
    std::cout << "100000 al   : " << 100000ull*almm << " mm" << std::endl;
    std::cout << "1000000 al  : " << 1000000ull*almm << " mm" << std::endl;
    std::cout << "10000000 al : " << 10000000ull*almm << " mm" << std::endl;

    std::cout << std::numeric_limits<long long int>::digits10 << std::endl;

    return 0;
}
////////////////////////////////////////////////////////////////////////////////
class AABB
{
public:
    AABB(const Vec3& pMin, const Vec3& pMax)
    : min(pMin), max(pMax)
    {
    }

    void add(const Vec3& v)
    {
        if(v.x < min.x) min.x = v.x;
        else if(v.x > max.x) max.x = v.x;

        if(v.y < min.y) min.y = v.y;
        else if(v.y > max.y) max.y = v.y;

        if(v.z < min.z) min.z = v.z;
        else if(v.z > max.z) max.z = v.z;
    }

    void add(const AABB& box)
    {
        add(box.min);
        add(box.max);
    }

    bool intersect(const Vec3& p) const
    {
        return (p.x > min.x && p.x < max.x &&
                p.y > min.y && p.y < max.y &&
                p.z > min.z && p.z < max.z);
    }

    size_t getMemSize() const
    {
        return sizeof(*this);
    }

    friend std::ostream& operator<<(std::ostream& o, const AABB& aabb)
    {
        return o << aabb.min << " / " << aabb.max;
    }

    Vec3 min, max;
};
//std::ostream& operator<<(std::ostream& o, const AABB& aabb)
//{
//    return o << aabb.min << " / " << aabb.max;
//}
////////////////////////////////////////////////////////////////////////////////
class Octree
{
public:
    Octree(const AABB& box, Octree* parent=nullptr)
    : m_parent(parent), m_children{nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, m_bbox(box)
    {

    }

    ~Octree()
    {
        for(int i=0; i<8; ++i)
        {
            delete m_children[i];
        }
    }

    size_t getDepth() const
    {
        if(!m_children[0])
        {
            return 0;
        }

        size_t res = 0;
        for(int i=0; i<8; ++i)
        {
            res = std::max(m_children[i]->getDepth(), res);
        }
        return 1+res;
    }

    size_t getMemSize() const
    {
        size_t res = sizeof(*this);
        for(int i=0; i<8; ++i)
        {
            res += (m_children[i]?m_children[i]->getMemSize():0);
        }
        return res;
    }

    void subdivide()
    {
        Vec3 corner, len = (m_bbox.max - m_bbox.min)*0.5f;
        for(int i=0; i<2; ++i)
        {
            for(int j=0; j<2; ++j)
            {
                for(int k=0; k<2; ++k)
                {
                    corner = m_bbox.min + Vec3(len.x*i, len.y*j, len.z*k);
                    m_children[j + 2*i + 4*k] = new Octree(AABB(corner, corner+len), this);
                    //std::cout << std::fixed << j + 2*i + 4*k << " " << i << " " << j << " " << k << " -> " << m_children[j + 2*i + 4*k]->m_bbox << std::endl;
                }
            }
        }
    }

    void insert(const Vec3& p)
    {
        if(m_bbox.intersect(p))
        {
            if(m_bbox.max.x - m_bbox.min.x > 100.0f)
            {
                subdivide();
                for(int i=0; i<8; ++i)
                {
                    m_children[i]->insert(p);
                }
            }
        }
    }

    Octree* m_parent;
    Octree* m_children[8];

    AABB m_bbox;
};
////////////////////////////////////////////////////////////////////////////////
void octreeTest(int depth)
{
    //for(int x = 0; x)
}
////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    //luaTest();

    //Vec2 v(0,0);
    runTests(argc, argv);

    std::cout << std::thread::hardware_concurrency << std::endl;

    universalExperiment();

    std::cout << "main : " << main << std::endl;
    std::cout << "&main : " << &main << std::endl;
    std::cout << "*main : " << *main << std::endl;

    printf("main : %d - %p\n", main, main);
    printf("&main : %d - %p\n", &main, &main);
    printf("*main : %d - %p\n", *main, *main);

    Mat4 m1(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
    std::cout << m1.getMemSize() << std::endl;
    m1(0,0) = 5;
    std::cout << m1;

    Mat4 m2 = m1*4;
    std::cout << m2.getMemSize() << std::endl;
    std::cout << m2;

    Mat4 m3 = m1*m2;
    std::cout << m3;

    std::cout << m1*m2;
    m1 *= m2;
    std::cout << m1;

    Vec4 a;

    Vec4 v(2,1,2,1);
    std::cout << v << std::endl;
    Vec4 v2 = m3*v;
    std::cout << v2 << std::endl;

    Octree octree(AABB(Vec3(-1000000000, -1000000000, -100000000), Vec3(1000000000, 1000000000, 1000000000)));
    octree.insert(Vec3(10, 10, 10));
    std::cout << "octree mem : " << octree.getMemSize() << " depth : " << octree.getDepth() << std::endl;

    WindowContextSDL2 wCtx;

    cppunit();

    //int i; std::cin >> i;

    return 0;
}
////////////////////////////////////////////////////////////////////////////////
