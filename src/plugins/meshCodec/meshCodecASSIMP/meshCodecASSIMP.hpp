#ifndef __MESHCODECASSIMP_HPP__
#define __MESHCODECASSIMP_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/plugin/iplugin.hpp"
#include "core/library.hpp"
#include "core/codecs/meshCodec.hpp"
#include "core/geom/mesh/mesh.hpp"
#include "meshcodecassimp_export.h"
////////////////////////////////////////////////////////////////////////////////
extern "C" MESHCODECASSIMP_EXPORT const PluginInfo* getPluginInfo();
////////////////////////////////////////////////////////////////////////////////
extern "C" MESHCODECASSIMP_EXPORT Library* getLibInstance(Engine* engine);
////////////////////////////////////////////////////////////////////////////////
extern "C" MESHCODECASSIMP_EXPORT void closeLibInstance();
////////////////////////////////////////////////////////////////////////////////
class PluginMeshCodecASSIMP : public MeshCodec
{
public:
    PluginMeshCodecASSIMP(Engine& engine);
    ~PluginMeshCodecASSIMP() override;

    virtual bool load(Mesh* mesh) override;
    virtual bool save(Mesh *mesh, const std::string& filePath) override;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __MESHCODECASSIMP_HPP__
