#include "core/EntryPoint.h"

#include "layers/SimulationLayer.h"

Application* CreateApplication() {
	Application* app = new Application("CollisionSimulation", 960, 540, true, false);
	app->PushLayer(new SimulationLayer());
	return app;
}