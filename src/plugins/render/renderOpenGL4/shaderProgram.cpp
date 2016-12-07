////////////////////////////////////////////////////////////////////////////////
#include "shaderProgram.hpp"
#include "core/log/logManager.hpp"
#include <GL/glew.h>
////////////////////////////////////////////////////////////////////////////////
ShaderProgramGL4::ShaderProgramGL4(const std::string& name, const std::string& fileName)
    : ShaderProgram(name, fileName)
{
    m_shaderProgId = glCreateProgram();
}
////////////////////////////////////////////////////////////////////////////////
ShaderProgramGL4::~ShaderProgramGL4()
{
    // attached shaders are automatically detached
    glDeleteProgram(m_shaderProgId);
}
////////////////////////////////////////////////////////////////////////////////
ShaderProgramPtr ShaderProgramGL4::create(const std::string& name, const std::string& fileName)
{
    struct MakeSharedEnabler : public ShaderProgramGL4
    {
        MakeSharedEnabler(const std::string& name, const std::string& fileName)
            : ShaderProgramGL4(name, fileName) {}
    };
    // check cache
    return std::make_shared<MakeSharedEnabler>(name, fileName);
}
////////////////////////////////////////////////////////////////////////////////
void ShaderProgramGL4::bind()
{
    if (!m_isLinked && !m_linkError)
        link();

    glUseProgram(m_shaderProgId);
}
////////////////////////////////////////////////////////////////////////////////
void ShaderProgramGL4::unbind()
{
    glUseProgram(0);
}
////////////////////////////////////////////////////////////////////////////////
void ShaderProgramGL4::addShader(ShaderPtr shader)
{
    GLenum err = glGetError();
    while (err != GL_NO_ERROR)
        err = glGetError();
    glAttachShader(m_shaderProgId, shader->getShaderId());
    err = glGetError();
    if (err == GL_NO_ERROR)
        m_shaders.push_back(shader);
    else
        log().log() << "addShader fail: " << err << "\n";
}
////////////////////////////////////////////////////////////////////////////////
bool ShaderProgramGL4::link()
{
    if (m_isLinked)
        return true;

    if (m_linkError)
        return false;

    // check shaders are compiled
    bool allCompiled = true;
    for (ShaderPtr shader : m_shaders)
    {
        bool compiled = shader->compile();
        if (!compiled)
            allCompiled = false;
    }

    glLinkProgram(m_shaderProgId);

    GLint status = GL_FALSE;
    glGetProgramiv(m_shaderProgId, GL_LINK_STATUS, &status);
    if(status == GL_FALSE)
    {
        m_isLinked = false;
        log().log() << "Shader program " << m_shaderProgId << " link failed.\n";
        GLsizei logLength = 0;
        glGetProgramiv(m_shaderProgId, GL_INFO_LOG_LENGTH, &logLength);
        if(logLength > 0)
        {
            m_linkError = true;
            GLsizei charsWritten = 0;
            std::string infoLog(logLength, 0);
            glGetProgramInfoLog(m_shaderProgId, logLength, &charsWritten, &infoLog.front());
            if (charsWritten < logLength)
                infoLog.resize(charsWritten);
            log().log() << "Shader program log: " << infoLog.substr(0, charsWritten) << "\n";
        }
    }
    else
    {
        m_isLinked = true;
        m_linkError = false;
        log().log() << "Shader program " << m_shaderProgId << " link success.\n";
    }

    return true;
}
////////////////////////////////////////////////////////////////////////////////
void ShaderProgramGL4::printOn(Logger& o) const
{

}
////////////////////////////////////////////////////////////////////////////////
