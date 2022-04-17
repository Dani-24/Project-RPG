#ifndef __ENTITY_MANAGER_H__
#define __ENTITY_MANAGER_H__

#include "Module.h"
#include "List.h"
#include <vector>

class Entity;

enum class EntityType;
enum class EntityType;
enum class DynamicType;
enum class CharacterType;
enum class NPCType;
enum class NormalEnemyType;
enum class PartyType;

class EntityManager : public Module
{
public:
	EntityManager(App* application, bool start_enabled = true);
	~EntityManager();

	bool Awake(pugi::xml_node& config);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	//bool Draw();
	bool CleanUp();

	bool Save(pugi::xml_node& file)const;
	bool Load(pugi::xml_node& file);


	Entity* CreateEntity(int x = 0, int y = 0);
	Entity* CreateEntity(EntityType type, int x = 0, int y = 0);
	Entity* CreateEntity(DynamicType type, int x = 0, int y = 0);
	Entity* CreateEntity(CharacterType type, int x = 0, int y = 0);
	Entity* CreateEntity(PartyType type, int x = 0, int y = 0);
	Entity* CreateEntity(NPCType type, int x = 0, int y = 0);
	Entity* CreateEntity(NormalEnemyType type, int x = 0, int y = 0);

	Entity* FindEntity(EntityType type);


	void DestroyEntity(Entity* entity);

public:

	List<Entity*> entityList;

};


#endif // !__ENTITY_MANAGER_H__