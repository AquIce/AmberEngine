#ifndef __AQUICE_SDL3_WORLD_HPP__
#define __AQUICE_SDL3_WORLD_HPP__ 

#include <array>

#include "../utils/ColorCodes.h"

#define MAX_X_COORD 128
#define MAX_Y_COORD 64
#define MAX_Z_COORD 128

#define X_CHUNK_SIZE 8
#define Y_CHUNK_SIZE 8
#define Z_CHUNK_SIZE 8

typedef struct Block {
	RGBA color;
} Block;

typedef std::array<Block, MAX_X_COORD> ChunkBarBlocks;

typedef std::array<ChunkBarBlocks, MAX_Y_COORD> ChunkLayerBlocks;

typedef std::array<ChunkLayerBlocks, MAX_Z_COORD> ChunkBlocks;

typedef struct Chunk {
	ChunkBlocks blocks;
} Chunk;

typedef std::array<Chunk, MAX_X_COORD / X_CHUNK_SIZE> WorldChunkBar;

typedef std::array<WorldChunkBar, MAX_Y_COORD / Y_CHUNK_SIZE> WorldChunkLayer;

typedef std::array<WorldChunkLayer, MAX_Z_COORD / Z_CHUNK_SIZE> WorldChunks;

typedef struct World {
	WorldChunks chunks;
} World;

#endif