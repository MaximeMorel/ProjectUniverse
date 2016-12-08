////////////////////////////////////////////////////////////////////////////////
#include "shaderProgram.hpp"
#include "renderManager.hpp"
#include "renderPlugin.hpp"
#include "core/resource/resourceManager.hpp"
#include <fstream>
////////////////////////////////////////////////////////////////////////////////
ResourceType ShaderProgram::type("ShaderProgram");
////////////////////////////////////////////////////////////////////////////////
ShaderProgram::ShaderProgram(const std::string& name, const std::string& fileName)
    : Resource(name)
    , m_isLinked(false)
    , m_linkError(false)
{
}
////////////////////////////////////////////////////////////////////////////////
ShaderProgram::~ShaderProgram()
{
}
////////////////////////////////////////////////////////////////////////////////
const char* ShaderProgram::getSearchPath()
{
    return render().impl()->getSearchPath();
}
////////////////////////////////////////////////////////////////////////////////
ShaderProgramPtr ShaderProgram::create(const std::string& name, const std::string& fileName)
{
    // parse name file (ex: effect1.prog, using data path and plugin path),
    // ex: data/shaders/opengl4/effect1.prog
    // containing something like:
    // effect1.vs
    // effect1.gs
    // effect1.ps
    // create shader resource for each line
    //ShaderPtr s = render().impl()->createShader(name, type);

    /// virtual constructor idiom, use create facility from render plugin
    ShaderProgramPtr prog = render().impl()->createShaderProgram(name, fileName);
    if (!prog)
    {
        // log error
        return nullptr;
    }
    // parse shader program file, each line contains the name of a shader file to add
    std::ifstream file(fileName);
    std::string line;
    while (file.good())
    {
        std::getline(file, line);
        if (line[0] == '#' || line[0] == '\n' || line.length() < 4)
            continue;

        ShaderPtr s = res().createFromFile<Shader>(line);
        if (s)
            prog->addShader(s);
    }
    return prog;
}
////////////////////////////////////////////////////////////////////////////////
uint32_t ShaderProgram::getProgId() const
{
    return m_shaderProgId;
}
////////////////////////////////////////////////////////////////////////////////
void ShaderProgram::bind()
{

}
////////////////////////////////////////////////////////////////////////////////
void ShaderProgram::unbind()
{

}
////////////////////////////////////////////////////////////////////////////////
void ShaderProgram::addShader(ShaderPtr shader)
{

}
////////////////////////////////////////////////////////////////////////////////
bool ShaderProgram::link()
{
    return false;
}
////////////////////////////////////////////////////////////////////////////////
void ShaderProgram::printOn(Logger& o) const
{

}
////////////////////////////////////////////////////////////////////////////////
