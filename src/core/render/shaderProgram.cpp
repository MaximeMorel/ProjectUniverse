////////////////////////////////////////////////////////////////////////////////
#include "shaderProgram.hpp"
#include "renderManager.hpp"
#include "renderPlugin.hpp"
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
    // parse name file (ex: effect1.sp, using data path and plugin path),
    // ex: data/shaders/opengl4/effect1.sp
    // containing something like:
    // effect1.vs
    // effect1.gs
    // effect1.ps
    // create shader resource for each line
    //ShaderPtr s1 = render().impl()->createShader(name, type);

    /// virtual constructor idiom, use create facility from render plugin
    ShaderProgramPtr res = render().impl()->createShaderProgram(name, fileName);
    std::ifstream file(fileName);
    std::string dirname = fileName.substr(0, fileName.rfind('/') + 1);
    std::string line;
    while (file.good())
    {
        std::string line;
        std::getline(file, line);
        log().log() << "line: " << dirname << line << std::endl;
        Shader::Type type = Shader::Type::VERTEX_SHADER;
        std::string ext = line.substr(line.rfind('.') + 1);
        if (ext == "vs")
            type = Shader::Type::VERTEX_SHADER;
        else if (ext == "tcs")
            type = Shader::Type::TESS_CONTROL_SHADER;
        else if (ext == "tes")
            type = Shader::Type::TESS_EVALUATION_SHADER;
        else if (ext == "gs")
            type = Shader::Type::GEOMETRY_SHADER;
        else if (ext == "fs")
            type = Shader::Type::FRAGMENT_SHADER;
        else if (ext == "cs")
            type = Shader::Type::COMPUTE_SHADER;
        ShaderPtr s = render().impl()->createShader(line, dirname + line, type);
        res->addShader(s);
    }
    return res;
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
