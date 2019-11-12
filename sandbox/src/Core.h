#pragma once
// Folders
#define GAME_RESOURCES "res/"
#define GAME_SHADERS GAME_RESOURCES"shaders/"
#define GAME_TEXTURES GAME_RESOURCES"textures/"
#define GAME_MODELS GAME_RESOURCES"models/"

// General Configs
#define CONF_FPS_SMOOTHING 0.9f

// Tarrain
#define CONF_TERRAIN_SCALE 50.0f
#define CONF_TERRAIN_WIDTH 100.0f
#define CONF_TERRAIN_LENGTH 100.0f
#define SHADER_TERRAIN GAME_SHADERS"Terrain"
#define TEXTURE_TERRAIN_COLORMAP_ID 0
#define TEXTURE_TERRAIN_COLORMAP GAME_TEXTURES"tutorial-unity-3d-mapper/texture.png"
#define TEXTURE_TERRAIN_HEIGHTMAP_ID 1
#define TEXTURE_TERRAIN_HEIGHTMAP GAME_TEXTURES"tutorial-unity-3d-mapper/heightmap.png"
#define TEXTURE_TERRAIN_TEXTURE_ID 2
#define TEXTURE_TERRAIN_TEXTURE GAME_TEXTURES"terrain/dirt01d.tga"
#define TEXTURE_TERRAIN_TEXTURE_NORMALS_ID 3
#define TEXTURE_TERRAIN_TEXTURE_NORMALS GAME_TEXTURES"terrain/dirt01n.tga"

// Shaders
#define SHADER_SQUARE_GRID GAME_SHADERS"SquareGrid"
#define SHADER_TEXTURE_SQUARE GAME_SHADERS"TextureSquare"
#define SHADER_MODEL_LOADER GAME_SHADERS"MeshLoad"

// Textures
#define TEXTURE_FLOGO_ID 4
#define TEXTURE_FLOGO GAME_TEXTURES"flower_logo.png"
#define TEXTURE_CRATE_ID 5
#define TEXTURE_CRATE GAME_TEXTURES"container.jpg"

#define TEXTURE_SKYBOX GAME_TEXTURES"skybox/Sunset" 

// Models
#define MODEL_TEAPOT GAME_MODELS"Teapot.obj"
#define MODEL_CUBE GAME_MODELS"Cube.obj"
#define MODEL_DINOSAUR GAME_MODELS"Dinosaur.obj"
#define MODEL_HELICOPTER GAME_MODELS"Helicopter.obj"
