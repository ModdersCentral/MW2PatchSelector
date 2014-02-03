/*
Made By: EmersonS35
Help From:
DarkHacker
EvilSperm


P0weT0ThePe0Ple
*/
#include <psl1ght/lv2.h>
#include <psl1ght/lv2/filesystem.h>

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <rsx/commands.h>
#include <rsx/nv40.h>
#include <rsx/reality.h>
#include <io/pad.h>
#include <sysmodule/sysmodule.h>
#include <sysutil/events.h>
#include <sysutil/video.h>
#include <rsx/gcm.h>
#include <rsx/reality.h>
#include <deadrsx/deadrsx.h>
#include <deadrsx/texture.h>
#include <deadrsx/nv_shaders.h>

#include "font.h"

int currentBuffer = 0;

int copy_state = 1;
int app_state = 1, btnPressed = 0; // used to switch screens
int background_color = COLOR_WHITE;

PadInfo padinfo;
PadData paddata;

u32 *tx_mem,sprite_offset,point_offset;
PngDatas sprite_image,point_image;


int menu_selection = 1, menu_amount = 6; // start menu selection on 1 and menu amout is total of menu items
void menu_gui() {

  drawText(sprite_offset, 32, "Patch 1", 50, 100);
  drawText(sprite_offset, 32, "Patch 2", 50, 150);
  drawText(sprite_offset, 32, "Patch 3", 50, 200);
  drawText(sprite_offset, 32, "Patch 4", 50, 250);
  drawText(sprite_offset, 32, "Clean Patch", 50, 300);
  drawText(sprite_offset, 32, "Exit Application", 50, 350);

  switch(menu_selection) {
  case 1:
  deadrsx_sprite(point_offset, 0, 93, 50, 50, 200, 100, 0, 0, 2, 1);
  break;
  case 2:
  deadrsx_sprite(point_offset, 0, 143, 50, 50, 200, 100, 0, 0, 2, 1);
  break;
  case 3:
  deadrsx_sprite(point_offset, 0, 193, 50, 50, 200, 100, 0, 0, 2, 1);
  break;
  case 4:
  deadrsx_sprite(point_offset, 0, 243, 50, 50, 200, 100, 0, 0, 2, 1);
  break;
  case 5:
  deadrsx_sprite(point_offset, 0, 293, 50, 50, 200, 100, 0, 0, 2, 1);
  break;
  case 6:
  deadrsx_sprite(point_offset, 0, 343, 50, 50, 200, 100, 0, 0, 2, 1);
  break;
  }
}


