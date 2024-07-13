#include "DeltaTime.h"

using namespace gly;

DeltaTime::DeltaTime(double sPerFrame) :
	sPerFrame(sPerFrame),
	currTime(0), 
	elapsedTime(0),
	prevTime(glfwGetTime()),
	m_value(0)
{
}

float DeltaTime::floatValue() const
{
	return (float)m_value;
}

double DeltaTime::value() const
{
	return m_value;
}

void DeltaTime::wait()
{
	// Wait until at least enough time for a frame to start,
	// also taking into account the time spent running the
	// contents of the application loop prior.
	while (elapsedTime < sPerFrame)
	{
		currTime = glfwGetTime();
		elapsedTime += currTime - prevTime;
		prevTime = currTime;
	}

	m_value = elapsedTime;
	elapsedTime = 0;
}
