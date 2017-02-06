#ifndef __FBO_OPENGL_HPP__
#define __FBO_OPENGL_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/render/fbo.hpp"
#include "GL/glew.h"
////////////////////////////////////////////////////////////////////////////////
class FBOGL : public FBO
{
public:
    FBOGL(const std::string& name);
    virtual ~FBOGL() override;

    static FBOPtr create(const std::string& name);

    GLuint getFboId() const;

    virtual void resize(uint32_t x, uint32_t y) override;

    virtual void attach(TexturePtr tex, uint32_t attachement) override;
    virtual void attachDepth(TexturePtr tex) override;

    virtual void bind() override;
    virtual void unbind() override;

protected:
    GLuint m_fboId;

protected:
    virtual void printOn(Logger& o) const override;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __FBO_OPENGL_HPP__
