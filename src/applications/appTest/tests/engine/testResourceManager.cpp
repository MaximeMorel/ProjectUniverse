////////////////////////////////////////////////////////////////////////////////
#include "testResourceManager.hpp"
#include "core/engine.hpp"
////////////////////////////////////////////////////////////////////////////////
void TestResourceManager::setUp()
{
    m_engine = &getEngine();
}
////////////////////////////////////////////////////////////////////////////////
void TestResourceManager::tearDown()
{
    setGlobalEngine(*m_engine);
}
////////////////////////////////////////////////////////////////////////////////
class DummyResource;
using DummyResourcePtr = std::shared_ptr<DummyResource>;
class DummyResource : public Resource
{
public:
    DummyResource(const std::string& name)
        : Resource(name)
    {
        id = sid++;
    }

    ~DummyResource()
    {
        getEngine().log().log() << "Dtor: " << *this << "\n";
    }

    static DummyResourcePtr create(const std::string& name)
    {
        return std::shared_ptr<DummyResource>(new DummyResource(name));
    }

    virtual size_t getMemSize() const
    {
        return sizeof(*this);
    }

protected:
    virtual void printOn(Logger& o) const
    {
        o << getName() << " - " << id;
    }

private:
    static int sid;
    int id = 0;
};
int DummyResource::sid = 0;
////////////////////////////////////////////////////////////////////////////////
void TestResourceManager::testResources()
{
    Engine engine("test");

    ResourcePtr a = engine.res().addResource(DummyResource::create("a"));
    ResourcePtr b = engine.res().addResource(DummyResource::create("b"));
    ResourcePtr c = engine.res().addResource(DummyResource::create("c"));
    ResourcePtr d = engine.res().addResource(DummyResource::create("d"));
    ResourcePtr e = engine.res().addResource(DummyResource::create("e"));
    ResourcePtr f = engine.res().addResource(DummyResource::create("f"));
    ResourcePtr g = engine.res().addResource(DummyResource::create("g"));
    ResourcePtr h = engine.res().addResource(DummyResource::create("h"));
    ResourcePtr i = engine.res().addResource(DummyResource::create("i"));
    ResourcePtr j = engine.res().addResource(DummyResource::create("k"));
    ResourcePtr k = engine.res().createResource<DummyResource>("k");

    //engine.log().log() << engine.res();

    engine.res().delResource(1);
    engine.res().delResource(4);
    engine.log().log() << engine.res();

    engine.log().log() << "Mem usage: "<< engine.res().getMemSize() << " bytes\n";
    engine.log().log() << "Full mem usage: "<< engine.res().getMemSizeFull() << " bytes\n";
}
////////////////////////////////////////////////////////////////////////////////
