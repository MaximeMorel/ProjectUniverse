////////////////////////////////////////////////////////////////////////////////
#include "example.hpp"
#include "core/plugin/plugin.hpp"
#include "core/log/logManager.hpp"
#include "core/engine.hpp"
#include "core/windowContext/windowPlugin.hpp"
#include "core/tools/timer.hpp"
////////////////////////////////////////////////////////////////////////////////
PluginInfo pluginInfo = { "example",
                          "example",
                          "app",
                          0,
                          1};
////////////////////////////////////////////////////////////////////////////////
ApplicationExample* app = nullptr;
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
        app = new ApplicationExample(*engine);
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
ApplicationExample::ApplicationExample(Engine& engine)
    : Application(engine)
{
    log().log() << "ApplicationExample start...\n";
}
////////////////////////////////////////////////////////////////////////////////
ApplicationExample::~ApplicationExample()
{
    log().log() << "ApplicationExample stop...\n";
}
////////////////////////////////////////////////////////////////////////////////
void ApplicationExample::run()
{
    ImagePtr image;
    PluginLibPtr libJPEG = res().createFromFile<PluginLib>("libImageCodecJPEG.so");
    if (libJPEG && libJPEG->isValid())
    {
        log().log() << libJPEG << "\n";
        libJPEG->getLibInstance(&getEngine());

        ImagePtr im = res().createFromFile<Image>("data/images/im.jpg");
        if (im)
            im->save("im_copy.jpg");
        image = im;
    }

    PluginLibPtr libPNG = res().createFromFile<PluginLib>("libImageCodecPNG.so");
    if (libPNG && libPNG->isValid())
    {
        log().log() << libPNG << "\n";
        libPNG->getLibInstance(&getEngine());

        ImagePtr im = res().createFromFile<Image>("data/images/im2.png");
        if (im)
            im->save("im2_copy.png");
        image = im;
    }

    PluginLibPtr lib = res().createFromFile<PluginLib>("libImageCodecSDL.so");
    if (lib && lib->isValid())
    {
        log().log() << lib << "\n";
        lib->getLibInstance(&getEngine());

        ImagePtr im = res().createFromFile<Image>("data/images/im.jpg");
        if (im)
            im->save("a.png");
        image = im;
    }
    //lib = nullptr;

    PluginLibPtr libM1 = res().createFromFile<PluginLib>("libMeshCodecCustom.so");
    if (libM1 && libM1->isValid())
    {
        log().log() << libM1 << "\n";
        libM1->getLibInstance(&getEngine());

        MeshPtr im = res().createFromFile<Mesh>("data/mesh/untitled.stl");
    }

    {
        PluginLibPtr libWindow = res().createFromFile<PluginLib>("libwindowContextSDL2.so");
        PluginLibPtr libRender = res().createFromFile<PluginLib>("libRenderOpenGL4.so");
        PluginLibPtr libInput = res().createFromFile<PluginLib>("libInputSDL.so");
        PluginLibPtr libAudio = res().createFromFile<PluginLib>("libAudioOpenAL.so");
        if (libAudio && libAudio->isValid())
        {
            log().log() << libAudio << "\n";
            libAudio->getLibInstance(&getEngine());
        }
        if (libWindow && libRender && libInput &&
            libWindow->isValid() && libRender->isValid() && libInput->isValid())
        {
            log().log() << libWindow << "\n";
            log().log() << libRender << "\n";
            log().log() << libInput << "\n";

            //SoundPtr sound = res().createFromFile<Sound>("data/sound/test.ogg");
            //SoundSourcePtr s = res().createFromFile<SoundSource>("data/sound/test.ogg");
            //sound->play();
            //audio().play(sound, );
            //s->position(0,0,0);
            //s->velocity(1,0,0);
            //s->volume(0.75);
            //s->play();

            WindowPlugin* w = static_cast<WindowPlugin*>(libWindow->getLibInstance(&getEngine()));

            libInput->getLibInstance(&getEngine());
            input().setPlugin(libInput);
            input().discoverDevices();
            input().listDevices(log().log());

            libRender->getLibInstance(&getEngine());
            render().setPlugin(libRender);

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

            TexturePtr tex = res().createFromFile<Texture>("data/images/im4.png");

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
                input().update();
                // process window events
                w->update();
                if (input().keyboard(0) &&
                    input().keyboard(0)->isPressed(Input::Keyboard::KEY_a))
                {
                    ;
                }

                if (input().keyboard(0) &&
                    input().keyboard(0)->isPressed(Input::Keyboard::KEY_ESC))
                {
                    stop = true;
                }

                if (input().mouse(0) &&
                    input().mouse(0)->isPressed(Input::Mouse::BT_1))
                {
                    ;
                }

                if (input().joystick(0) &&
                    input().joystick(0)->isPressed(Input::Joystick::BT_1))
                {
                    ;
                }

                if (input().joystick(0) &&
                    input().joystick(0)->value(Input::Joystick::AXIS_1) > 0.5)
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
                    log().log() << "frame time over " << targetFrameTime << " ms : " << frameTime << std::endl;
                }

                if (timer.getTime() >= 1000)
                {
                    log().log() << "fps: " << fps << " (" << timeSlept * 0.1 << "% idle)" << std::endl;
                    fps = 0;
                    timeSlept = 0.0;
                    timer.reset();
                    if (prog)
                        prog->reload();
                    if (tex)
                        tex->reload();
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
    log().log() << "sizeof(bool): " << sizeof(bool) << "\n";

    log().log() << "main exit..." << std::endl;
}
////////////////////////////////////////////////////////////////////////////////
