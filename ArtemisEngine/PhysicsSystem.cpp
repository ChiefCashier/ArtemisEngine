#include "PhysicsSystem.h"
#include "GameObject.h"
#include "Transformable.h"
#include <math.h>

PhysicsSystem::PhysicsSystem(float grav)
{
	gravity = grav;
	deltaTime = 0.016f;
}

void PhysicsSystem::Update(double deltaT)
{
	PCIT = physicsComponents.begin();
	while (PCIT != physicsComponents.end())
	{
		if ((*PCIT)->GetParent() == nullptr)
			PCIT++;
		else
		{
			UpdateForces((*PCIT));

			Collision((*PCIT));

			PCIT++; 
		}
	}

	PCIT = physicsComponents.begin();
	while (PCIT != physicsComponents.end())
	{
		if ((*PCIT)->GetParent() == nullptr)
			PCIT++;
		else
		{
			if (!(*PCIT)->collision)
			{
				UpdateSpeed((*PCIT));
			}
			else
			{
				(*PCIT)->collision = false;
			}
			PCIT++;
		}
	}



}

void PhysicsSystem::UpdateSpeed(Physics* comp)
{

	GameObject* GO = (GameObject*)comp->GetParent();
	Transformable* trans = GO->GetComponent<Transformable>();
	if (trans->GetOrigin().y + comp->GetSpeed().y * deltaTime > 80)
	{
		trans->SetOrigin(trans->GetOrigin().x, 80, trans->GetOrigin().z);
		comp->SetSpeed(Vector3<float>(comp->GetSpeed().x, -std::abs(comp->GetSpeed().y * comp->GetElasticity()), comp->GetSpeed().z));
		comp->SetForces(Vector3<float>(comp->GetForces().x, comp->GetForces().y - gravity * comp->GetMass(), comp->GetForces().z));
		UpdateAngularSpeed(comp, 0);
	}

	if (trans->GetOrigin().y + comp->GetSpeed().y * deltaTime < -80)
	{
		trans->SetOrigin(trans->GetOrigin().x, -80, trans->GetOrigin().z);
		comp->SetSpeed(Vector3<float>(comp->GetSpeed().x, std::abs(comp->GetSpeed().y * comp->GetElasticity()), comp->GetSpeed().z));
		comp->SetForces(Vector3<float>(comp->GetForces().x, comp->GetForces().y + gravity * comp->GetMass(), comp->GetForces().z));
		UpdateAngularSpeed(comp, 0);
	}

	if (trans->GetOrigin().x + comp->GetSpeed().x * deltaTime < -120)
	{
		trans->SetOrigin(-120, trans->GetOrigin().y, trans->GetOrigin().z);
		comp->SetSpeed(Vector3<float>(std::abs(comp->GetSpeed().x * comp->GetElasticity()), comp->GetSpeed().y, comp->GetSpeed().z));
		UpdateAngularSpeed(comp, 1);
	}

	if (trans->GetOrigin().x + comp->GetSpeed().x * deltaTime >  120)
	{
		trans->SetOrigin(120, trans->GetOrigin().y, trans->GetOrigin().z);
		comp->SetSpeed(Vector3<float>(-std::abs(comp->GetSpeed().x * comp->GetElasticity()), comp->GetSpeed().y, comp->GetSpeed().z));
		UpdateAngularSpeed(comp, 1);
	}

	if (trans->GetOrigin().z + comp->GetSpeed().z * deltaTime < -400)
	{
		trans->SetOrigin(trans->GetOrigin().x, trans->GetOrigin().z, -400);
		comp->SetSpeed(Vector3<float>(comp->GetSpeed().x, comp->GetSpeed().y, std::abs(comp->GetSpeed().z * comp->GetElasticity())));
		UpdateAngularSpeed(comp, 2);
	}

	if (trans->GetOrigin().z + comp->GetSpeed().z * deltaTime > -100)
	{
		trans->SetOrigin(trans->GetOrigin().x, trans->GetOrigin().y, -100);
		comp->SetSpeed(Vector3<float>(comp->GetSpeed().x, comp->GetSpeed().y, -std::abs(comp->GetSpeed().z * comp->GetElasticity())));
		UpdateAngularSpeed(comp, 2);
	}



	comp->SetSpeed(Vector3<float>(
		comp->GetSpeed().x + (comp->GetForces().x * deltaTime / comp->GetMass() ),	//X
		comp->GetSpeed().y + (comp->GetForces().y * deltaTime / comp->GetMass() ),	//Y
		comp->GetSpeed().z + (comp->GetForces().z * deltaTime / comp->GetMass() )	//Z
		));

	comp->SetForces(Vector3<float>(
		0.0f,
		0.0f,
		0.0f
		));

	GO->GetComponent<Transformable>()->SetOrigin(
		GO->GetComponent<Transformable>()->GetOrigin().x + comp->GetSpeed().x * deltaTime,
		GO->GetComponent<Transformable>()->GetOrigin().y + comp->GetSpeed().y * deltaTime,
		GO->GetComponent<Transformable>()->GetOrigin().z + comp->GetSpeed().z * deltaTime
		);
	GO->GetComponent<Transformable>()->SetRotation(
		GO->GetComponent<Transformable>()->GetRotation().x + comp->GetAngularSpeed().x * deltaTime,
		GO->GetComponent<Transformable>()->GetRotation().y + comp->GetAngularSpeed().y * deltaTime,
		GO->GetComponent<Transformable>()->GetRotation().z + comp->GetAngularSpeed().z * deltaTime
		);
}
void PhysicsSystem::UpdateAngularSpeed(Physics* comp, int x)
{
	Vector3<float> angularVec = comp->GetAngularSpeed();
	Vector3<float> speedVec = comp->GetSpeed();

	switch (x)
	{
		case 0:
			comp->SetSpeed(Vector3<float>(speedVec.x - angularVec.z * comp->GetFriction() * deltaTime, speedVec.y, speedVec.z + angularVec.x * comp->GetFriction() * deltaTime));
			comp->SetAngularSpeed(Vector3<float>(angularVec.x, angularVec.y, angularVec.z - angularVec.z * comp->GetFriction()* deltaTime - speedVec.x * comp->GetFriction() * deltaTime));
			break;
	
		case 1:
			comp->SetSpeed(Vector3<float>(speedVec.x, speedVec.y - angularVec.x  * comp->GetFriction() * deltaTime, speedVec.z + angularVec.y  * comp->GetFriction() * deltaTime));
			comp->SetAngularSpeed(Vector3<float>(angularVec.x - angularVec.x * comp->GetFriction()* deltaTime - speedVec.x * comp->GetFriction() * deltaTime, angularVec.y, angularVec.z));
			break;
	
		case 2:
			comp->SetSpeed(Vector3<float>(speedVec.x - angularVec.z * comp->GetFriction() * deltaTime, speedVec.y - angularVec.x * comp->GetFriction() * deltaTime, speedVec.z));
			comp->SetAngularSpeed(Vector3<float>(angularVec.x - angularVec.x * comp->GetFriction() * deltaTime - speedVec.x * comp->GetFriction() * deltaTime, angularVec.y, angularVec.z - angularVec.z * comp->GetFriction()* deltaTime));
			break;
	}
}
void PhysicsSystem::UpdateForces(Physics* comp)
{
	comp->SetForces(Vector3<float>(
		comp->GetForces().x,
		comp->GetForces().y - gravity * comp->GetMass(),
		comp->GetForces().z
		));
}

