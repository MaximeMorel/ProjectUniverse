////////////////////////////////////////////////////////////////////////////////
#include "shaderProgram.hpp"
#include "renderManager.hpp"
#include "renderPlugin.hpp"
#include "core/resource/resourceManager.hpp"
#include <fstream>
#include <algorithm>
////////////////////////////////////////////////////////////////////////////////
ResourceType ShaderProgram::type("ShaderProgram");
////////////////////////////////////////////////////////////////////////////////
ShaderProgram::ShaderProgram(const std::string& name, const std::string& fileName)
    : super(name, fileName)
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
    return render().impl()->getShaderSearchPath();
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
void ShaderProgram::removeShader(ShaderPtr shader)
{
}
////////////////////////////////////////////////////////////////////////////////
bool ShaderProgram::link()
{
    return false;
}
////////////////////////////////////////////////////////////////////////////////
void ShaderProgram::setUniform1f(uint32_t id, float v0)
{
}
////////////////////////////////////////////////////////////////////////////////
void ShaderProgram::setUniform1f(const char* str, float v0)
{
}
////////////////////////////////////////////////////////////////////////////////
void ShaderProgram::setUniform2f(uint32_t id, float v0, float v1)
{
}
////////////////////////////////////////////////////////////////////////////////
void ShaderProgram::setUniform2f(const char* str, float v0, float v1)
{
}
////////////////////////////////////////////////////////////
void ShaderProgram::setUniform1i(uint32_t id, int32_t v0)
{
}
////////////////////////////////////////////////////////////////////////////////
void ShaderProgram::setUniform1i(const char* str, int32_t v0)
{
}
////////////////////////////////////////////////////////////////////////////////
void ShaderProgram::setUniformMat4f(uint32_t id, const Mat4f& m)
{
}
////////////////////////////////////////////////////////////////////////////////
void ShaderProgram::setUniformMat4f(const char* str, const Mat4f& m)
{
}
////////////////////////////////////////////////////////////////////////////////
bool ShaderProgram::reload()
{
    // parse again .prog file, and add/remove shaders if needed
    uint32_t oldmTime = m_mtime;
    updateMtime();
    if (m_mtime > oldmTime)
    {
        std::ifstream file(getFileName());
        std::string line;
        std::vector<std::string> lines;
        while (file.good())
        {
            std::getline(file, line);
            if (line[0] == '#' || line[0] == '\n' || line.length() < 4)
                continue;

            lines.push_back(line);
        }
        bool outDated = false;
        // remove
        for (ShaderPtr shader : m_shaders)
        {
            auto it = std::find(lines.begin(), lines.end(), shader->getName());
            if (it == lines.end())
            {
                // shader not there anymore, remove
                removeShader(shader);
                outDated = true;
            }
            else
            {
                // was already there
                lines.erase(it);
            }
        }

        // add
        for (const auto& str : lines)
        {
            bool missing = true;
            for (ShaderPtr shader : m_shaders)
            {
                if (shader->getName() == str)
                    missing = false;
            }
            if (missing)
            {
                outDated = true;
                ShaderPtr s = res().createFromFile<Shader>(str);
                if (s)
                    addShader(s);
            }
        }
        return outDated;
    }
    return false;
}
////////////////////////////////////////////////////////////////////////////////
void ShaderProgram::printOn(Logger& o) const
{
    o << "ShaderProgram " << m_shaderProgId << " " << getName();
}
////////////////////////////////////////////////////////////////////////////////
