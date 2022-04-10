#ifndef __MAP_H__
#define __MAP_H__

#include "Module.h"
#include "List.h"
#include "Point.h"
#include "Collisions.h"

#include "PugiXml\src\pugixml.hpp"

// Struct to hold information for a TileSet
struct TileSet
{
	SString	name;
	int	firstgid;
	int margin;
	int	spacing;
	int	tileWidth;
	int	tileHeight;

	SDL_Texture* texture;
	int	texWidth;
	int	texHeight;
	int	tilecount;
	int	columns;

	// Method that receives a tile id and returns it's Rectfind the Rect associated with a specific tile id
	SDL_Rect GetTileRect(int id) const;
};

// Enum for map type, just for convenience,
enum MapTypes
{
	MAPTYPE_UNKNOWN = 0,
	MAPTYPE_ORTHOGONAL,
	MAPTYPE_ISOMETRIC,
	MAPTYPE_STAGGERED
};

// Generic structure to hold properties
struct Properties
{
	struct Property
	{
		//...
		SString name;
		int intValue;
		const char* charValue;

	};
	
	~Properties()
	{
		//...
		ListItem<Property*>* item;
		item = list.start;

		while (item != NULL)
		{
			RELEASE(item->data);
			item = item->next;
		}

		list.clear();
	}

	// L06: DONE 7: Method to ask for the value of a custom property
	template <class T>
	T GetProperty(const char* name, int default_value = 0) const;

	List<Property*> list;
};

// Struct for the map layer
struct MapLayer
{
	SString	name;
	int width;
	int height;
	uint* data;

	bool isHigh;

	// Support custom properties
	Properties properties;

	MapLayer() : data(NULL)
	{}

	~MapLayer()
	{
		RELEASE(data);
	}

	// L04: DONE 6: Short function to get the value of x,y
	inline uint Get(int x, int y) const
	{
		return data[(y * width) + x];
	}
};

// Struct to hold the information to Map node
struct MapData
{
	int width;
	int	height;
	int	tileWidth;
	int	tileHeight;
	SDL_Color backgroundColor;
	MapTypes type;
	List<TileSet*> tilesets;

	// List of layers to the map
	List<MapLayer*> layers;
};


class Map : public Module
{
public:

    Map(App* application, bool start_enabled = true);

    // Destructor
    virtual ~Map();

    // Called before render is available
    bool Awake(pugi::xml_node& conf);

	bool Start();

    // Called each loop iteration
    void Draw();
	void ReDraw();

    // Called before quitting
    bool CleanUp();

    // Load new map
    bool Load(const char* path);

	//Translates x,y coordinates from map positions to world positions
	iPoint MapToWorld(int x, int y) const;

	// Add orthographic world to map coordinates
	iPoint WorldToMap(int x, int y) const;

private:

	// Methods to load all required map data
	bool LoadMap(pugi::xml_node mapFile);
	bool LoadTileSets(pugi::xml_node mapFile);
	bool LoadTilesetDetails(pugi::xml_node& tileset_node, TileSet* set);
	bool LoadTilesetImage(pugi::xml_node& tileset_node, TileSet* set);

	bool LoadLayer(pugi::xml_node& node, MapLayer* layer);
	bool LoadAllLayers(pugi::xml_node mapNode);

	// Load a group of properties 
	bool LoadProperties(pugi::xml_node& node, Properties& properties);

	// Pick the right Tileset based on a tile id
	TileSet* GetTilesetFromTileId(int id) const;

public:

	MapData mapData;

	void LoadCol();
	void RemoveCol();

	Collider* mapWalls[2000];
	//TileSet* mapTiles[3600];

	
	List<const char*>charValues;
	List<int>intValues;

	Entity* wallsEntity;

	int contador1 = 0;
	int contador2 = 0;

	const char* wallChar3;

private:

    SString folder;
    bool mapLoaded;
	

};

#endif // __MAP_H__