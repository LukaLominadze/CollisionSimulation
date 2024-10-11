#include "core/EntryPoint.h"

Application* CreateApplication() {
	Application* app = new Application("CollisionSimulation", 960, 540, true);
	return app;
}