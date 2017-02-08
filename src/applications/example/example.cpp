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
PluginInfo pluginInfo = { "Example",
                          "Example",
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
            //ImagePtr im = res().createFromFile<Image>("data/images/im.png");
            //im->save("im.png");

            //SoundPtr sound = res().createFromFile<Sound>("data/sound/test.ogg");
            //SoundSourcePtr s = res().createFromFile<SoundSource>("data/sound/test.ogg");
            //sound->play();
            //audio().play(sound, );
            //s->position(0,0,0);
            //s->velocity(1,0,0);
            //s->volume(0.75);
            //s->play();

            //input().discoverDevices(); // done in engine
            //input().listDevices(log().log());

            //input().setWindowInputFocus(w->getWindowId());

            auto func = std::bind(&RenderPlugin::resize, render().impl(), std::placeholders::_1, std::placeholders::_2);
            window().getWindow()->setEventResizeCallback(func);

            ShaderProgramPtr prog = res().createFromFile<ShaderProgram>("effect1.prog");
            if (prog)
                prog->bind();

            ShaderProgramPtr prog2 = res().createFromFile<ShaderProgram>("effect1.prog");
            ShaderProgramPtr prog3 = res().createFromFile<ShaderProgram>("drawtri.prog");
            ShaderProgramPtr prog4 = res().createFromFile<ShaderProgram>("normal.prog");
            ShaderProgramPtr prog5 = res().createFromFile<ShaderProgram>("blob.prog");

            //TexturePtr tex2 = res().createFromFile<Texture>("data/images/car1.tiff");
            //TexturePtr tex1 = res().createFromFile<Texture>("data/images/im.tif");
            TexturePtr tex = res().createFromFile<Texture>("data/images/im.png");

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

            FBOPtr fbo = res().create<FBO>("fbo");
            TexturePtr texfbo = res().create<Texture>("texfbo");
            TexturePtr texfboDepth = res().create<Texture>("texfbodepth");
            if (fbo && texfbo &&  texfboDepth)
            {
                texfboDepth->makeDepth(0, 0);
                fbo->attach(texfbo, 0);
                fbo->attachDepth(texfboDepth);
                fbo->resize(512, 512);
            }

            Scene scene;
            if (mesh)
                scene.add(mesh.get());

            bool stop = false;
            window().getWindow()->setEventCloseCallback([&stop](){ stop = true; });

            std::chrono::microseconds targetFrameTime(1000000 / 60);
            std::chrono::microseconds timeSlept = std::chrono::microseconds::zero();
            Timer timer;
            timer.start();
            int fps = 0;
            Timer frameTimer;

            Timer gameTimer;
            gameTimer.start();
            Vec2i mouseCoords;
            Mat4f proj = Mat4f::perspective(50, 1, 1, 100);
            //Mat4f proj = Mat4f::ortho(-2, 2, -2, 2, -1, 1);
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
                    //stop = true;
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
                mv *= Mat4f::translate(Vec3f(0, 0, -5.0f));
                mv *= Mat4f::rotate(gameTimer.getTime().count()*0.00001, Vec3f(0.0f, 1.0f, 0.0f));
                mv *= Mat4f::rotate(1 + gameTimer.getTime().count()*0.00002, Vec3f(1.0f, 0.0f, 0.0f));
                mv *= Mat4f::rotate(2 + gameTimer.getTime().count()*0.00004, Vec3f(0.0f, 0.0f, 1.0f));//*/

                Mat4f mvp = proj * mv;

                //fbo->bind();

                render().impl()->clear();
                /*/
                if (prog)
                {
                    prog->bind();
                    prog2->setUniform1f(0u, gameTimer.getTime().count()*0.00001);
                    if (tex)
                        prog2->setUniform1i("tex", 0);
                }
                render().impl()->draw();//*/
                if (prog3)
                {
                    prog3->bind();
                    prog3->setUniformMat4f("mv", mv);
                    prog3->setUniformMat4f("mvp", mvp);
                    if (tex)
                        tex->bind(0);
                    prog3->setUniform1i("tex", 0);
                }
                render().impl()->drawScene(&scene);
                if (prog4)
                {
                    prog4->bind();
                    prog4->setUniformMat4f(0u, mv);
                    prog4->setUniformMat4f(1u, mvp);
                    render().impl()->drawScene(&scene);
                }
                prog5 = nullptr;
                if (prog5)
                {
                    Vec2i resolution = config().resolution->get();
                    render().impl()->clear();
                    prog5->bind();
                    prog5->setUniform1f(0u, gameTimer.getTime().count() * 0.000001);
                    prog5->setUniform2f(1u, resolution.x, resolution.y);
                    prog5->setUniform2f(2u, mouseCoords.x, mouseCoords.y);
                    render().impl()->draw();
                }

                window().getWindow()->swapBuffers();

                std::chrono::microseconds frameTime = frameTimer.getTime();
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
                    log().log() << "frame time over " << targetFrameTime.count() * 0.001 << " ms : " << frameTime.count() * 0.001 << std::endl;
                }

                if (timer.getTime().count() >= 1000000)
                {
                    log().log() << "fps: " << fps << " (" << timeSlept.count() * 0.0001 << "% idle)" << std::endl;
                    log().log() << render().impl()->getStats();
                    fps = 0;
                    timeSlept = std::chrono::microseconds::zero();
                    timer.reset();
                    if (prog)
                        prog->reload();
                    if (prog3)
                        prog3->reload();
                    if (prog4)
                        prog4->reload();
                    if (prog5)
                        prog5->reload();
                    if (tex)
                        tex->reload();
                }

                if (getEngine().getRequestQuit())
                    stop = true;
            }
            //log().log() << res() << "\n";
        }
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

    log().log() << getEngine().config();
}
////////////////////////////////////////////////////////////////////////////////
