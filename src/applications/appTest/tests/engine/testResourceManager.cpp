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
        return std::make_shared<DummyResource>(name);
    }

    static const char* getSearchPath()
    {
        return ".";
    }

    virtual size_t getMemSize() const
    {
        return sizeof(*this);
    }

protected:
    virtual void printOn(Logger& o) const
    {
        o << "DummyResource: " << getName() << " - " << id;
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

    DummyResourcePtr a = engine.res().create<DummyResource>("a");
    DummyResourcePtr b = engine.res().create<DummyResource>("b");
    DummyResourcePtr c = engine.res().create<DummyResource>("c");
    DummyResourcePtr d = engine.res().create<DummyResource>("d");
    DummyResourcePtr e = engine.res().create<DummyResource>("e");
    DummyResourcePtr f = engine.res().create<DummyResource>("f");
    DummyResourcePtr g = engine.res().create<DummyResource>("g");
    DummyResourcePtr h = engine.res().create<DummyResource>("h");
    DummyResourcePtr i = engine.res().create<DummyResource>("i");
    DummyResourcePtr j = engine.res().create<DummyResource>("j");
    DummyResourcePtr k = engine.res().create<DummyResource>("k");

    //engine.log().log() << engine.res();

    engine.res().delResource(1);
    engine.res().delResource(4);
    engine.log().log() << engine.res();

    engine.log().log() << "Mem usage: "<< engine.res().getMemSize() << " bytes\n";
    engine.log().log() << "Full mem usage: "<< engine.res().getMemSizeFull() << " bytes\n";
}
////////////////////////////////////////////////////////////////////////////////
