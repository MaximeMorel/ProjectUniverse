#ifndef __MESHCODECCUSTOM_HPP__
#define __MESHCODECCUSTOM_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/plugin/iplugin.hpp"
#include "core/library.hpp"
#include "core/codecs/meshCodec.hpp"
#include "core/geom/mesh/mesh.hpp"
#include "meshcodeccustom_export.h"
////////////////////////////////////////////////////////////////////////////////
extern "C" MESHCODECCUSTOM_EXPORT const PluginInfo* getPluginInfo();
////////////////////////////////////////////////////////////////////////////////
extern "C" MESHCODECCUSTOM_EXPORT Library* getLibInstance(Engine* engine);
////////////////////////////////////////////////////////////////////////////////
extern "C" MESHCODECCUSTOM_EXPORT void closeLibInstance();
////////////////////////////////////////////////////////////////////////////////
class PluginMeshCodecCustom : public MeshCodec
{
public:
    PluginMeshCodecCustom(Engine& engine);
    ~PluginMeshCodecCustom() override;

    virtual bool load(Mesh* mesh) override;
    virtual bool load(MeshPtr mesh) override;

private:
    bool loadStl(Mesh* mesh);
    bool loadStlText(Mesh* mesh);
    bool loadStlBinary(Mesh* mesh);
    bool loadObj(Mesh* mesh);
};
////////////////////////////////////////////////////////////////////////////////
#endif // __MESHCODECCUSTOM_HPP__
