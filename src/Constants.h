#ifndef CONSTANTS_H
#define CONSTANTS_H

enum ControllerType {UNSET, XB1, PS4, SNES, NES, GEN, SMS, ATARI_2600, ATARI_7800};

const std::string CONTROLLERNAME[] = {
	"UNSET",
	"XB1",
	"PS4",
	"SNES",
	"NES",
	"GEN",
	"SMS",
	"ATARI_2600",
	"ATARI_7800"
};

//Xbox One Mapping
#define XB1_BTN_A		0x130
#define XB1_BTN_B		0x131
#define XB1_BTN_X		0x133
#define XB1_BTN_Y		0x134
#define XB1_BTN_LB		0x136
#define XB1_BTN_RB		0x137
#define XB1_BTN_SELECT		0x9E
#define XB1_BTN_START		0x13B
#define XB1_BTN_LS		0x13D
#define XB1_BTN_RS		0x13E
#define XB1_BTN_HOME		0xAC
#define XB1_LEFT_Y_AXIS		0x01
#define XB1_LEFT_X_AXIS		0x00
#define XB1_RIGHT_Y_AXIS	0x05
#define XB1_RIGHT_X_AXIS	0x02
#define XB1_RIGHT_TRIGGER   	0x09
#define XB1_LEFT_TRIGGER   	0x0A
#define XB1_DPAD_X		0x10
#define XB1_DPAD_Y		0x11

//Xbox One Alternate Mapping (reconnected controller)
/*
#define XB1_BTN_A		0x130
#define XB1_BTN_B		0x131
#define XB1_BTN_X		0x132
#define XB1_BTN_Y		0x133
#define XB1_BTN_LB		0x134
#define XB1_BTN_RB		0x135
#define XB1_BTN_SELECT		0x136
#define XB1_BTN_START		0x137
#define XB1_BTN_LS		0x138
#define XB1_BTN_RS		0x139
#define XB1_BTN_HOME		0xAC
#define XB1_RIGHT_TRIGGER	0x09
#define XB1_LEFT_TRIGGER    	0x0A
*/

//PS4 Mappings
#define PS4_BTN_CROSS		0x130
#define PS4_BTN_CIRCLE		0x131
#define PS4_BTN_SQUARE		0x134
#define PS4_BTN_TRIANGLE	0x133
#define PS4_BTN_L1		0x136
#define PS4_BTN_R1		0x137
#define PS4_BTN_SELECT		0x13A
#define PS4_BTN_START		0x13B
#define PS4_BTN_LS		0x13D
#define PS4_BTN_RS		0x13E
#define PS4_BTN_HOME		0x13C
#define PS4_LEFT_Y_AXIS		0x01
#define PS4_LEFT_X_AXIS		0x00
#define PS4_RIGHT_Y_AXIS	0x04
#define PS4_RIGHT_X_AXIS	0x03
#define PS4_RIGHT_TRIGGER   	0x05
#define PS4_LEFT_TRIGGER    	0x02
#define PS4_DPAD_X		0x10
#define PS4_DPAD_Y		0x11

#endif
