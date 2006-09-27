#include "osgART/VideoPlugin"
#include "osgART/VideoConfig"
#include "osgART/GenericVideo"
#include "DummyImageVideo"


DLL_API osgART::GenericVideo* osgart_createvideo(const osgART::VideoConfiguration& config)
{
	return new DummyImageVideo(config.deviceconfig);
}

OSGART_PLUGIN_ENTRY()
