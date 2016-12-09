////////////////////////////////////////////////////////////////////////////////
#include "application.hpp"
#include "core/log/loggerStream.hpp"
#include "core/log/loggerNull.hpp"
#include "core/tools/timer.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <btBulletDynamicsCommon.h>
#include "core/render/renderPlugin.hpp"
#include "core/windowContext/windowPlugin.hpp"
////////////////////////////////////////////////////////////////////////////////
int main2(int argc, char** argv)
{
   /*std::cout << "test log begin\n";
    LoggerStreamBuf buf(std::cout);
    //LoggerStream log("stdout", buf);
    LoggerStream log("stdout", std::cout);
    log << "Init main...\n";
    std::cout << "test log end\n";*/

    return 0;
}
////////////////////////////////////////////////////////////////////////////////


#include <iostream>
#include <string>
////////////////////////////////////////////////////////////////////////////////
//template <class T>
class ResTypeId
{
public:
    int m_id;
    std::string m_name;
    ResTypeId* m_parent;

    ResTypeId& getParent()
    {
        return *m_parent;
    }
};
////////////////////////////////////////////////////////////////////////////////
//template <class T>
std::ostream& operator<<(std::ostream& o, const ResTypeId& rhs)
{
    return o << rhs.m_id << " : " << rhs.m_name << '(' << (rhs.m_parent?*rhs.m_parent:ResTypeId{-1, "top"}) << ')';
}
////////////////////////////////////////////////////////////////////////////////
class IRes
{
public:
    virtual ResTypeId& getResTypeId()
    {
        return s_resTypeId;
    }

    static ResTypeId& _getResTypeId()
    {
        return s_resTypeId;
    }

    static ResTypeId s_resTypeId;
};
ResTypeId IRes::s_resTypeId;
////////////////////////////////////////////////////////////////////////////////
class A : public IRes
{
public:
    using Super = IRes;

    virtual ResTypeId& getResTypeId()
    {
        return s_resTypeId;
    }

    static ResTypeId& _getResTypeId()
    {
        return s_resTypeId;
    }

    static ResTypeId s_resTypeId;
};
ResTypeId A::s_resTypeId;
////////////////////////////////////////////////////////////////////////////////
class A1 : public A
{
public:
    using Super = A;

    virtual ResTypeId& getResTypeId()
    {
        return s_resTypeId;
    }

    static ResTypeId& _getResTypeId()
    {
        return s_resTypeId;
    }

    static ResTypeId s_resTypeId;
};
ResTypeId A1::s_resTypeId;
////////////////////////////////////////////////////////////////////////////////
class B : public IRes
{
public:
    using Super = IRes;

    virtual ResTypeId& getResTypeId()
    {
        return s_resTypeId;
    }

    static ResTypeId& _getResTypeId()
    {
        return s_resTypeId;
    }

    static ResTypeId s_resTypeId;
};
ResTypeId B::s_resTypeId;
////////////////////////////////////////////////////////////////////////////////
class ResMan
{
public:
    //void register(int);


};
////////////////////////////////////////////////////////////////////////////////
int main4(int argc, char** argv)
{
    IRes::_getResTypeId().m_id = 0;
    IRes::_getResTypeId().m_name = "IRes";
    IRes::_getResTypeId().m_parent = nullptr;
    A::_getResTypeId().m_id = 1;
    A::_getResTypeId().m_name = "A";
    A::_getResTypeId().m_parent = &A::Super::_getResTypeId();
    A1::_getResTypeId().m_id = 2;
    A1::_getResTypeId().m_name = "A1";
    A1::_getResTypeId().m_parent = &A1::Super::_getResTypeId();
    B::_getResTypeId().m_id = 3;
    B::_getResTypeId().m_name = "B";
    B::_getResTypeId().m_parent = &B::Super::_getResTypeId();

    A a;
    A1 a1;
    B b;

    IRes& r1 = a;
    IRes& r2 = a1;
    IRes& r3 = b;

    std::cout << A::_getResTypeId() << "\n";
    std::cout << A1::_getResTypeId() << "\n";
    std::cout << B::_getResTypeId() << "\n";

    std::cout << r1.getResTypeId() << "\n";
    std::cout << r2.getResTypeId() << "\n";
    std::cout << r3.getResTypeId() << "\n";

    return 0;
}
////////////////////////////////////////////////////////////////////////////////





/*#include <iostream>
#include <fstream>
#include <vector>

class log : public std::basic_ostream<char>
{
public:
    log(std::basic_streambuf<char> *sb)
    : std::basic_ostream<char>(sb)
    {
    }

    virtual ~log() override
    {
    }
};

class logfilebuf : public std::filebuf
{
public:
    logfilebuf(const char* f)
    {
        open(f, std::ios_base::out);
    }

    virtual int_type overflow(int_type c = traits_type::eof())
    {
        return std::filebuf::overflow(c);
    }

private:
};

class log2 : public std::basic_ostream<char>
{
public:
    log2(const char* f)
    : m_buf(f)
    {
        rdbuf(&m_buf);
    }

    virtual ~log2() override
    {
    }

    logfilebuf m_buf;
};

class logstringbuf : public std::stringbuf
{
public:

    virtual int_type overflow(int_type c = traits_type::eof())
    {
        return std::stringbuf::overflow(c);
    }

private:
};

class loggroupbuf : public std::basic_streambuf<char>
{
public:
    void add(std::basic_streambuf<char> *strBuf)
    {
        mBufs.push_back(strBuf);
    }

    virtual int_type overflow(int_type c = traits_type::eof())
    {
        for (auto *buf : mBufs) {
            buf->sputc(c);
        }
        return c;
    }

private:
    std::vector<std::basic_streambuf<char> *> mBufs;
};*/

