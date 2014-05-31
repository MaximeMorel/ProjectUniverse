////////////////////////////////////////////////////////////////////////////////
#include "core/math/vec2.hpp"
#include "core/math/vec3.hpp"
#include "core/math/mat3.hpp"
#include "core/math/mat4.hpp"
#include "core/geom/aabb.hpp"
#include "core/geom/octree.hpp"
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
    std::cout << std::numeric_limits<float>::digits10 << std::endl;
    std::cout << std::numeric_limits<double>::digits10 << std::endl;

    return 0;
}
////////////////////////////////////////////////////////////////////////////////
class Frustum
{
public:
};
////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    //luaTest();

    //Vec2 v(0,0);
    //runTests(argc, argv);

    //std::cout << std::thread::hardware_concurrency << std::endl;

    universalExperiment();

    //std::cout << "main : " << main << std::endl;
    //std::cout << "&main : " << &main << std::endl;
    //std::cout << "*main : " << *main << std::endl;

    //printf("main : %d - %p\n", main, main);
    //printf("&main : %d - %p\n", &main, &main);
    //printf("*main : %d - %p\n", *main, *main);

    /*Mat4 m1 = Mat4::identity();
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
    std::cout << v2 << std::endl;*/

    //Mat3 m(5,1,2,10,5,3,8,1,5);
    Mat3 m(1,0,0,0,1,0,0,0,0);
    std::cout << m;
    try
    {
        Mat3 im = m.inverse();
        std::cout << im;
        std::cout << im*m;
    }
    catch(std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    //srand48(time(0));

    Octree octree(AABB(Vec3(-8388608, -8388608, -8388608), Vec3(8388608, 8388608, 8388608)));
    std::cout << "octree mem : " << octree.getMemSize() << " B depth : " << octree.getDepth() << " nodes : " << octree.getNumNodes() << " elements : " << octree.getNumElements() << std::endl;
    for(int i=0; i<1000000; ++i)
    {
        //Vec3 p((drand48()-0.5)*2000000000.0, (drand48()-0.5)*2000000000.0, (drand48()-0.5)*2000000000.0);
        Vec3 p((drand48()-0.5)*200000.0, (drand48()-0.5)*200000.0, (drand48()-0.5)*200000.0);
        //std::cout << "insert : " << std::fixed << p << std::endl;
        //std::cout << octree.m_bbox << std::endl;
        octree.insert(p);
    }
    std::cout << "octree mem : " << octree.getMemSize()/(1024*1024) << " MB depth : " << octree.getDepth() << " nodes : " << octree.getNumNodes() << " elements : " << octree.getNumElements() << std::endl;

    //WindowContextSDL2 wCtx;

    //cppunit();

    //int i; std::cin >> i;

    return 0;
}
////////////////////////////////////////////////////////////////////////////////
