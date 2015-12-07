#pragma once
#include "System.h"
#include "RenderingContext.h"
class RenderingSystem : public System
{
public:
	RenderingSystem(RenderingContext* rendContx);
	~RenderingSystem();


	void Draw(GameObject* objectToDraw);

	
	void Update(){ RenderFrame(); };


private:

	void RenderFrame();

	RenderingContext* RC;

	glm::mat4 _projection;
	glm::mat4 _cameraObscura;


	std::vector<GameObject*> drawableObj;
	std::vector<GameObject*>::iterator ObjIT;

};

