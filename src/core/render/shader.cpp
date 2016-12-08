////////////////////////////////////////////////////////////////////////////////
#include "shader.hpp"
#include "renderManager.hpp"
#include "renderPlugin.hpp"
////////////////////////////////////////////////////////////////////////////////
ResourceType Shader::type("Shader");
////////////////////////////////////////////////////////////////////////////////
Shader::Shader(const std::string& name, const std::string& fileName, Type t)
    : Resource(name)
    , m_shaderId(0)
    , m_type(t)
    , m_isCompiled(false)
    , m_compileError(false)
{
}
////////////////////////////////////////////////////////////////////////////////
Shader::~Shader()
{
}
////////////////////////////////////////////////////////////////////////////////
ShaderPtr Shader::create(const std::string& name, const std::string& fileName)
{
    Shader::Type type = Shader::Type::VERTEX_SHADER;
    size_t pos = fileName.rfind('.');
    if (pos == std::string::npos)
        return nullptr;

    std::string ext = fileName.substr(pos + 1);
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
    else
        return nullptr;

    /// virtual constructor idiom, use create facility from render plugin
    return render().impl()->createShader(name, fileName, type);
}
////////////////////////////////////////////////////////////////////////////////
const char* Shader::getSearchPath()
{
    return render().impl()->getSearchPath();
}
////////////////////////////////////////////////////////////////////////////////
bool Shader::compile()
{
    return false;
}
////////////////////////////////////////////////////////////////////////////////
bool Shader::isCompiled() const
{
    return m_isCompiled;
}
////////////////////////////////////////////////////////////////////////////////
uint32_t Shader::getShaderId() const
{
    return m_shaderId;
}
////////////////////////////////////////////////////////////////////////////////
const char* Shader::getShaderTypeString(Shader::Type type)
{
    switch (type)
    {
    case Shader::Type::VERTEX_SHADER:
        return "VERTEX_SHADER";
    case Shader::Type::TESS_CONTROL_SHADER:
        return "TESS_CONTROL_SHADER";
    case Shader::Type::TESS_EVALUATION_SHADER:
        return "TESS_EVALUATION_SHADER";
    case Shader::Type::GEOMETRY_SHADER:
        return "GEOMETRY_SHADER";
    case Shader::Type::FRAGMENT_SHADER:
        return "FRAGMENT_SHADER";
    case Shader::Type::COMPUTE_SHADER:
        return "COMPUTE_SHADER";
    }
    return "UNKNOWN_SHADER";
}
////////////////////////////////////////////////////////////////////////////////
void Shader::printOn(Logger& o) const
{

}
////////////////////////////////////////////////////////////////////////////////
