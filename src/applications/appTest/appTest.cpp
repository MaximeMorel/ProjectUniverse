////////////////////////////////////////////////////////////////////////////////
#include "appTest.hpp"
#include "core/math/vec2.hpp"
#include "core/math/vec3.hpp"
#include "core/math/mat3.hpp"
#include "core/math/mat4.hpp"
#include "core/geom/boundingVolume/aabb.hpp"
#include "core/geom/octree.hpp"
#include "core/geom/frustum.hpp"
#include "core/tests/testRunner.hpp"
//#include "core/render/windowContext/windowContextSDL2/windowContextSDL2.hpp"
//#include "core/script/lua/testlua.hpp"
#include "core/log/loggerStream.hpp"
#include "core/log/loggerFile.hpp"
#include "core/log/logManager.hpp"
#include <iostream>
#include <thread>
#include <limits>
#include <cmath>
////////////////////////////////////////////////////////////////////////////////
//namespace
////////////////////////////////////////////////////////////////////////////////
int universalExperiment()
{
    std::cout << "sizeof(int32_t) : " <<  sizeof(int32_t) << "\n";
    std::cout << "sizeof(int64_t) : " <<  sizeof(int64_t) << "\n";

    std::cout << "sizeof(float) : " <<  sizeof(float) << "\n";
    std::cout << "sizeof(double) : " <<  sizeof(double) << "\n";

    unsigned long long int c = 299792458ull;
    unsigned long long int au = 149597870700ull;
    unsigned long long int al = 9460730472580800ull;
    unsigned long long int almm = 9460730472580800000ull;
    unsigned long long int pc = 30856775814671916ull;


    // std::cout << "1 au : " << 149597870700ll << " m\n";
    // std::cout << "c : " << 299792458ll << " m / s\n";
    // std::cout << "1 al : " << 299792458ll*3600ll*24ll*365ll + 299792458ll*3600ll*6ll << " m\n";
    // std::cout << "1 al : " << static_cast<long long int>(299792458ll*3600ll*24ll*365.25) << " m\n";
    // std::cout << "1 pc : " << static_cast<long long int>(149597870700ll / tan(1.0/3600.0*M_PI/180.0)) << " m\n";

    std::cout << "1 au : " << au << " m\n";
    std::cout << "c : " << c << " m / s\n";
    std::cout << "1 al : " << al << " m\n";
    std::cout << "1 pc : " << pc << " m\n";

    std::cout << "10 al       : " << 10ull*al << " m\n";
    std::cout << "100 al      : " << 100ull*al << " m\n";
    std::cout << "1000 al     : " << 1000ull*al << " m\n";
    std::cout << "10000 al    : " << 10000ull*al << " m\n";
    std::cout << "100000 al   : " << 100000ull*al << " m\n";
    std::cout << "1000000 al  : " << 1000000ull*al << " m\n";
    std::cout << "10000000 al : " << 10000000ull*al << " m\n";

    std::cout << "1 al        : " << 1ull*almm << " mm\n";
    std::cout << "10 al       : " << 10ull*almm << " mm\n";
    std::cout << "100 al      : " << 100ull*almm << " mm\n";
    std::cout << "1000 al     : " << 1000ull*almm << " mm\n";
    std::cout << "10000 al    : " << 10000ull*almm << " mm\n";
    std::cout << "100000 al   : " << 100000ull*almm << " mm\n";
    std::cout << "1000000 al  : " << 1000000ull*almm << " mm\n";
    std::cout << "10000000 al : " << 10000000ull*almm << " mm\n";

    std::cout << std::numeric_limits<long long int>::digits10 << "\n";
    std::cout << std::numeric_limits<float>::digits10 << "\n";
    std::cout << std::numeric_limits<double>::digits10 << "\n";

    return 0;
}
////////////////////////////////////////////////////////////////////////////////
int universalExperiment2()
{
    std::cout << "sizeof(int32_t) : " <<  sizeof(int32_t) << "\n";
    std::cout << "sizeof(int64_t) : " <<  sizeof(int64_t) << "\n";

    std::cout << "sizeof(float) : " <<  sizeof(float) << "\n";
    std::cout << "sizeof(double) : " <<  sizeof(double) << "\n";

    double c = 299792458.0;
    double au = 149597870700.0;
    double al = 9460730472580800.0;
    double almm = 9460730472580800000.0;
    double pc = 30856775814671916.0;

    // std::cout << "1 au : " << 149597870700ll << " m\n";
    // std::cout << "c : " << 299792458ll << " m / s\n";
    // std::cout << "1 al : " << 299792458ll*3600ll*24ll*365ll + 299792458ll*3600ll*6ll << " m\n";
    // std::cout << "1 al : " << static_cast<long long int>(299792458ll*3600ll*24ll*365.25) << " m\n";
    // std::cout << "1 pc : " << static_cast<long long int>(149597870700ll / tan(1.0/3600.0*M_PI/180.0)) << " m\n";

    std::cout << std::fixed;

    std::cout << "1 au : " << au << " m\n";
    std::cout << "c : " << c << " m / s\n";
    std::cout << "1 al : " << al << " m\n";
    std::cout << "1 pc : " << pc << " m\n";

    std::cout << "1 au + 165,1234m : " << au + 165.1234 << " m\n";
    std::cout << "1 al + 165,1234m : " << al + 165.1234 << " m\n";

    std::cout << "10 al       : " << 10.0*al << " m\n";
    std::cout << "100 al      : " << 100.0*al << " m\n";
    std::cout << "1000 al     : " << 1000.0*al << " m\n";
    std::cout << "10000 al    : " << 10000.0*al << " m\n";
    std::cout << "100000 al   : " << 100000.0*al << " m\n";
    std::cout << "1000000 al  : " << 1000000.0*al << " m\n";
    std::cout << "10000000 al : " << 10000000.0*al << " m\n";

    std::cout << "1 al        : " << 1.0*almm << " mm\n";
    std::cout << "10 al       : " << 10.0*almm << " mm\n";
    std::cout << "100 al      : " << 100.0*almm << " mm\n";
    std::cout << "1000 al     : " << 1000.0*almm << " mm\n";
    std::cout << "10000 al    : " << 10000.0*almm << " mm\n";
    std::cout << "100000 al   : " << 100000.0*almm << " mm\n";
    std::cout << "1000000 al  : " << 1000000.0*almm << " mm\n";
    std::cout << "10000000 al : " << 10000000.0*almm << " mm\n";

    std::cout << std::numeric_limits<long long int>::digits10 << "\n";
    std::cout << std::numeric_limits<float>::digits10 << "\n";
    std::cout << std::numeric_limits<double>::digits10 << "\n";

    return 0;
}
////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    LoggerStream log("stdout", std::cout);
    //luaTest();

    //Vec2 v(0,0);
    //runTests(argc, argv);

    //log << std::thread::hardware_concurrency << "\n";

    universalExperiment();
    universalExperiment2();

    //log << "main : " << main << "\n";
    //log << "&main : " << &main << "\n";
    //log<< "*main : " << *main << "\n";

    //printf("main : %d - %p\n", main, main);
    //printf("&main : %d - %p\n", &main, &main);
    //printf("*main : %d - %p\n", *main, *main);

    /*Mat4 m1 = Mat4::identity();
    log << m1.getMemSize() << "\n";
    m1(0,0) = 5;
    log << m1;

    Mat4 m2 = m1*4;
    log << m2.getMemSize() << "\n";
    log << m2;

    Mat4 m3 = m1*m2;
    log << m3;

    log << m1*m2;
    m1 *= m2;
    log << m1;

    Vec4 a;

    Vec4 v(2,1,2,1);
    log << v << "\n";
    Vec4 v2 = m3*v;
    log << v2 << "\n";*/

    //Mat3 m(5,1,2,10,5,3,8,1,5);
    Mat3 m(1,0,0,0,1,0,0,0,0);
    log << m;
    try
    {
        Mat3 im = m.inverse();
        log << im;
        log << im*m;
    }
    catch(std::exception& e)
    {
        log << e.what() << "\n";
    }

    Mat4 p = Mat4::perspective(90, 16./9., 1., 10000.);
    Mat4 t = Mat4::translate(Vec3(0,5,-5000));
    p = p*t;
    //p = Mat4::ortho(-1000,1000,-1000,1000,-1000,1000);
    //p = Mat4::ortho(-1,1,-1,1,-1,1);
    log << p;

    Frustum f(p);
    log << f;

    srand48(time(0));

    Octree octree(AABB(Vec3(-8388608, -8388608, -8388608), Vec3(8388608, 8388608, 8388608)));
    log << "octree mem : " << octree.getMemSize() << " B depth : " << octree.getDepth() << " nodes : " << octree.getNumNodes() << " elements : " << octree.getNumElements() << "\n";
    for (int i=0; i<100000; ++i)
    {
        //Vec3 p((drand48()-0.5)*2000000000.0, (drand48()-0.5)*2000000000.0, (drand48()-0.5)*2000000000.0);
        Vec3 p((drand48()-0.5)*200000.0, (drand48()-0.5)*200000.0, (drand48()-0.5)*200000.0);
        //log << "insert : " << std::fixed << p << "\n";
        //log << octree.m_bbox << "\n";
        octree.insert(p);
    }
    log << "octree mem : " << octree.getMemSize()/(1024*1024) << " MB depth : " << octree.getDepth() << " nodes : " << octree.getNumNodes() << " elements : " << octree.getNumElements() << "\n";

    std::vector<const Octree*> resTraverse;
    octree.traverse(f, resTraverse);
    log << "traverse : " << resTraverse.size() << "\n";

    //WindowContextSDL2 wCtx;

    //cppunit();

    //int i; std::cin >> i;

    std::string str("unit tests : ");
    log << str;
    log << str;
    log << "\n";

    testRunner();

    return 0;
}
////////////////////////////////////////////////////////////////////////////////
#include "core/plugin/plugin.hpp"
////////////////////////////////////////////////////////////////////////////////
static PluginInfo pluginInfo = { "This app contains unit tests.",
                                 "appTest",
                                 "app",
                                 0,
                                 1};
////////////////////////////////////////////////////////////////////////////////
static ApplicationAppTest* app = nullptr;
////////////////////////////////////////////////////////////////////////////////
const PluginInfo* getPluginInfo()
{
    return &pluginInfo;
}
////////////////////////////////////////////////////////////////////////////////
Application* getAppInstance(Engine* engine)
{
    if (app == nullptr)
    {
        app = new ApplicationAppTest(*engine);
    }
    return app;
}
////////////////////////////////////////////////////////////////////////////////
void closeAppInstance()
{
    delete app;
    app = nullptr;
}

////////////////////////////////////////////////////////////////////////////////
ApplicationAppTest::ApplicationAppTest(Engine& engine)
    : Application(engine)
{
    log().log() << "ApplicationAppTest start...\n";

    runTests();
}
////////////////////////////////////////////////////////////////////////////////
ApplicationAppTest::~ApplicationAppTest()
{
    log().log() << "ApplicationAppTest stop...\n";
}
////////////////////////////////////////////////////////////////////////////////
int ApplicationAppTest::runTests()
{
    return testRunner();
}
////////////////////////////////////////////////////////////////////////////////