void drawFrame(int buffer, long frame) {

	realityViewportTranslate(context, 0.0, 0.0, 0.0, 0.0);
	realityViewportScale(context, 1.0, 1.0, 1.0, 0.0); 

        deadrsx_scale(); // scales screen to 847x511 - deadrsx library

	realityZControl(context, 0, 1, 1); // disable viewport culling
	realityBlendFunc(context,
		NV30_3D_BLEND_FUNC_SRC_RGB_SRC_ALPHA |
		NV30_3D_BLEND_FUNC_SRC_ALPHA_SRC_ALPHA,
		NV30_3D_BLEND_FUNC_DST_RGB_ONE_MINUS_SRC_ALPHA |
		NV30_3D_BLEND_FUNC_DST_ALPHA_ZERO);
	realityBlendEquation(context, NV40_3D_BLEND_EQUATION_RGB_FUNC_ADD |
		NV40_3D_BLEND_EQUATION_ALPHA_FUNC_ADD);
	realityBlendEnable(context, 1);
	realityViewport(context, res.width, res.height);
	setupRenderTarget(buffer);

	deadrsx_background(background_color);

	realitySetClearDepthValue(context, 0xffff);
	realityClearBuffers(context, REALITY_CLEAR_BUFFERS_COLOR_R |
				     REALITY_CLEAR_BUFFERS_COLOR_G |
				     REALITY_CLEAR_BUFFERS_COLOR_B |
				     NV30_3D_CLEAR_BUFFERS_COLOR_A |
				     NV30_3D_CLEAR_BUFFERS_STENCIL |
				     REALITY_CLEAR_BUFFERS_DEPTH);
	realityLoadVertexProgram_old(context, &nv40_vp);
	realityLoadFragmentProgram_old(context, &nv30_fp);

        drawText(sprite_offset, 32, "EmersonS35.wordpress.com", 425, 510);

        switch(app_state) {

        case 0:// screen while in-game xmb open
        background_color = COLOR_BLACK;
        break;

        case 1:
        background_color = COLOR_WHITE;
        deadrsx_sprite(point_offset, 0, 0, 847, 511, 200, 100, 2, 0, 3, 1); // gray alpha overlay
        drawText(sprite_offset, 32, "COD Patch Selector", 0, 0);
        drawText(sprite_offset, 20, "EmesonS35", 5,35);

        menu_gui(); // displays your gui
        
        break;

        case 2: 
        // empty screen can be used for anything 
        break;

        case 3:
        // menu selection one screen
        deadrsx_sprite(point_offset, 0, 0, 847, 511, 200, 100, 2, 0, 3, 1); // gray alpha overlay
        drawText(sprite_offset, 32, "You Copied the Patch in Slot 1", 150, 200);
        drawText(sprite_offset, 20, "Press X to Exit", 325, 235);
        drawText(sprite_offset, 20, "Press O to Return to Main Menu", 250, 255);
        break;
 
        case 4:
        // menu selection two screen
        deadrsx_sprite(point_offset, 0, 0, 847, 511, 200, 100, 2, 0, 3, 1); // gray alpha overlay
        drawText(sprite_offset, 32, "You Copied the Patch in Slot 2", 150, 200);
        drawText(sprite_offset, 20, "Press X to Exit", 325, 235);
        drawText(sprite_offset, 20, "Press O to Return to Main Menu", 250, 255);
        break;

        case 5:
        // menu selection one screen
        deadrsx_sprite(point_offset, 0, 0, 847, 511, 200, 100, 2, 0, 3, 1); // gray alpha overlay
        drawText(sprite_offset, 32, "You Copied the Patch in Slot 3", 150, 200);
        drawText(sprite_offset, 20, "Press X to Exit", 325, 235);
        drawText(sprite_offset, 20, "Press O to Return to Main Menu", 250, 255);
        break;
 
        case 6:
        // menu selection two screen
        deadrsx_sprite(point_offset, 0, 0, 847, 511, 200, 100, 2, 0, 3, 1); // gray alpha overlay
        drawText(sprite_offset, 32, "You Copied the Patch in Slot 4", 150, 200);
        drawText(sprite_offset, 20, "Press X to Exit", 325, 235);
        drawText(sprite_offset, 20, "Press O to Return to Main Menu", 250, 255);
        break;

        case 7:
        // menu selection one screen
        deadrsx_sprite(point_offset, 0, 0, 847, 511, 200, 100, 2, 0, 3, 1); // gray alpha overlay
        drawText(sprite_offset, 32, "You Now Have a Clean Patch", 150, 200);
        drawText(sprite_offset, 20, "Press X to Exit", 325, 235);
        drawText(sprite_offset, 20, "Press O to Return to Main Menu", 250, 255);
        break;

        }
}

static void eventHandle(u64 status, u64 param, void * userdata) {
    (void)param;
    (void)userdata;
	if(status == EVENT_REQUEST_EXITAPP){
	exit(0);
	}else if(status == EVENT_MENU_OPEN){
	app_state = 2;
	}else if(status == EVENT_MENU_CLOSE) {
        app_state = 1;
	}else{
	printf("Unhandled event: %08llX\n", (unsigned long long int)status);
	}
}


int copyfile(const char* fn_src, const char* fn_dst)
{
	u64 pos;
	u64 read;
	u64 write;

	Lv2FsFile src = -1;
	Lv2FsFile dst = -1;
	
	if(lv2FsOpen(fn_src, LV2_O_RDONLY, &src, 0, NULL, 0)!= 0 || lv2FsOpen(fn_dst, LV2_O_WRONLY|LV2_O_CREAT|LV2_O_TRUNC, &dst, 0, NULL, 0) != 0)
	{
		return -1;
	}

	lv2FsChmod(fn_dst, S_IFMT | 0777);

	lv2FsLSeek64(src, 0, 0, &pos);
	lv2FsLSeek64(dst, 0, 0, &pos);
	
	char buffer[32786];

	while(lv2FsRead(src, buffer, sizeof(buffer) - 1, &read) == 0 && read > 0)
	{
		lv2FsWrite(dst, buffer, read, &write);
	}

	if(read != 0)
	{
		return -1;
	}

	lv2FsClose(src);
	lv2FsClose(dst);

	return 0;
}


