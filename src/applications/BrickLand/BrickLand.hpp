#ifndef __BRICKLAND_HPP__
#define __BRICKLAND_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/application.hpp"
#include "brickland_export.h"
////////////////////////////////////////////////////////////////////////////////
class ApplicationBrickLand : public Application
{
public:
    ApplicationBrickLand(Engine &engine);
    virtual ~ApplicationBrickLand() override;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __BRICKLAND_HPP__
