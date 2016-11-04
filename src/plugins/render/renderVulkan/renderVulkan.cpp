////////////////////////////////////////////////////////////////////////////////
#include "renderVulkan.hpp"
////////////////////////////////////////////////////////////////////////////////
PluginInfo pluginInfo = { "renderVulkan",
                          "renderVulkan",
                          0,
                          1};
////////////////////////////////////////////////////////////////////////////////
PluginRenderVulkan* lib = nullptr;
////////////////////////////////////////////////////////////////////////////////
const PluginInfo* getPluginInfo()
{
    return &pluginInfo;
}
////////////////////////////////////////////////////////////////////////////////
Library* getLibInstance(Engine* engine)
{
    if (lib == nullptr)
    {
        lib = new PluginRenderVulkan(*engine);
    }
    return lib;
}
////////////////////////////////////////////////////////////////////////////////
void closeLibInstance()
{
    delete lib;
    lib = nullptr;
}
////////////////////////////////////////////////////////////////////////////////
PluginRenderVulkan::PluginRenderVulkan(Engine &engine)
    : Library(engine)
    , m_instanceIsValid(0)
{
    log().log() << "PluginRenderVulkan start...\n";

    // Filling out application description:
    // sType is mandatory
    m_applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    // pNext is mandatory
    m_applicationInfo.pNext = nullptr;
    // The name of our application
    m_applicationInfo.pApplicationName = "app";
    // The name of the engine (e.g: Game engine name)
    m_applicationInfo.pEngineName = nullptr;
    // The version of the engine
    m_applicationInfo.engineVersion = 1;
    // The version of Vulkan we're using for this application
    m_applicationInfo.apiVersion = VK_API_VERSION_1_0;

    // Filling out instance description:
    // sType is mandatory
    m_instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    // pNext is mandatory
    m_instanceInfo.pNext = nullptr;
    // flags is mandatory
    m_instanceInfo.flags = 0;
    // The application info structure is then passed through the instance
    m_instanceInfo.pApplicationInfo = &m_applicationInfo;
    // Don't enable and layer
    m_instanceInfo.enabledLayerCount = 0;
    m_instanceInfo.ppEnabledLayerNames = nullptr;
    // Don't enable any extensions
    m_instanceInfo.enabledExtensionCount = 0;
    m_instanceInfo.ppEnabledExtensionNames = nullptr;

    // Now create the desired instance
    VkResult result = vkCreateInstance(&m_instanceInfo, nullptr, &m_instance);
    if (result != VK_SUCCESS)
    {
        log().log() << "Failed to create instance:" << result << "\n";
    }
    else
    {
        m_instanceIsValid = 1;
    }
}
////////////////////////////////////////////////////////////////////////////////
PluginRenderVulkan::~PluginRenderVulkan()
{
    log().log() << "PluginRenderVulkan stop...\n";
    if (m_instanceIsValid)
    {
        vkDestroyInstance(m_instance, nullptr);
    }
}
////////////////////////////////////////////////////////////////////////////////
