#include "App.h"
#include "Render.h"
#include "Textures.h"
#include "Map.h"

#include "Defs.h"
#include "Log.h"

#include "Entity.h"
#include "EntityManager.h"

#include <math.h>

using namespace  std;

Map::Map(App* application, bool start_enabled) : Module(application, start_enabled)
{
	name.Create("map");
	// Add all the string properties in the list
	charValues.add("Col");
	
	mapLoaded = false;
}

// Destructor
Map::~Map()
{}

template <class T>
T Properties::GetProperty(const char* value, int defaultValue) const
{
	//...

	ListItem<Property*>* item = list.start;

	while (item)
	{

		if (item->data->name == value) {

			ListItem<const char*>* charValueInList;
			charValueInList = app->map->charValues.start;

			for (charValueInList = app->map->charValues.start; charValueInList != NULL; charValueInList = charValueInList->next)
			{
				if (charValueInList->data == value)
				{
					return (T)item->data->charValue.GetString();
				}
			}
			return (T)item->data->intValue;
		}
			
		item = item->next;
	}
	return (T)defaultValue;
}

int Properties::GetPropertyInt(const char* value, int defaultValue) const
{
	//...

	ListItem<Property*>* item = list.start;

	while (item)
	{
		if (item->data->name == value) {

			return item->data->intValue;

		}

		item = item->next;
	}
	return defaultValue;
}

const char* Properties::GetPropertyChar(const char* value, const char* defaultValue) const
{
	//...

	ListItem<Property*>* item = list.start;

	while (item)
	{

		if (item->data->name == value) {

			return item->data->charValue.GetString();

		}

		item = item->next;
	}
	return defaultValue;
}

// Called before render is available
bool Map::Awake(pugi::xml_node& config)
{
	wallsEntity = app->entities->CreateEntity();
    LOG("Loading Map Parser");
    bool ret = true;

    folder.Create(config.child("folder").child_value());

    return ret;
}

bool Map::Start() {


	return true;
}
// Draw the map (all requried layers)
void Map::Draw()
{
	if (mapLoaded == false) return;

	// Prepare the loop to draw all tilesets + DrawTexture()
	ListItem<MapLayer*>* mapLayerItem;
	mapLayerItem = mapData.layers.start;

	// Draw all the layers and not just the first one
	while (mapLayerItem != NULL) {

		if (mapLayerItem->data->isHigh == false) {

			if (mapLayerItem->data->properties.GetProperty<int>("Draw") == 1) {

				for (int x = 0; x < mapLayerItem->data->width; x++)
				{
					for (int y = 0; y < mapLayerItem->data->height; y++)
					{
						// L04: DONE 9: Complete the draw function
						int gid = mapLayerItem->data->Get(x, y);

						if (gid > 0) {

							//Obtain the tile set using GetTilesetFromTileId
							//now we always use the firt tileset in the list
							//TileSet* tileset = mapData.tilesets.start->data;
							TileSet* tileset = GetTilesetFromTileId(gid);

							SDL_Rect r = tileset->GetTileRect(gid);
							iPoint pos = MapToWorld(x, y);

							app->render->DrawTexture(tileset->texture,
								pos.x,
								pos.y,
								&r);
						}

					}

				}

			}

		}

		mapLayerItem = mapLayerItem->next;
	}
}

void Map::ReDraw()
{
	if (mapLoaded == false) return;

	// Prepare the loop to draw all tilesets + DrawTexture()
	ListItem<MapLayer*>* mapLayerItem;
	mapLayerItem = mapData.layers.start;

	// Draw all the layers and not just the first one
	while (mapLayerItem != NULL) {

		if (mapLayerItem->data->isHigh == true) {

			if ((int)mapLayerItem->data->properties.GetProperty<int>("Draw") == 1) {

				for (int x = 0; x < mapLayerItem->data->width; x++)
				{
					for (int y = 0; y < mapLayerItem->data->height; y++)
					{
						// L04: DONE 9: Complete the draw function
						int gid = mapLayerItem->data->Get(x, y);

						if (gid > 0) {

							//Obtain the tile set using GetTilesetFromTileId
							//now we always use the firt tileset in the list
							//TileSet* tileset = mapData.tilesets.start->data;
							TileSet* tileset = GetTilesetFromTileId(gid);

							SDL_Rect r = tileset->GetTileRect(gid);
							iPoint pos = MapToWorld(x, y);

							app->render->DrawTexture(tileset->texture,
								pos.x,
								pos.y,
								&r);
						}

					}
				}
			}
		}

		mapLayerItem = mapLayerItem->next;
	}
}

