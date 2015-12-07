#include "RenderingSystem.h"


RenderingSystem::RenderingSystem(RenderingContext* rendContx)
{
	RC = rendContx;
	_projection = rendContx->get_projection();
}

RenderingSystem::~RenderingSystem()
{
	delete RC;
}

void RenderingSystem::Draw(GameObject* objectToDraw)
{
	if (objectToDraw->GetComponent<Renderable>() == nullptr || objectToDraw->GetComponent<Transformable>() == nullptr)
		return;
	ObjIT = drawableObj.begin();
	while (ObjIT != drawableObj.end())
	{

		if (*ObjIT == objectToDraw)
			return;
		ObjIT++;
	}
	drawableObj.push_back(objectToDraw);
}


void RenderingSystem::RenderFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glFlush();
	glUseProgram(RC->getProgramIndex());


	ObjIT = drawableObj.begin();
	while (ObjIT != drawableObj.end())
	{

		GameObject* OTD = *ObjIT;
		Renderable* Rend = OTD->GetComponent<Renderable>();
		if (Rend->draw)
		{
			Transformable* Trans = OTD->GetComponent<Transformable>();


			glBindVertexArray(Rend->vertexArray);


			glUniform1f(RC->get_alphaChannel(), Rend->getAlpha());

			glm::mat4 _worldtransform = glm::translate(glm::vec3(Trans->GetOrigin().x, Trans->GetOrigin().y, Trans->GetOrigin().z));
			_worldtransform *= glm::rotate(Trans->GetRotation().x, glm::vec3(1.0f, 0.0f, 0.0f)) * glm::rotate(Trans->GetRotation().y, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::rotate(Trans->GetRotation().z, glm::vec3(0.0f, 0.0f, 1.0f));

			glUniformMatrix4fv(RC->get_worldIndex(), 1, GL_FALSE, glm::value_ptr(_worldtransform));


			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, Rend->hasTexture == true ? Rend->getTextureID() : 0u);


			glDrawElements(GL_TRIANGLES, Rend->get_indexSize(), GL_UNSIGNED_INT, reinterpret_cast<GLvoid*>(0));


			glBindTexture(GL_TEXTURE_2D, 0u);

			glBindVertexArray(0u);
		}
		ObjIT++;

	}

	_cameraObscura = glm::inverse(glm::translate(glm::vec3(0.0f, 0.0f, 0.0f))) * glm::rotate(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::rotate(0.0f, glm::vec3(1.0f, 0.0f, 0.0f)) * glm::rotate(0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	_cameraObscura *= glm::rotate(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::rotate(0.0f, glm::vec3(1.0f, 0.0f, 0.0f)) * glm::rotate(0.0f, glm::vec3(0.0f, 0.0f, 1.0f));

	glUniformMatrix4fv(RC->get_cameraIndex(), 1, GL_FALSE, glm::value_ptr(_cameraObscura));

	glUseProgram(0);

	SwapBuffers(RC->getHDC());
}