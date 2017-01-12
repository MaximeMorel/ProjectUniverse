#ifndef __MESHCODEC_HPP__
#define __MESHCODEC_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/library.hpp"
#include "core/codecs/codec.hpp"
#include "core/geom/mesh/mesh.hpp"
////////////////////////////////////////////////////////////////////////////////
class MeshCodec : public Codec
{
public:
    MeshCodec(Engine& engine);
    ~MeshCodec() override;

    virtual bool load(Mesh* mesh);
    virtual bool save(Mesh* mesh, const std::string& filePath);
};
////////////////////////////////////////////////////////////////////////////////
#endif // __MESHCODEC_HPP__
