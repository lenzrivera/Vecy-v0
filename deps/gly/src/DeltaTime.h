#ifndef GLY_DELTATIME_INCLUDED
#define GLY_DELTATIME_INCLUDED

#include "GLFW/glfw3.h"

namespace gly {
	
	// Quick and dirty utility class for computing dt.
	class DeltaTime
	{
	private:
		const double sPerFrame;
		double currTime, elapsedTime, prevTime, m_value;

	public:
		DeltaTime(double sPerFrame);
		
		// Returns the time difference as a float, for convenience.
		float floatValue() const;

		// Returns the time difference.
		double value() const;

		// Waits for the next frame and recomputes the time difference.
		void wait();
	};
	
}

#endif