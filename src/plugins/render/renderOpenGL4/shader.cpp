////////////////////////////////////////////////////////////////////////////////
#include "shader.hpp"
#include "core/resource/resourceManager.hpp"
#include "core/log/logManager.hpp"
#include <GL/glew.h>
////////////////////////////////////////////////////////////////////////////////
ShaderGL4::ShaderTypeMapping ShaderGL4::m_shaderTypeMapping;
////////////////////////////////////////////////////////////////////////////////
ShaderGL4::ShaderTypeMapping::ShaderTypeMapping()
{
    m_mapping[Type::VERTEX_SHADER] = GL_VERTEX_SHADER;
    m_mapping[Type::TESS_CONTROL_SHADER] = GL_TESS_CONTROL_SHADER;
    m_mapping[Type::TESS_EVALUATION_SHADER] = GL_TESS_EVALUATION_SHADER;
    m_mapping[Type::GEOMETRY_SHADER] = GL_GEOMETRY_SHADER;
    m_mapping[Type::FRAGMENT_SHADER] = GL_FRAGMENT_SHADER;
    m_mapping[Type::COMPUTE_SHADER] = GL_COMPUTE_SHADER;
}
////////////////////////////////////////////////////////////////////////////////
uint32_t ShaderGL4::ShaderTypeMapping::get(Type t)
{
    return m_mapping[t];
}
////////////////////////////////////////////////////////////////////////////////
ShaderGL4::ShaderGL4(const std::string& name, const std::string& fileName, Type t)
: Shader(name, fileName, t)
{
    m_shaderId = glCreateShader(m_shaderTypeMapping.get(t));
    std::ifstream ifs(fileName);
    std::string str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
    GLint len = str.size();
    const GLchar* src = str.c_str();
    glShaderSource(m_shaderId, 1, &src, &len);
    compile();
}
////////////////////////////////////////////////////////////////////////////////
ShaderGL4::~ShaderGL4()
{
    glDeleteShader(m_shaderId);

    if (isEnginemanaged())
    {
        log().log() << __FUNCTION__ << ": " << *this << std::endl;
        res().delResource(getId(), getName());
    }
}
////////////////////////////////////////////////////////////////////////////////
ShaderPtr ShaderGL4::create(const std::string& name, const std::string& fileName, Type t)
{
    return std::make_shared<ShaderGL4>(name, fileName, t);
}
////////////////////////////////////////////////////////////////////////////////
ShaderPtr ShaderGL4::createFromSource(const std::string& name, Type t, const std::string& src)
{
    return nullptr;
}
////////////////////////////////////////////////////////////////////////////////
bool ShaderGL4::compile()
{
    if (m_isCompiled)
        return true;

    if (m_compileError)
        return false;

    glFlushErrors();
    glCompileShader(m_shaderId);
    glLogCurrentError();

    GLint status = GL_FALSE;
    glGetShaderiv(m_shaderId, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        m_isCompiled = false;
        log().log() << *this << " compile failed\n";
        GLsizei logLength = 0;
        glGetShaderiv(m_shaderId, GL_INFO_LOG_LENGTH, &logLength);
        if (logLength > 0)
        {
            m_compileError = true;
            GLsizei charsWritten = 0;
            std::string infoLog(logLength, 0);
            glGetShaderInfoLog(m_shaderId, logLength, &charsWritten, &infoLog.front());
            if (charsWritten < logLength)
                infoLog.resize(charsWritten);
            log().log() << "Shader log: " << infoLog << "\n";
        }
    }
    else
    {
        m_isCompiled = true;
        m_compileError = false;
        log().log() << *this << " compile success.\n";
    }

    return true;
}
////////////////////////////////////////////////////////////////////////////////
void ShaderGL4::printOn(Logger& o) const
{
    o << "ShaderGL4 " << m_shaderId << " " << Shader::getShaderTypeString(m_type) << " " << getName();
}
////////////////////////////////////////////////////////////////////////////////