// Create a method that translates x,y coordinates from map positions to world positions
iPoint Map::MapToWorld(int x, int y) const
{
	iPoint ret;

	// Add isometric map to world coordinates
	if (mapData.type == MAPTYPE_ORTHOGONAL)
	{
		ret.x = x * mapData.tileWidth;
		ret.y = y * mapData.tileHeight;
	}
	else if (mapData.type == MAPTYPE_ISOMETRIC)
	{
		ret.x = (x - y) * (mapData.tileWidth / 2);
		ret.y = (x + y) * (mapData.tileHeight / 2);
	}
	else
	{
		LOG("Unknown map type");
		ret.x = x; ret.y = y;
	}

	return ret;
}

// Add orthographic world to map coordinates
iPoint Map::WorldToMap(int x, int y) const
{
	iPoint ret(0, 0);

	// Add the case for isometric maps to WorldToMap
	if (mapData.type == MAPTYPE_ORTHOGONAL)
	{
		ret.x = x / mapData.tileWidth;
		ret.y = y / mapData.tileHeight;
	}
	else if (mapData.type == MAPTYPE_ISOMETRIC)
	{

		float half_width = mapData.tileWidth * 0.5f;
		float half_height = mapData.tileHeight * 0.5f;
		ret.x = int((x / half_width + y / half_height) / 2);
		ret.y = int((y / half_height - (x / half_width)) / 2);
	}
	else
	{
		LOG("Unknown map type");
		ret.x = x; ret.y = y;
	}

	return ret;
}

// Pick the right Tileset based on a tile id
TileSet* Map::GetTilesetFromTileId(int id) const
{
	ListItem<TileSet*>* item = mapData.tilesets.start;
	TileSet* set = item->data;

	while (item)
	{
		if (id < item->data->firstgid)
		{
			set = item->prev->data;
			break;
		}
		set = item->data;
		item = item->next;
	}

	return set;
}

// Get relative Tile rectangle
SDL_Rect TileSet::GetTileRect(int id) const
{
	SDL_Rect rect = { 0 };

	// Get relative Tile rectangle
	int relativeId = id - firstgid;
	rect.w = tileWidth;
	rect.h = tileHeight;
	rect.x = margin + ((rect.w + spacing) * (relativeId % columns));
	rect.y = margin + ((rect.h + spacing) * (relativeId / columns));
	
	return rect;
}

// Called before quitting
bool Map::CleanUp()
{
    LOG("Unloading map");

	RemoveCol();

    // Make sure you clean up any memory allocated from tilesets/map
    // Remove all tilesets
	ListItem<TileSet*>* item;
	item = mapData.tilesets.start;

	while (item != NULL)
	{
		RELEASE(item->data);
		item = item->next;
	}
	mapData.tilesets.clear();

	// Clean up all layer data
	// Remove all layers
	ListItem<MapLayer*>* item2;
	item2 = mapData.layers.start;

	while (item2 != NULL)
	{
		RELEASE(item2->data);
		item2 = item2->next;
	}
	mapData.layers.clear();

	app->entities->DestroyEntity(wallsEntity);

    return true;
}

// Load new map
bool Map::Load(const char* filename)
{
    bool ret = true;
    SString tmp("%s%s", folder.GetString(), filename);

	pugi::xml_document mapFile; 
    pugi::xml_parse_result result = mapFile.load_file(tmp.GetString());

    if(result == NULL)
    {
        LOG("Could not load map xml file %s. pugi error: %s", filename, result.description());
        ret = false;
    }

	// Load general info
    if(ret == true)
    {
        // L03: DONE 3: Create and call a private function to load and fill all your map data
		ret = LoadMap(mapFile);
	}

    // Create and call a private function to load a tileset
    // remember to support more any number of tilesets!
	if (ret == true)
	{
		ret = LoadTileSets(mapFile.child("map"));
	}

	// Iterate all layers and load each of them
	// Load layer info
	if (ret == true)
	{
		ret = LoadAllLayers(mapFile.child("map"));
	}
    

	mapLoaded = ret;

    if(ret == true)
    {
		LoadCol();
    }

	return ret;
}

