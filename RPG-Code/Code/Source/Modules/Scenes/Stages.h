#ifndef __STAGES_H__
#define __STAGES_H__

#include "Module.h"
#include "GuiButton.h"
#include "Animation.h"

struct SDL_Texture;
class Player;

enum class StageIndex {
	NONE,
	TOWN
};

class Stages : public Module
{
public:

	Stages(App* application, bool start_enabled = true);

	// Destructor
	virtual ~Stages();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	void ChangeStage(StageIndex newStage);

private:

public:
	bool pause;

	StageIndex actualStage;

	Player* playerPtr;

};

#endif // __STAGES_H__
