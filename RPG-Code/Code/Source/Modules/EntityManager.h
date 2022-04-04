#ifndef __ENTITY_MANAGER_H__
#define __ENTITY_MANAGER_H__

#include "Module.h"
#include "List.h"
#include <vector>

class Entity;
class DynamicEntity;
class StaticEntity;

enum class EntityType;

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
	bool CleanUp();

	bool Save(pugi::xml_node& file)const;
	bool Load(pugi::xml_node& file);


	Entity* CreateEntity(EntityType type);

	Entity* FindEntity(EntityType type);


	void DestroyEntity(Entity* entity);

public:

	List<Entity*> entityList;

	List<DynamicEntity*> dynamicEnitiesList;
	List<StaticEntity*> staticEnitiesList;

};


#endif // !__ENTITY_MANAGER_H__