// Load map general properties
bool Map::LoadMap(pugi::xml_node mapFile)
{
	bool ret = true;
	pugi::xml_node map = mapFile.child("map");

	if (map == NULL)
	{
		LOG("Error parsing map xml file: Cannot find 'map' tag.");
		ret = false;
	}
	else
	{
		// Load map general properties
		mapData.height = map.attribute("height").as_int();
		mapData.width = map.attribute("width").as_int();
		mapData.tileHeight = map.attribute("tileheight").as_int();
		mapData.tileWidth = map.attribute("tilewidth").as_int();

		// Add formula to go from isometric map to world coordinates
		mapData.type = MAPTYPE_UNKNOWN;
		if (strcmp(map.attribute("orientation").as_string(), "isometric") == 0)
		{
			mapData.type = MAPTYPE_ISOMETRIC;
		}
		if (strcmp(map.attribute("orientation").as_string(), "orthogonal") == 0)
		{
			mapData.type = MAPTYPE_ORTHOGONAL;
		}
	}

	return ret;
}

// Implement the LoadTileSet function to load the tileset properties
bool Map::LoadTileSets(pugi::xml_node mapFile) {

	bool ret = true;

	pugi::xml_node tileset;
	for (tileset = mapFile.child("tileset"); tileset && ret; tileset = tileset.next_sibling("tileset"))
	{
		TileSet* set = new TileSet();
		if (ret == true) ret = LoadTilesetDetails(tileset, set);
		if (ret == true) ret = LoadTilesetImage(tileset, set);
		mapData.tilesets.add(set);
	}

	return ret;
}

// Load Tileset attributes
bool Map::LoadTilesetDetails(pugi::xml_node& tileset_node, TileSet* set)
{
	bool ret = true;

	// Load Tileset attributes
	set->name.Create(tileset_node.attribute("name").as_string());
	set->firstgid = tileset_node.attribute("firstgid").as_int();
	set->tileWidth = tileset_node.attribute("tilewidth").as_int();
	set->tileHeight = tileset_node.attribute("tileheight").as_int();
	set->margin = tileset_node.attribute("margin").as_int();
	set->spacing = tileset_node.attribute("spacing").as_int();
	set->tilecount = tileset_node.attribute("tilecount").as_int();
	set->columns = tileset_node.attribute("columns").as_int();

	return ret;
}

// Load Tileset image
bool Map::LoadTilesetImage(pugi::xml_node& tileset_node, TileSet* set)
{
	bool ret = true;
	pugi::xml_node image = tileset_node.child("image");

	if (image == NULL)
	{
		LOG("Error parsing tileset xml file: Cannot find 'image' tag.");
		ret = false;
	}
	else
	{
		// Load Tileset image
		SString tmp("%s%s", folder.GetString(), image.attribute("source").as_string());
		set->texture = app->tex->Load(tmp.GetString());
	}

	return ret;
}

// Implement a function that loads a single layer layer
bool Map::LoadLayer(pugi::xml_node& node, MapLayer* layer)
{
	bool ret = true;

	// Load the attributes
	layer->name = node.attribute("name").as_string();
	layer->width = node.attribute("width").as_int();
	layer->height = node.attribute("height").as_int();
	
	

	// Call Load Propoerties
	LoadProperties(node, layer->properties);

	// Reserve the memory for the tile array
	layer->data = new uint[layer->width * layer->height];
	memset(layer->data, 0, layer->width * layer->height);

	// Iterate over all the tiles and assign the values
	pugi::xml_node tile;
	int i = 0;
	for (tile = node.child("data").child("tile"); tile && ret; tile = tile.next_sibling("tile"))
	{
		layer->data[i] = tile.attribute("gid").as_int();
		i++;
	}

	//LOG("%d", layer->properties.GetProperty<int>("Height"));
	layer->properties.GetProperty<int>("Height") == 1 ? layer->isHigh = true : layer->isHigh = false;
	
	return ret;
}

