#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "SDL/include/SDL_rect.h"
#define MAX_FRAMES 100

class Animation
{
public:
	float speed = 1.0f;
	SDL_Rect frames[MAX_FRAMES];
	bool loop = true;

	// Allows the animation to keep going back and forth
	bool pingpong = false;

	float currentFrame = 0.0f;

	int totalFrames = 0;
private:
	int loopCount = 0;
	int pingpongDirection = 1;

public:

	void PushBack(const SDL_Rect& rect)
	{
		frames[totalFrames++] = rect;
	}

	void Reset()
	{
		currentFrame = 0;
	}

	bool HasFinished()
	{
		if (currentFrame >= totalFrames - 1) {
			return true;
		}
		else {
			return false;
		}
	}

	void Update(float dt = 16)
	{
		currentFrame += speed * dt;
		if (currentFrame >= totalFrames)
		{
			currentFrame = (loop || pingpong) ? 0.0f : totalFrames - 1;
			++loopCount;

			if (pingpong)
				pingpongDirection = -pingpongDirection;
		}
	}

	SDL_Rect& GetCurrentFrame()
	{
		int actualFrame = currentFrame;
		if (pingpongDirection == -1)
			actualFrame = totalFrames - currentFrame;

		return frames[actualFrame];
	}

	int GetCurrentFrameINT() {
		int actualFrame = currentFrame;
		if (pingpongDirection == -1)
			actualFrame = totalFrames - currentFrame;

		return actualFrame;
	}

	void DeleteAnim() {
		totalFrames = 0;
	}

};

#endif