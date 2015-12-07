
#pragma once

class OpaquePtrSample
{
public:

	OpaquePtrSample();
	~OpaquePtrSample();
	
	void doSomething();

private:
	
	class Implementation;
	Implementation* _impl;

};