// Iterate all layers and load each of them
bool Map::LoadAllLayers(pugi::xml_node mapNode) {
	bool ret = true;
	for (pugi::xml_node layerNode = mapNode.child("layer"); layerNode && ret; layerNode = layerNode.next_sibling("layer"))
	{
		// Load the layer
		MapLayer* mapLayer = new MapLayer();
		ret = LoadLayer(layerNode, mapLayer);

		// add the layer to the map
		mapData.layers.add(mapLayer);
	}

	return ret;
}

// Load a group of properties from a node and fill a list with it
bool Map::LoadProperties(pugi::xml_node& node, Properties& properties)
{
	bool ret = false;
	pugi::xml_node data = node.child("properties");

	if (data != NULL) {

		for (pugi::xml_node propertieNode = node.child("properties").child("property"); propertieNode; propertieNode = propertieNode.next_sibling("property"))
		{
			Properties::Property* p = new Properties::Property();
			p->name = propertieNode.attribute("name").as_string();
			p->intValue = propertieNode.attribute("value").as_int();
			p->charValue = propertieNode.attribute("value").as_string();

			properties.list.add(p);
		}
	}
	
	return ret;
}


void Map::LoadCol() {

	if (mapLoaded == false) return;

	// Prepare the loop to draw all tilesets + DrawTexture()
	ListItem<MapLayer*>* mapLayerItem;
	mapLayerItem = mapData.layers.start;

	int i = 0;

	while (mapLayerItem != NULL) {
	
		const char* wallChar = static_cast<const char*>(mapLayerItem->data->properties.GetProperty<const char*>("Col"));
		if (wallChar != nullptr) {
			if (wallChar == std::string("wall")) {

				for (int x = 0; x < mapLayerItem->data->width; x++)
				{
					for (int y = 0; y < mapLayerItem->data->height; y++)
					{
						// Complete the col function
						int gid = mapLayerItem->data->Get(x, y);

						if (gid > 0) {

							// Obtain the tile set using GetTilesetFromTileId
							// now we always use the firt tileset in the list
							TileSet* tileset = mapData.tilesets.start->data;

							SDL_Rect r = tileset->GetTileRect(gid);
							iPoint pos = MapToWorld(x, y);

							mapWalls[i] = app->collisions->AddCollider({ pos.x, pos.y , r.w,  r.h }, Collider::Type::WALL, wallsEntity);
							i++;
						}
					}
				}
			}
		}

		//const char* colProperty = static_cast<const char*>(mapLayerItem->data->properties.GetPropertyChar("Col"));

		//if (colProperty != nullptr) {

		//	LOG("%s", colProperty);
		//	if (colProperty == std::string("wall"))
		//	{

		//		for (int x = 0; x < mapLayerItem->data->width; x++)
		//		{
		//			for (int y = 0; y < mapLayerItem->data->height; y++)
		//			{
		//				//Complete the draw function
		//				int gid = mapLayerItem->data->Get(x, y);

		//				if (gid > 0) {

		//					//L06: TODO 4: Obtain the tile set using GetTilesetFromTileId
		//					//now we always use the firt tileset in the list
		//					TileSet* tileset = mapData.tilesets.start->data;

		//					SDL_Rect r = tileset->GetTileRect(gid);
		//					iPoint pos = MapToWorld(x, y);

		//					mapWalls[i] = app->collisions->AddCollider({ pos.x, pos.y , r.w,  r.h }, Collider::Type::WALL, wallsEntity);
		//					i++;
		//				}
		//			}
		//		}

		//	}
		//}

		mapLayerItem = mapLayerItem->next;
	}
}

void Map::RemoveCol() {

	if (mapLoaded == false) return;

	// Prepare the loop to draw all tilesets + DrawTexture()
	ListItem<MapLayer*>* mapLayerItem;
	mapLayerItem = mapData.layers.start;

	int i = 0;

	while (mapLayerItem != NULL) {

		for (int x = 0; x < mapLayerItem->data->width; x++)
		{
			for (int y = 0; y < mapLayerItem->data->height; y++)
			{
				int gid = mapLayerItem->data->Get(x, y);

				if (gid > 0) {

					TileSet* tileset = mapData.tilesets.start->data;

					SDL_Rect r = tileset->GetTileRect(gid);
					iPoint pos = MapToWorld(x, y);

					if (mapWalls[i] != nullptr) {

						app->collisions->RemoveCollider(mapWalls[i]);
						
						i++;
					}

				}

			}
		}
		mapLayerItem = mapLayerItem->next;
	}

}
