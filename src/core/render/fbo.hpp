#ifndef __FBO_HPP__
#define __FBO_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/resource/resource.hpp"
#include "core/render/texture.hpp"
#include "core/math/vec2.hpp"
#include "core/engine_export.h"
#include <vector>
////////////////////////////////////////////////////////////////////////////////
template class ENGINE_EXPORT std::vector<TexturePtr>;
////////////////////////////////////////////////////////////////////////////////
class FBO;
using FBOPtr = std::shared_ptr<FBO>;
////////////////////////////////////////////////////////////////////////////////
class ENGINE_EXPORT FBO : public Resource
{
public:
    FBO(const std::string& name);
    virtual ~FBO() override;

    static FBOPtr create(const std::string& name);

    Vec2ui getResolution() const;

    virtual void resize(uint32_t x, uint32_t y);

    virtual void attach(TexturePtr tex, uint32_t attachement);
    virtual void attachDepth(TexturePtr tex);

    virtual void bind();
    virtual void unbind();

protected:
    Vec2ui m_resolution;
    std::vector<TexturePtr> m_textures;
    TexturePtr m_depthTexture;

public:
    virtual ResourceType& dyntype() override { return type; }
    virtual const ResourceType& dyntype() const override { return type; }
    static ResourceType type;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __FBO_HPP__
