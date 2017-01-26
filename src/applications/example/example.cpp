////////////////////////////////////////////////////////////////////////////////
#include "example.hpp"
#include "core/plugin/plugin.hpp"
#include "core/log/logManager.hpp"
#include "core/engine.hpp"
#include "core/windowContext/windowPlugin.hpp"
#include "core/tools/timer.hpp"
#include "core/scene/scene.hpp"
#include "core/render/renderPlugin.hpp"
#include <functional>
#include "core/script/lua/engineLua.hpp"
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
    {
        {
            //SoundPtr sound = res().createFromFile<Sound>("data/sound/test.ogg");
            //SoundSourcePtr s = res().createFromFile<SoundSource>("data/sound/test.ogg");
            //sound->play();
            //audio().play(sound, );
            //s->position(0,0,0);
            //s->velocity(1,0,0);
            //s->volume(0.75);
            //s->play();

            input().discoverDevices();
            input().listDevices(log().log());

            //input().setWindowInputFocus(w->getWindowId());

            auto func = std::bind(&RenderPlugin::resize, render().impl(), std::placeholders::_1, std::placeholders::_2);
            window().getWindow()->setEventResizeCallback(func);

            ShaderProgramPtr prog = res().createFromFile<ShaderProgram>("effect1.prog");
            if (prog)
                prog->bind();

            ShaderProgramPtr prog2 = res().createFromFile<ShaderProgram>("effect1.prog");
            ShaderProgramPtr prog3 = res().createFromFile<ShaderProgram>("drawtri.prog");
            ShaderProgramPtr prog4 = res().createFromFile<ShaderProgram>("normal.prog");

            TexturePtr tex = res().createFromFile<Texture>("data/images/car1.tiff");
            TexturePtr tex1 = res().createFromFile<Texture>("data/images/im.tif");

            //ImagePtr im = res().createFromFile<Image>("data/images/im.dds");

            //MeshPtr mesh = res().createFromFile<Mesh>("data/mesh/untitled.stl");
            //MeshPtr mesh = res().createFromFile<Mesh>("data/mesh/untitled2.stl");
            //MeshPtr mesh = res().createFromFile<Mesh>("data/mesh/untitled.obj");
            MeshPtr mesh = res().createFromFile<Mesh>("data/mesh/car.obj");
            if (mesh)
            {
                mesh->save("test2.stl");
                mesh->save("test.obj");
            }

            Scene scene;
            if (mesh)
                scene.add(mesh.get());

            bool stop = false;
            window().getWindow()->setEventCloseCallback([&stop](){ stop = true; });

            double targetFrameTime = 1000.0 / 60.0;
            double timeSlept = 0.0;
            Timer timer;
            timer.start();
            int fps = 0;
            Timer frameTimer;

            Timer gameTimer;
            gameTimer.start();
            Vec2i mouseCoords;
            while (!stop)
            {
                frameTimer.reset();
                // process window events
                window().getWindow()->update();
                // process input events
                input().update();
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
                    (input().mouse(0)->isPressed(Input::Mouse::BT_1) ||
                     input().mouse(0)->isPressed(Input::Mouse::BT_2) ||
                     input().mouse(0)->isPressed(Input::Mouse::BT_3)))
                {
                    stop = true;
                }

                if (input().mouse(0) &&
                    input().mouse(0)->isMotion(mouseCoords))
                {
                    log().log() << mouseCoords << std::endl;
                }

                if (input().mouse(0) &&
                    input().mouse(0)->isPressed(Input::Mouse::BT_WHEEL_UP))
                {
                    log().log() << "wheel up" << std::endl;
                }
                if (input().mouse(0) &&
                    input().mouse(0)->isPressed(Input::Mouse::BT_WHEEL_DOWN))
                {
                    log().log() << "wheel down" << std::endl;
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

                Mat4f mv = Mat4f::identity();
                mv *= Mat4f::scale(Vec3f(0.4f, 0.4f, 0.4f));
                //mv *= Mat4f::translate(Vec3f(mouseCoords.x/50.0f, -mouseCoords.y/50.0f, 0.0f));
                mv *= Mat4f::rotate(gameTimer.getTime()/10.0f/5, Vec3f(0.0f, 1.0f, 0.0f));
                mv *= Mat4f::rotate(1 + gameTimer.getTime()/8.0f/5, Vec3f(1.0f, 0.0f, 0.0f));
                mv *= Mat4f::rotate(2 + gameTimer.getTime()/6.0f/5, Vec3f(0.0f, 0.0f, 1.0f));//*/

                render().impl()->clear();
                /*/
                if (prog)
                {
                    prog->bind();
                    prog2->setUniform1f(0u, gameTimer.getTime()/1000.0);
                    if (tex)
                        prog2->setUniform1i("tex", 0);
                }
                render().impl()->draw();//*/
                if (prog3)
                {
                    prog3->bind();
                    prog3->setUniformMat4f("mv", mv);
                    if (tex)
                        tex->bind(0);
                    prog3->setUniform1i("tex", 0);
                }
                render().impl()->drawScene(&scene);
                if (prog4)
                {
                    prog4->bind();
                    prog4->setUniformMat4f(0u, mv);
                    render().impl()->drawScene(&scene);
                }

                window().getWindow()->swapBuffers();

                double frameTime = frameTimer.getTime();
                //log().log() << "frame time: " << frameTime << std::endl;
                //log().log() << "potential fps: " << 1000.0/frameTime << std::endl;

                ++fps;
                if (frameTime < targetFrameTime)
                {
                    //log().log() << "wait: " << targetFrameTime - frameTime << std::endl;
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
                    if (prog3)
                        prog3->reload();
                    if (prog4)
                        prog4->reload();
                    if (tex)
                        tex->reload();
                }

                if (getEngine().getRequestQuit())
                    stop = true;
            }
            //log().log() << res() << "\n";
        }
        threads().joinAll();
    }

    //log().log() << res() << "\n";

    /*log().log() << "sizeof(Resource): " << sizeof(Resource) << "\n";
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
    log().log() << "sizeof(bool): " << sizeof(bool) << "\n";*/

    luaTest();

    log().log() << getEngine().config();
}
////////////////////////////////////////////////////////////////////////////////
