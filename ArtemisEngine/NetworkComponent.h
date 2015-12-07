#pragma once
#include "Vector3.h"
#include "Component.h"
#include <string>
#include <iostream>
#include <sstream>

class NetworkComponent : public Component
{
	friend std::ostream& operator<< (std::ostream& out, NetworkComponent* comp) {
		out << comp->command << " " << comp->object << " " << comp->texture << " " << comp->origin << " " << comp->rotation << " " << comp->velocity << " " << comp->force;
		return out;
	}

	friend std::istream& operator>> (std::istream& in, NetworkComponent* comp) {
		in >> comp->command;
		in >> comp->object;
		in >> comp->texture;
		in >> comp->origin;
		in >> comp->rotation;
		in >> comp->velocity;
		in >> comp->force;
		return in;
	}

public:

	NetworkComponent(
					int ID,
					std::string command,	std::string object,		std::string texture,
					Vector3<float> origin,	Vector3<float> rotation,
					Vector3<float> velocity,Vector3<float> force
					);
	NetworkComponent(int ID);
	~NetworkComponent();

	void SetValues(
		std::string command, std::string object, std::string texture,
		Vector3<float> origin, Vector3<float> rotation,
		Vector3<float> velocity, Vector3<float> force
		)
	{
		this->command = command;
		this->object = object;
		this->texture = texture;
		this->origin = origin;
		this->rotation = rotation;
		this->velocity = velocity;
		this->force = force;
	};

	std::string GetCommand()	{ return command; };
	std::string GetObjecti()		{ return object; };
	std::string GetTexture()	{ return texture; };

	Vector3<float> GetOrigin()	{ return origin; };
	Vector3<float> GetRotation(){ return rotation; };
	Vector3<float> GetVelocity(){ return velocity; };
	Vector3<float> GetForce()	{ return force; };


	void SetCommand(std::string in)	{ command = in; };
	void SetObject(std::string in)		{ object = in; };
	void SetTexture(std::string in)	{ texture = in; };

	void SetOrigin(Vector3<float> in)	{ origin = in; };
	void SetRotation(Vector3<float> in) { rotation = in; };
	void SetVelocity(Vector3<float> in) { velocity = in; };
	void SetForce(Vector3<float> in)	{ force = in; };

	std::string MsgForm()
	{
		std::string temp;
		char buffer[500];
		std::stringstream s;
		s << this;
		temp = s.str();
		for (int i = 0; i < temp.size(); i++)
		{
			buffer[i] = temp.at(i);
		}
		buffer[temp.size()] = '\0';
		std::string str(buffer);
		return str;
	};

	void Reform(char* msg)
	{
		std::stringstream s;
		std::string temp(msg);
		s << temp;
		s >> this;
	};




private:

	std::string command;
	std::string object;
	std::string texture;

	Vector3<float> origin;
	Vector3<float> rotation;
	Vector3<float> velocity;
	Vector3<float> force;

};

