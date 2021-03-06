////////////////////////////////////////////////////////////////////////////////
#include "shaderGL.hpp"
#include "core/resource/resourceManager.hpp"
#include "core/log/logManager.hpp"
#include "opengltools.hpp"
#include <GL/glew.h>
////////////////////////////////////////////////////////////////////////////////
ShaderGL::ShaderTypeMapping ShaderGL::m_shaderTypeMapping;
////////////////////////////////////////////////////////////////////////////////
ShaderGL::ShaderTypeMapping::ShaderTypeMapping()
{
    m_mapping[Type::VERTEX_SHADER] = GL_VERTEX_SHADER;
    m_mapping[Type::TESS_CONTROL_SHADER] = GL_TESS_CONTROL_SHADER;
    m_mapping[Type::TESS_EVALUATION_SHADER] = GL_TESS_EVALUATION_SHADER;
    m_mapping[Type::GEOMETRY_SHADER] = GL_GEOMETRY_SHADER;
    m_mapping[Type::FRAGMENT_SHADER] = GL_FRAGMENT_SHADER;
    m_mapping[Type::COMPUTE_SHADER] = GL_COMPUTE_SHADER;
}
////////////////////////////////////////////////////////////////////////////////
uint32_t ShaderGL::ShaderTypeMapping::get(Type t)
{
    return m_mapping[t];
}
////////////////////////////////////////////////////////////////////////////////
ShaderGL::ShaderGL(const std::string& name, const std::string& fileName, Type t)
: super(name, fileName, t)
{
    //m_shaderId = glCreateShader(m_shaderTypeMapping.get(t));
    //loadSource();
    //compile();
}
////////////////////////////////////////////////////////////////////////////////
ShaderGL::~ShaderGL()
{
    glDeleteShader(m_shaderId);

    if (isEnginemanaged())
    {
        log().log() << __FUNCTION__ << ": " << *this << std::endl;
        res().delResource(this);
    }
}
////////////////////////////////////////////////////////////////////////////////
ShaderPtr ShaderGL::create(const std::string& name, const std::string& fileName, Type t)
{
    return std::make_shared<ShaderGL>(name, fileName, t);
}
////////////////////////////////////////////////////////////////////////////////
ShaderPtr ShaderGL::createFromSource(const std::string& name, Type t, const std::string& src)
{
    return nullptr;
}
////////////////////////////////////////////////////////////////////////////////
bool ShaderGL::compile()
{
    if (m_isCompiled)
        return true;

    if (m_compileError)
        return false;

    if (m_shaderId == 0)
    {
        m_shaderId = glCreateShader(m_shaderTypeMapping.get(m_type));
        loadSource();
    }

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
void ShaderGL::loadSource()
{
    std::ifstream ifs(getFileName());
    std::string str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
    loadSourceFromBuf(str);
}
////////////////////////////////////////////////////////////////////////////////
void ShaderGL::loadSourceFromBuf(const std::string& source)
{
    GLint len = source.size();
    const GLchar* src = source.c_str();
    glShaderSource(m_shaderId, 1, &src, &len);
}
////////////////////////////////////////////////////////////////////////////////
bool ShaderGL::reload()
{
    uint32_t oldmTime = m_mtime;
    updateMtime();
    if (m_mtime > oldmTime)
    {
        log().log() << "Reload: " << *this << "\n";

        m_isCompiled = false;
        m_compileError = false;

        loadSource();
        compile();
        return true;
    }
    return false;
}
////////////////////////////////////////////////////////////////////////////////
void ShaderGL::printOn(Logger& o) const
{
    o << "ShaderGL " << m_shaderId << " " << Shader::getShaderTypeString(m_type) << " " << getName();
}
////////////////////////////////////////////////////////////////////////////////
