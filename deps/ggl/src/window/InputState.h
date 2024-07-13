#ifndef INPUT_STATE_H
#define INPUT_STATE_H

namespace ggl {

	struct InputState
	{
		/**
		 * @brief Indicates whether an input is being held down (i.e. active) REGARDLESS
		 * of when it was first pressed or released.
		 */
		bool isHeld;

		/**
		 * @brief Indicates whether an input has not yet been released, i.e. no release
		 * checks have been performed yet.
		 */
		bool hasNotBeenReleased;

		/**
		 * @brief Indicates whether an input has not yet been pressed, i.e. held down for
		 * the first time.
		 */
		bool hasNotBeenPressed;

		InputState()
			: isHeld(false), hasNotBeenReleased(false), hasNotBeenPressed(true)
		{
		}
	};

}

#endif