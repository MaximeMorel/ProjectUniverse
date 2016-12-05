////////////////////////////////////////////////////////////////////////////////
#include "shaderProgram.hpp"
#include "core/log/logManager.hpp"
#include <GL/glew.h>
////////////////////////////////////////////////////////////////////////////////
ShaderProgramGL4::ShaderProgramGL4(const std::string& name, std::initializer_list<ShaderPtr> shaders)
    : ShaderProgram(name, shaders)
{
    m_shaderProgId = glCreateProgram();

    // add shaders passed as params if any
    for (ShaderPtr shader : shaders)
    {
        addShader(shader);
    }

    // compile and link if we have shaders
    if (shaders.size())
    {
        link();
    }
}
////////////////////////////////////////////////////////////////////////////////
ShaderProgramGL4::~ShaderProgramGL4()
{
    // attached shaders are automatically detached
    glDeleteProgram(m_shaderProgId);
}
////////////////////////////////////////////////////////////////////////////////
ShaderProgramPtr ShaderProgramGL4::create(const std::string& name, std::initializer_list<ShaderPtr> shaders)
{
    // check cache
    return std::shared_ptr<ShaderProgramGL4>(new ShaderProgramGL4(name, shaders));
}
////////////////////////////////////////////////////////////////////////////////
void ShaderProgramGL4::bind() const
{
    glUseProgram(m_shaderProgId);
}
////////////////////////////////////////////////////////////////////////////////
void ShaderProgramGL4::unbind() const
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
            std::string infoLog;
            infoLog.resize(logLength);
            glGetProgramInfoLog(m_shaderProgId, logLength, &charsWritten, &infoLog.front());
            if (charsWritten < logLength)
                infoLog = infoLog.substr(0, charsWritten);
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
