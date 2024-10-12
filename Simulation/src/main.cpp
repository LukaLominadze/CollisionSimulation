#include "core/EntryPoint.h"

#include "layers/SimulationLayer.h"

Application* CreateApplication() {
	Application* app = new Application("CollisionSimulation", 1366, 768, false, false);
	app->PushLayer(new SimulationLayer());
	return app;
}