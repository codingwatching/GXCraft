#pragma once
#include "DisplayList.hpp"

#define nRenderChunks 256

typedef struct {
	bool active;
	bool update;
	unsigned short x, z;
	DisplayList *list;
	DisplayList *blendlist;
} renderchunk;

class Chunked {
	private:
		static renderchunk *renderchunks[nRenderChunks];

		static void deallocall();
		static int getchunkfromchunkpos(short unsigned int, short unsigned int);
		static int chunk_cmp(const void*, const void*);
		static void renderNewChunk(signed short, signed short);
	public:
		static void init();
		static void markchunkforupdate(unsigned short, unsigned short);
		static bool rerenderChunkUpdates(bool);
		static void rerenderChunk(signed short, signed short, bool);
		static void refresh(int);
		static void render();
		static void getfifousage(int*, int*);
};