void PhysicsSystem::UpdateCollisionMap(Physics* comp)
{
	if (CollisionMap.find(comp->componentId) != CollisionMap.end())
	{
		PCIT2 = physicsComponents.begin();
		GameObject* GO = (GameObject*)comp->GetParent();
		GameObject* GO2 = (GameObject*)(*PCIT2)->GetParent();
		float deltax = GO->GetComponent<Transformable>()->GetOrigin().x - GO2->GetComponent<Transformable>()->GetOrigin().x + comp->GetSpeed().x * deltaTime + (*PCIT2)->GetSpeed().x * deltaTime;
		float deltay = GO->GetComponent<Transformable>()->GetOrigin().y - GO2->GetComponent<Transformable>()->GetOrigin().y + comp->GetSpeed().y * deltaTime + (*PCIT2)->GetSpeed().y * deltaTime;
		float deltaz = GO->GetComponent<Transformable>()->GetOrigin().z - GO2->GetComponent<Transformable>()->GetOrigin().z + comp->GetSpeed().z * deltaTime + (*PCIT2)->GetSpeed().z * deltaTime;
	}
}

void PhysicsSystem::Collision(Physics* comp)
{
	GameObject* GO = (GameObject*)comp->GetParent();

	PCIT2 = physicsComponents.begin();

	while (PCIT2 != physicsComponents.end())
	{
		if ((*PCIT2)->GetParent() == nullptr)
			PCIT2++;
		else if ((*PCIT2)->componentId == comp->componentId)
			PCIT2++;
		else
		{
			GameObject* GO2 = (GameObject*)(*PCIT2)->GetParent();

			float deltax = GO->GetComponent<Transformable>()->GetOrigin().x - GO2->GetComponent<Transformable>()->GetOrigin().x + comp->GetSpeed().x * deltaTime + (*PCIT2)->GetSpeed().x * deltaTime;
			float deltay = GO->GetComponent<Transformable>()->GetOrigin().y - GO2->GetComponent<Transformable>()->GetOrigin().y + comp->GetSpeed().y * deltaTime + (*PCIT2)->GetSpeed().y * deltaTime;
			float deltaz = GO->GetComponent<Transformable>()->GetOrigin().z - GO2->GetComponent<Transformable>()->GetOrigin().z + comp->GetSpeed().z * deltaTime + (*PCIT2)->GetSpeed().z * deltaTime;
			
			float deltax2 = GO->GetComponent<Transformable>()->GetOrigin().x - GO2->GetComponent<Transformable>()->GetOrigin().x + comp->GetSpeed().x * deltaTime * 2 + (*PCIT2)->GetSpeed().x * deltaTime * 2;
			float deltay2 = GO->GetComponent<Transformable>()->GetOrigin().y - GO2->GetComponent<Transformable>()->GetOrigin().y + comp->GetSpeed().y * deltaTime * 2 + (*PCIT2)->GetSpeed().y * deltaTime * 2;
			float deltaz2 = GO->GetComponent<Transformable>()->GetOrigin().z - GO2->GetComponent<Transformable>()->GetOrigin().z + comp->GetSpeed().z * deltaTime * 2 + (*PCIT2)->GetSpeed().z * deltaTime * 2;


			bool colision = true;
			int i = 2;

			Transformable* trans1 = GO->GetComponent<Transformable>();
			Transformable* trans2 = GO2->GetComponent<Transformable>();

			float temp1X = 0;
			float temp1Y = 0;
			float temp2X = 0;
			float temp2Y = 0;



			if (std::cbrt(std::pow(deltax, 2) + std::pow(deltay, 2) + std::pow(deltaz, 2)) <= 14)
			{ 			
				
				Vector3<float> asd(GO->GetComponent<Transformable>()->GetOrigin().x + comp->GetSpeed().x * deltaTime, GO->GetComponent<Transformable>()->GetOrigin().y+ comp->GetSpeed().y * deltaTime, GO->GetComponent<Transformable>()->GetOrigin().z + comp->GetSpeed().z * deltaTime);

				Vector3<float> asd2(GO2->GetComponent<Transformable>()->GetOrigin().x + comp->GetSpeed().x * deltaTime, GO2->GetComponent<Transformable>()->GetOrigin().y + comp->GetSpeed().y * deltaTime, GO2->GetComponent<Transformable>()->GetOrigin().z + comp->GetSpeed().z * deltaTime);


				float angle = atan((asd.x - asd2.x) / (asd.y - asd2.y));

				if (abs(asd.y - asd2.y) < 5)
				if (asd.y - asd2.y < 0)
					angle = 0;
				else
					angle = 3.14f;
				
				if (abs(asd.x - asd2.x) < 5)
				if (asd.x - asd2.x < 0)
					angle = 3.14f / 4;
				else
					angle = 3.14f / 2;

				float X = deltax / 2;
				X += asd2.x;
				float Y = deltay / 2;
				Y += asd2.y;


				if (deltax < 0 && deltay > 0)
				{
					temp1X = trans1->GetOrigin().x + comp->GetSpeed().x * deltaTime - cos(angle) * 7;
					temp1Y = trans1->GetOrigin().y + comp->GetSpeed().y * deltaTime + sqrt(sin(angle)*sin(angle)) * 7;
													
					temp2X = trans2->GetOrigin().x + (*PCIT2)->GetSpeed().x * deltaTime + cos(angle) * 7;
					temp2Y = trans2->GetOrigin().y + (*PCIT2)->GetSpeed().y * deltaTime - sqrt(sin(angle)*sin(angle)) * 7;
				}									
													
				if (deltax < 0 && deltay < 0)		
				{									
					temp1X = trans1->GetOrigin().x + comp->GetSpeed().x * deltaTime - cos(angle) * 7;
					temp1Y = trans1->GetOrigin().y + comp->GetSpeed().y * deltaTime - sqrt(sin(angle)*sin(angle)) * 7;
													
					temp2X = trans2->GetOrigin().x + (*PCIT2)->GetSpeed().x * deltaTime + cos(angle) * 7;
					temp2Y = trans2->GetOrigin().y + (*PCIT2)->GetSpeed().y * deltaTime + sqrt(sin(angle)*sin(angle)) * 7;
				}									
													
				if (deltax > 0 && deltay < 0)		
				{									
					temp1X = trans1->GetOrigin().x + comp->GetSpeed().x * deltaTime + cos(angle) * 7;
					temp1Y = trans1->GetOrigin().y + comp->GetSpeed().y * deltaTime - sqrt(sin(angle)*sin(angle)) * 7;
													
					temp2X = trans2->GetOrigin().x + (*PCIT2)->GetSpeed().x  * deltaTime - cos(angle) * 7;
					temp2Y = trans2->GetOrigin().y + (*PCIT2)->GetSpeed().y  * deltaTime + sqrt(sin(angle)*sin(angle)) * 7;
				}									
													
				if (deltax > 0 && deltay > 0)		
				{									
					temp1X = trans1->GetOrigin().x + comp->GetSpeed().x  * deltaTime + cos(angle) * 7;
					temp1Y = trans1->GetOrigin().y + comp->GetSpeed().y  * deltaTime + sqrt(sin(angle)*sin(angle)) * 7;
													
					temp2X = trans2->GetOrigin().x + (*PCIT2)->GetSpeed().x  * deltaTime - cos(angle) * 7;
					temp2Y = trans2->GetOrigin().y + (*PCIT2)->GetSpeed().y  * deltaTime - sqrt(sin(angle)*sin(angle)) * 7;
				}
				
				trans1->SetOrigin(temp1X, temp1Y, trans1->GetOrigin().z);
				trans2->SetOrigin(temp2X, temp2Y, trans2->GetOrigin().z);


				while(colision)
				{
					float deltax = GO->GetComponent<Transformable>()->GetOrigin().x - GO2->GetComponent<Transformable>()->GetOrigin().x + comp->GetSpeed().x * (deltaTime / i) + (*PCIT2)->GetSpeed().x * (deltaTime / i);
					float deltay = GO->GetComponent<Transformable>()->GetOrigin().y - GO2->GetComponent<Transformable>()->GetOrigin().y + comp->GetSpeed().y * (deltaTime / i) + (*PCIT2)->GetSpeed().y * (deltaTime / i);
					float deltaz = GO->GetComponent<Transformable>()->GetOrigin().z - GO2->GetComponent<Transformable>()->GetOrigin().z + comp->GetSpeed().z * (deltaTime / i) + (*PCIT2)->GetSpeed().z * (deltaTime / i);
					float x = std::cbrt(std::pow(deltax, 2) + std::pow(deltay, 2) + std::pow(deltaz, 2));
					if (x > 15)
						i -= 1;
					if (x < 14)
						i += 2;
					else
					{	
						trans1->SetOrigin(trans1->GetOrigin().x + comp->GetSpeed().x * (deltaTime / i), trans1->GetOrigin().y + comp->GetSpeed().y * (deltaTime / i),trans1->GetOrigin().z + comp->GetSpeed().z * (deltaTime / i));
						trans2->SetOrigin(trans2->GetOrigin().x + comp->GetSpeed().x * (deltaTime / i), trans2->GetOrigin().y + comp->GetSpeed().y * (deltaTime / i), trans2->GetOrigin().z + comp->GetSpeed().z * (deltaTime / i));
						colision = false;
						
					}
					if (i > 100)
					{
						colision = false;
					}
				}
		
				std::cout << "collision" << std::endl;

				//GO->GetComponent<Transformable>()->SetOrigin(
				//	GO->GetComponent<Transformable>()->GetOrigin()[0] - 50 * sin(angle)* deltaTime,
				//	GO->GetComponent<Transformable>()->GetOrigin()[1] - 50 * cos(angle)* deltaTime,
				//	GO->GetComponent<Transformable>()->GetOrigin()[2]
				//	);

				//GO2->GetComponent<Transformable>()->SetOrigin(
				//	GO2->GetComponent<Transformable>()->GetOrigin()[0] - 50 * sin(angle + 3.141)* deltaTime,
				//	GO2->GetComponent<Transformable>()->GetOrigin()[1] - 50 * cos(angle + 3.141)* deltaTime,
				//	GO2->GetComponent<Transformable>()->GetOrigin()[2]
				//	);


				

				float AbN = comp->GetSpeed().x * cos(angle) + comp->GetSpeed().y * sin(angle);
				float AbT = comp->GetSpeed().x * -sin(angle) + comp->GetSpeed().y * cos(angle);
				float BbN = (*PCIT2)->GetSpeed().x * cos(angle) + (*PCIT2)->GetSpeed().y * sin(angle);
				float BbT = (*PCIT2)->GetSpeed().x * -sin(angle) + (*PCIT2)->GetSpeed().y * cos(angle);

				float AaN = ((comp->GetMass() - comp->GetElasticity() * (*PCIT2)->GetMass()) / (comp->GetMass() + (*PCIT2)->GetMass())) * AbN;
				AaN += (((1 + comp->GetElasticity()) * (*PCIT2)->GetMass()) / (comp->GetMass() + (*PCIT2)->GetMass())) * BbN;
				float BaN = ((comp->GetMass() - (*PCIT2)->GetElasticity() * (*PCIT2)->GetMass()) / (comp->GetMass() + (*PCIT2)->GetMass())) * BbN;
				BaN += (((1 + comp->GetElasticity()) * (*PCIT2)->GetMass()) / (comp->GetMass() + (*PCIT2)->GetMass())) * AbN;

				comp->SetSpeed(Vector3<float>((AaN * cos(angle) + AbT * sin(-angle)), (AaN * sin(angle) + AbT * cos(angle)), comp->GetSpeed().z));
				(*PCIT2)->SetSpeed(Vector3<float>((BaN * cos(angle) + BbT * sin(-angle)), (BaN * sin(angle) + BbT * cos(angle)), (*PCIT2)->GetSpeed().z));
				//comp->SetForces(Vector3<float>(comp->GetForces().x, comp->GetForces().y + gravity * comp->GetMass(), comp->GetForces().z));
				UpdateSpeed(comp);
				UpdateSpeed((*PCIT2));
				comp->collision = true;
				(*PCIT2)->collision = true;

			}
			PCIT2++;
		}
			
	}

}

void PhysicsSystem::AddPhysicsComponent(Physics* physComp)
{
	physicsComponents.push_back(physComp);
}