void processArgs(int argc, char **argv)
{
    for (int i = 0; i < argc; ++i)
    {

    }
}

int main(int argc, char **argv)
{
    std::cout << "Start...\n";
    Engine engine("main");

    /*PluginAppPtr app = res().createFromFile<PluginApp>("AppNull/libAppNull.so");
    if (app && app->isValid())
    {
        engine.log().log() << app << "\n";
        app->getLibInstance(&engine);
    }

    // AppTest
    app = res().createFromFile<PluginApp>("AppTest/libAppTest.so");
    if (app && app->isValid())
    {
        engine.log().log() << app  << "\n";
        app->getLibInstance(&engine);
    }
    app = nullptr;

    PluginLibPtr lib = res().createFromFile<PluginLib>("libRenderNull.so");
    if (lib && lib->isValid())
    {
        engine.log().log() << lib << "\n";
        lib->getLibInstance(&engine);
    }

    lib = res().createFromFile<PluginLib>("libRenderVulkan.so");
    if (lib && lib->isValid())
    {
        engine.log().log() << lib << "\n";
        lib->getLibInstance(&engine);
    }
    lib = nullptr;

    {
        // Build the broadphase
        btBroadphaseInterface* broadphase = new btDbvtBroadphase();

        // Set up the collision configuration and dispatcher
        btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
        btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);

        // The actual physics solver
        btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

        // The world.
        btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
        dynamicsWorld->setGravity(btVector3(0, -10, 0));

        // Do_everything_else_here
        // Clean up behind ourselves like good little programmers
        delete dynamicsWorld;
        delete solver;
        delete dispatcher;
        delete collisionConfiguration;
        delete broadphase;
    }*/

    {
        PluginLibPtr libWindow = res().createFromFile<PluginLib>("libwindowContextSDL2.so");
        PluginLibPtr libRender = res().createFromFile<PluginLib>("libRenderOpenGL4.so");
        PluginLibPtr libInput = res().createFromFile<PluginLib>("libInputSDL.so");
        PluginLibPtr libAudio = res().createFromFile<PluginLib>("libAudioOpenAL.so");
        if (libAudio && libAudio->isValid())
        {
            engine.log().log() << libAudio << "\n";
            libAudio->getLibInstance(&engine);
        }
        if (libWindow && libRender && libInput &&
            libWindow->isValid() && libRender->isValid() && libInput->isValid())
        {
            engine.log().log() << libWindow << "\n";
            engine.log().log() << libRender << "\n";
            engine.log().log() << libInput << "\n";

            WindowPlugin* w = static_cast<WindowPlugin*>(libWindow->getLibInstance(&engine));
            //w->setResolution(Vec2i(1280, 720));

            libInput->getLibInstance(&engine);
            engine.input().setPlugin(libInput);
            engine.input().discoverDevices();
            engine.input().listDevices(engine.log().log());

            libRender->getLibInstance(&engine);
            engine.render().setPlugin(libRender);

            ShaderProgramPtr prog = res().createFromFile<ShaderProgram>("effect1.prog");
            if (prog)
                prog->bind();

            VAOPtr v = res().create<VAO>("vao");
            if (v)
                v->bind();

            bool stop = false;

            double targetFrameTime = 1000.0 / 60.0;
            double timeSlept = 0.0;
            Timer timer;
            timer.start();
            int fps = 0;
            Timer frameTimer;

            Timer gameTimer;
            gameTimer.start();
            while (!stop)
            {
                frameTimer.reset();
                engine.input().update();
                if (engine.input().keyboard(0) &&
                    engine.input().keyboard(0)->isPressed(Input::Keyboard::KEY_a))
                {
                    ;
                }

                if (engine.input().keyboard(0) &&
                    engine.input().keyboard(0)->isPressed(Input::Keyboard::KEY_ESC))
                {
                    stop = true;
                }

                if (engine.input().mouse(0) &&
                    engine.input().mouse(0)->isPressed(Input::Mouse::BT_1))
                {
                    ;
                }

                if (engine.input().joystick(0) &&
                    engine.input().joystick(0)->isPressed(Input::Joystick::BT_1))
                {
                    ;
                }

                if (engine.input().joystick(0) &&
                    engine.input().joystick(0)->value(Input::Joystick::AXIS_1) > 0.5)
                {
                    ;
                }

                v->bind();
                prog->bind();
                prog->setUniform1f(0u, gameTimer.getTime()/1000.0);
                render().impl()->draw();
                w->swapBuffers();

                double frameTimeEnd = frameTimer.getTime();
                //engine.log().log() << "frame time: " << frameTime << std::endl;
                //engine.log().log() << "potential fps: " << 1000.0/frameTime << std::endl;

                ++fps;
                if (frameTimeEnd < targetFrameTime)
                {
                    //engine.log().log() << "wait: " << targetFrameTime - frameTime << std::endl;
                    Timer::wait(targetFrameTime - frameTimeEnd);
                    timeSlept += targetFrameTime - frameTimeEnd;
                }
                else
                {
                    engine.log().log() << "frame time: " << frameTimeEnd << std::endl;
                }

                if (timer.getTime() >= 1000)
                {
                    engine.log().log() << "fps: " << fps << " (" << timeSlept * 0.1 << "% idle)" << std::endl;
                    fps = 0;
                    timeSlept = 0.0;
                    timer.reset();
                }
            }
        }
    }

    log().log() << res() << std::endl;

    std::cout << "main exit...\n";

    return 0;
}
