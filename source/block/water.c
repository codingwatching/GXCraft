#include <grrlib.h>

#include "../main.h"
#include "../block.h"
#include "../render.h"
#include "../textures/block_water.h"
#include "water.h"

GRRLIB_texImg *tex_water;

inline void drawWaterBlock(int xPos, int yPos, int zPos, GRRLIB_texImg *tex);

static void render(int xPos, int yPos, int zPos, unsigned char pass) {
	if (pass == 0) return;
	drawWaterBlock(xPos, yPos, zPos, tex_water);
}

void water_init() {
	blockEntry entry;
	entry.renderBlock = render;
	registerBlock(8, entry);
	tex_water = GRRLIB_LoadTexture(block_water);
}

void water_clean() {
	GRRLIB_FreeTexture(tex_water);
}

bool testWaterFace(unsigned char face) {
	return face == 0 || face == 6 || face == 37 || face == 38 || face == 39 || face == 40;
}

inline void drawWaterBlock(int xPos, int yPos, int zPos, GRRLIB_texImg *tex) {

	bool drawBack  = zPos >= worldZ-1 || testWaterFace(theWorld[yPos][xPos][zPos + 1]);
	bool drawFront = zPos <= 0        || testWaterFace(theWorld[yPos][xPos][zPos - 1]);
	bool drawRight = xPos >= worldX-1 || testWaterFace(theWorld[yPos][xPos + 1][zPos]);
	bool drawLeft  = xPos <= 0        || testWaterFace(theWorld[yPos][xPos - 1][zPos]);
	bool drawTop   = yPos >= worldY-1 || testWaterFace(theWorld[yPos + 1][xPos][zPos]);
	bool drawBott  = yPos > 0         && testWaterFace(theWorld[yPos - 1][xPos][zPos]);

	int size = 0;
	if (drawBack)  size += 4;
	if (drawFront) size += 4;
	if (drawRight) size += 4;
	if (drawLeft)  size += 4;
	if (drawTop)   size += 4;
	if (drawBott)  size += 4;
	
	if (size == 0) return;
	
	if (lastTex != tex)
		GRRLIB_SetTexture(tex, 0);
	lastTex = tex;

	GX_Begin(GX_QUADS, GX_VTXFMT1, size);

	if (drawBack) {
		GX_Position3s16(xPos, 1+yPos, 1+zPos);
		GX_Color1u16(0xCCCF);
		GX_TexCoord2u8(0,0);
		GX_Position3s16( 1+xPos, 1+yPos, 1+zPos);
		GX_Color1u16(0xCCCF);
		GX_TexCoord2u8(1,0);
		GX_Position3s16( 1+xPos,yPos, 1+zPos);
		GX_Color1u16(0xCCCF);
		GX_TexCoord2u8(1,1);
		GX_Position3s16(xPos,yPos, 1+zPos);
		GX_Color1u16(0xCCCF);
		GX_TexCoord2u8(0,1);
	}

	if (drawFront) {
		GX_Position3s16( 1+xPos, 1+yPos,zPos);
		GX_Color1u16(0xCCCF);
		GX_TexCoord2u8(0,0);
		GX_Position3s16(xPos, 1+yPos,zPos);
		GX_Color1u16(0xCCCF);
		GX_TexCoord2u8(1,0);
		GX_Position3s16(xPos,yPos,zPos);
		GX_Color1u16(0xCCCF);
		GX_TexCoord2u8(1,1);
		GX_Position3s16( 1+xPos,yPos,zPos);
		GX_Color1u16(0xCCCF);
		GX_TexCoord2u8(0,1);
	}

	if (drawRight) {
		GX_Position3s16( 1+xPos, 1+yPos, 1+zPos);
		GX_Color1u16(0x999F);
		GX_TexCoord2u8(0,0);
		GX_Position3s16( 1+xPos, 1+yPos,zPos);
		GX_Color1u16(0x999F);
		GX_TexCoord2u8(1,0);
		GX_Position3s16( 1+xPos,yPos,zPos);
		GX_Color1u16(0x999F);
		GX_TexCoord2u8(1,1);
		GX_Position3s16( 1+xPos,yPos, 1+zPos);
		GX_Color1u16(0x999F);
		GX_TexCoord2u8(0,1);
	}

	if (drawLeft) {
		GX_Position3s16(xPos, 1+yPos,zPos);
		GX_Color1u16(0x999F);
		GX_TexCoord2u8(0,0);
		GX_Position3s16(xPos, 1+yPos, 1+zPos);
		GX_Color1u16(0x999F);
		GX_TexCoord2u8(1,0);
		GX_Position3s16(xPos,yPos, 1+zPos);
		GX_Color1u16(0x999F);
		GX_TexCoord2u8(1,1);
		GX_Position3s16(xPos,yPos,zPos);
		GX_Color1u16(0x999F);
		GX_TexCoord2u8(0,1);
	}

	if (drawTop) {
		GX_Position3s16(xPos, 1+yPos,zPos);
		GX_Color1u16(0xFFFF);
		GX_TexCoord2u8(0,0);
		GX_Position3s16( 1+xPos, 1+yPos,zPos);
		GX_Color1u16(0xFFFF);
		GX_TexCoord2u8(1,0);
		GX_Position3s16( 1+xPos, 1+yPos, 1+zPos);
		GX_Color1u16(0xFFFF);
		GX_TexCoord2u8(1,1);
		GX_Position3s16(xPos, 1+yPos, 1+zPos);
		GX_Color1u16(0xFFFF);
		GX_TexCoord2u8(0,1);
	}

	if (drawBott) {
		GX_Position3s16( 1+xPos,yPos,zPos);
		GX_Color1u16(0x555F);
		GX_TexCoord2u8(0,0);
		GX_Position3s16(xPos,yPos,zPos);
		GX_Color1u16(0x555F);
		GX_TexCoord2u8(1,0);
		GX_Position3s16(xPos,yPos, 1+zPos);
		GX_Color1u16(0x555F);
		GX_TexCoord2u8(1,1);
		GX_Position3s16( 1+xPos,yPos, 1+zPos);
		GX_Color1u16(0x555F);
		GX_TexCoord2u8(0,1);
	}

	GX_End();
}
