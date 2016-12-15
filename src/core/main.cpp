////////////////////////////////////////////////////////////////////////////////
#include "engine.hpp"
#include "application.hpp"
#include "core/log/loggerStream.hpp"
#include "core/log/loggerNull.hpp"
#include "core/tools/timer.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include "core/render/renderPlugin.hpp"
#include "core/windowContext/windowPlugin.hpp"
#include "core/coretypes/image.hpp"
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

class logstringbuf : public std::stringbufNew Event
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
    lib = nullptr;*/

    ImageRGBAPtr image;
    PluginLibPtr libJPEG = res().createFromFile<PluginLib>("libImageCodecJPEG.so");
    if (libJPEG && libJPEG->isValid())
    {
        engine.log().log() << libJPEG << "\n";
        libJPEG->getLibInstance(&engine);

        ImageRGBAPtr im = res().createFromFile<ImageRGBA>("data/images/im.jpg");
        im->save("a.jpg");
        image = im;
    }

    PluginLibPtr libPNG = res().createFromFile<PluginLib>("libImageCodecPNG.so");
    if (libPNG && libPNG->isValid())
    {
        engine.log().log() << libPNG << "\n";
        libPNG->getLibInstance(&engine);

        ImageRGBAPtr im = res().createFromFile<ImageRGBA>("data/images/im2.png");
        image = im;
    }

    PluginLibPtr lib = res().createFromFile<PluginLib>("libImageCodecSDL.so");
    if (lib && lib->isValid())
    {
        engine.log().log() << lib << "\n";
        lib->getLibInstance(&engine);

        ImageRGBAPtr im = res().createFromFile<ImageRGBA>("data/images/im.jpg");
        im->save("a.png");
        image = im;
    }
    //lib = nullptr;

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

            //SoundPtr sound = res().createFromFile<Sound>("data/sound/test.ogg");
            //SoundSourcePtr s = res().createFromFile<SoundSource>("data/sound/test.ogg");
            //sound->play();
            //audio().play(sound, );
            //s->position(0,0,0);
            //s->velocity(1,0,0);
            //s->volume(0.75);
            //s->play();

            WindowPlugin* w = static_cast<WindowPlugin*>(libWindow->getLibInstance(&engine));

            libInput->getLibInstance(&engine);
            engine.input().setPlugin(libInput);
            engine.input().discoverDevices();
            engine.input().listDevices(engine.log().log());

            libRender->getLibInstance(&engine);
            engine.render().setPlugin(libRender);

            w->setResolution(1280, 720);
            w->setResolution(640, 480);
            w->setResolution(100, 100);

            ShaderProgramPtr prog = res().createFromFile<ShaderProgram>("effect1.prog");
            if (prog)
                prog->bind();

            VAOPtr v = res().create<VAO>("vao");
            if (v)
                v->bind();

            ShaderProgramPtr prog2 = res().createFromFile<ShaderProgram>("effect1.prog");

            TexturePtr tex = res().createFromFile<Texture>("data/images/im.jpg");

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
                // process input events
                engine.input().update();
                // process window events
                w->update();
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

                if (v)
                    v->bind();

                if (prog)
                {
                    prog->bind();
                    prog2->setUniform1f(0u, gameTimer.getTime()/1000.0);
                    if (tex)
                        prog2->setUniform1i("tex", tex->getTextureId());
                }
                render().impl()->draw();
                w->swapBuffers();

                double frameTime = frameTimer.getTime();
                //engine.log().log() << "frame time: " << frameTime << std::endl;
                //engine.log().log() << "potential fps: " << 1000.0/frameTime << std::endl;

                ++fps;
                if (frameTime < targetFrameTime)
                {
                    //engine.log().log() << "wait: " << targetFrameTime - frameTime << std::endl;
                    Timer::wait(targetFrameTime - frameTime);
                    timeSlept += targetFrameTime - frameTime;
                }
                else
                {
                    engine.log().log() << "frame time over " << targetFrameTime << " ms : " << frameTime << std::endl;
                }

                if (timer.getTime() >= 1000)
                {
                    engine.log().log() << "fps: " << fps << " (" << timeSlept * 0.1 << "% idle)" << std::endl;
                    fps = 0;
                    timeSlept = 0.0;
                    timer.reset();
                    prog->reload();
                }
            }
            log().log() << res() << "\n";
        }
    }

    log().log() << res() << "\n";

    log().log() << "sizeof(Resource): " << sizeof(Resource) << "\n";
    log().log() << "sizeof(ResourceFile): " << sizeof(ResourceFile) << "\n";
    log().log() << "sizeof(ResourcePtr): " << sizeof(ResourcePtr) << "\n";
    log().log() << "sizeof(std::string): " << sizeof(std::string) << "\n";
    log().log() << "sizeof(std::vector<int>): " << sizeof(std::vector<int>) << "\n";
    log().log() << "sizeof(std::vector<int*>): " << sizeof(std::vector<int*>) << "\n";
    log().log() << "sizeof(std::vector<ResourceFile>): " << sizeof(std::vector<ResourceFile>) << "\n";
    log().log() << "sizeof(float): " << sizeof(float) << "\n";
    log().log() << "sizeof(double): " << sizeof(double) << "\n";
    log().log() << "sizeof(Vec2ui): " << sizeof(Vec2ui) << "\n";
    log().log() << "sizeof(Vec4f): " << sizeof(Vec4f) << "\n";

    log().log() << "main exit..." << std::endl;

    return 0;
}