void appCleanup(){
	sysUnregisterCallback(EVENT_SLOT0);
}
void loading() {
   deadrsx_loadfile("/dev_hdd0/game/ES3500MW2/USRDIR/font.png", sprite_image, &sprite_offset);
   deadrsx_loadfile("/dev_hdd0/game/ES3500MW2/USRDIR/sprite.png", point_image, &point_offset);
}
void copy(){
	switch(copy_state){
	case 1:
	if(copyfile("/dev_hdd0/game/ES3500MW2/slot1/patch_mp.ff", "/dev_hdd0/game/BLUS30377/USRDIR/patch_mp.ff") == 0)
   	{
   		//yay
   	}
   	else
   	{
     		//nay
  	}
  	sleep(1);
	break;
	case 2:
	if(copyfile("/dev_hdd0/game/ES3500MW2/slot2/patch_mp.ff", "/dev_hdd0/game/BLUS30377/USRDIR/patch_mp.ff") == 0)
   	{
   		//yay
   	}
   	else
   	{
     		//nay
  	}
  	sleep(1);
	break;
	case 3:
	if(copyfile("/dev_hdd0/game/ES3500MW2/slot3/patch_mp.ff", "/dev_hdd0/game/BLUS30377/USRDIR/patch_mp.ff") == 0)
   	{
   		//yay
   	}
   	else
   	{
     		//nay
  	}
  	sleep(1);
	break;
	case 4:
	if(copyfile("/dev_hdd0/game/ES3500MW2/slot4/patch_mp.ff", "/dev_hdd0/game/BLUS30377/USRDIR/patch_mp.ff") == 0)
   	{
   		//yay
   	}
   	else
   	{
     		//nay
  	}
  	sleep(1);
	break;
	case 5:
	if(copyfile("/dev_hdd0/game/ES3500MW2/clean/patch_mp.ff", "/dev_hdd0/game/BLUS30377/USRDIR/patch_mp.ff") == 0)
   	{
   		//yay
   	}
   	else
   	{
     		//nay
  	}
  	sleep(1);
	break;
}
}
void ps3_pad() {

  ioPadGetInfo(&padinfo);
  for(int i=0; i<MAX_PADS; i++){
  if(padinfo.status[i]){
  ioPadGetData(i, &paddata);
  
      switch(app_state) {
      case 1:
	    if(paddata.BTN_CROSS){
	    switch(menu_selection) {
            case 1:
            app_state = 3;
      	    copy_state = 1;
	    copy();
            break;
            case 2:
            app_state = 4;
	    copy_state = 2;
	    copy();
            break;
            case 3:
            app_state = 5;
	    copy_state = 3;
	    copy();
            case 4:
            app_state = 6;
	    copy_state = 4;
	    copy();
            case 5:
            app_state = 7;
	    copy_state = 5;
	    copy();
            case 6:
            exit(1);
            break;
            }
	    }else if(paddata.BTN_UP) {

            if(btnPressed == 0) {
            btnPressed = 1;
            if(menu_selection > 1) {
            menu_selection -= 1;
            }
            }

            }else if(paddata.BTN_DOWN) {

            if(btnPressed == 0) {
            btnPressed = 1;
            if(menu_selection < menu_amount) {
            menu_selection += 1;
            }
            }

            }else if(paddata.BTN_LEFT) {

            }else if(paddata.BTN_RIGHT) {

            }else{
            btnPressed = 0;
            }

      break;
      case 3:
            if(paddata.BTN_CROSS){
	    sleep(1);
            exit(1);
	    }
            if(paddata.BTN_CIRCLE){
	    sleep(1);
            app_state = 1;
	    }
      break;
      case 4:
            if(paddata.BTN_CROSS){
	    sleep(1);
	    exit(1);
	    }
            if(paddata.BTN_CIRCLE){
	    sleep(1);
            app_state = 1;
	    }
      break;
      case 5:
            if(paddata.BTN_CROSS){
	    sleep(1);
            exit(1);
	    }
            if(paddata.BTN_CIRCLE){
	    sleep(1);
            app_state = 1;
	    }
      break;
      case 6:
            if(paddata.BTN_CROSS){
	    sleep(1);
	    exit(1);
	    }
            if(paddata.BTN_CIRCLE){
	    sleep(1);
            app_state = 1;
	    }
      break;
      case 7:
            if(paddata.BTN_CROSS){
	    sleep(1);
            exit(1);
	    }
            if(paddata.BTN_CIRCLE){
	    sleep(1);
            app_state = 1;
	    }
      break;
      }

  }		
 }
}
s32 main(s32 argc, const char* argv[])
{

	atexit(appCleanup);
	deadrsx_init();
	ioPadInit(7);
	sysRegisterCallback(EVENT_SLOT0, eventHandle, NULL);

	u32 *frag_mem = rsxMemAlign(256, 256);
	printf("frag_mem = 0x%08lx\n", (u64) frag_mem);
	realityInstallFragmentProgram_old(context, &nv30_fp, frag_mem);

        loading(); // where all the loading done xD

	long frame = 0; 

	while(1){
                ps3_pad(); // where all are controls are
		waitFlip(); // Wait for the last flip to finish, so we can draw to the old buffer
		drawFrame(currentBuffer, frame++); // Draw into the unused buffer
		flip(currentBuffer); // Flip buffer onto screen
		currentBuffer = !currentBuffer;
		sysCheckCallback();

	}
	
	return 0;
}

