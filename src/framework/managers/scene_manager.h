
#ifndef FRAMEWORK_MANAGERS_SCENEMANAGER_H
#define FRAMEWORK_MANAGERS_SCENEMANAGER_H

#include <framework/graphics/scene.h>

namespace framework {
namespace managers {

class SceneManager
{
public:
	void render();

};

} // ns managers
} // ns framework

extern framework::managers::SceneManager g_sceneManager;

#endif