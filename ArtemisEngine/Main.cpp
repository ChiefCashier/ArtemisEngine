#include "Window.h"
#include "RenderingSystem.h"
#include "PhysicsSystem.h"
#include "SystemManager.h"
#include "NetworkSystem.h"
#include "Input.h"
#include "ComponentFactory.h"
#include "GameObject.h"
#include "Renderable.h"
#include "Transformable.h"
#include "Vector3.h"

int main()
{

	Window window(0, L"Window", "Mastodon", 800, 600);
	window.ShowAWindow();
	RenderingContext* rendContext = new RenderingContext(&window);

	SystemManager* SM = new SystemManager();
	RenderingSystem* RS = new RenderingSystem(rendContext);
	PhysicsSystem* PS = new PhysicsSystem(98.1f);

	SM->AddSystem(RS);
	//SM->AddSystem(PS);

	bool ON = true;

	Renderable* R = ComponentFactory::CreateRenderable("assets/daebox.obj", "assets/tribaltatuointi.png");
	Physics* P = ComponentFactory::CreatePhysicsComponent(PS);
	Transformable* T = ComponentFactory::CreateTransformable(0,0,-1,0,45,0);

	GameObject* GO = new GameObject("ball");
	GO->AddComponent(R);
	GO->AddComponent(P);
	GO->AddComponent(T);

	RS->Draw(GO);
	float r = 0;
	while (true)
	{

		if (Input::isKeyPressed(Input::W))
				GO->GetComponent<Physics>()->SetForces(Vector3<float>(0,  1000, 0));//*/NC->SetOrigin(NC->GetOrigin() + Vector3<float>(0, 1, 0));
			if (Input::isKeyPressed(Input::S))
				GO->GetComponent<Physics>()->SetForces(Vector3<float>(0, -1000, 0));//*/NC->SetOrigin(NC->GetOrigin() + Vector3<float>(0, -1, 0));
			if (Input::isKeyPressed(Input::D))
				GO->GetComponent<Physics>()->SetForces(Vector3<float>(1000, 0, 0));//*/NC->SetOrigin(NC->GetOrigin() + Vector3<float>(1, 0, 0));
			if (Input::isKeyPressed(Input::A))
				GO->GetComponent<Physics>()->SetForces(Vector3<float>(-1000, 0, 0));//*/NC->SetOrigin(NC->GetOrigin() + Vector3<float>(-1, 0, 0));
			if (Input::isKeyPressed(Input::Up))
				GO->GetComponent<Physics>()->SetForces(Vector3<float>(0, 0, 1000));//*/NC->SetOrigin(NC->GetOrigin() + Vector3<float>(0, 0, 1));
			if (Input::isKeyPressed(Input::Down))
				GO->GetComponent<Physics>()->SetForces(Vector3<float>(0, 0, -1000));//*/NC->SetOrigin(NC->GetOrigin() + Vector3<float>(0, 0, -1));
		

		window.WindowMessageCheck();
		SM->UpdateSystems();

		T->SetRotation(Vector3<float>(0,r,0));
		r += 0.1;

		if (Input::isKeyPressed(Input::Escape))
		{
			ON = false;
		}

		if (!ON)
			break;
	}
	return 0;
}