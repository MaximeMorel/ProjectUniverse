#ifndef __MESHCODEC_HPP__
#define __MESHCODEC_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/library.hpp"
#include "core/codecs/codec.hpp"
////////////////////////////////////////////////////////////////////////////////
class MeshCodec : public Codec
{
public:
    MeshCodec(Engine& engine);
    ~MeshCodec() override;

    /*virtual bool load(MeshPtr mesh);
    virtual bool load(Mesh* mesh);
    virtual bool save(MeshPtr mesh, const std::string& filePath);
    virtual bool save(Mesh* mesh, const std::string& filePath);*/
};
////////////////////////////////////////////////////////////////////////////////
#endif // __MESHCODEC_HPP__
