#ifndef __DIALOGSYSTEM__
#define __DIALOGSYSTEM__

#include "Module.h"
#include "ModuleQFonts.h"
#include "NPC.h"
#include "List.h"
#include "Point.h"

#define DIALOG_LENGHT 20

struct SDL_Texture;

class DialogSystem : public Module {
public:
	DialogSystem(App* application, bool start_enabled = true);

	virtual ~DialogSystem();

	bool Awake(pugi::xml_node& config);

	bool Start();

	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	bool CleanUp();

public:

	// Specify who is talking like: "trainer", 
	// then put all his texts together with the following format: { "First text", "second text", "final text" }
	// They will be displayed in order asking to press Space/Enter to continue
	void CreateDialog(NPCType charaType, const char* text[DIALOG_LENGHT]);

private:

	//NPCType charaType;
	SDL_Texture* currentChara;
	iPoint dialogPosition;
	bool wait;

	List<const char*> dialogList;

public:
	// Block Scene Update is true
	bool dialoging = false;
};

#endif // !__DIALOGSYSTEM__