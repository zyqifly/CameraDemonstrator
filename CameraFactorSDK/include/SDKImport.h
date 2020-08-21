#pragma once
#pragma warning(disable:4251)
#pragma warning(disable:26451)
#ifdef CAMERA_FACTORY_DYNAMIC
#define	CAMERA_FACTORY_API	__declspec(dllexport)
#else	
#define	CAMERA_FACTORY_API
#endif // CAMERA_FACTORY_DYNAMIC
