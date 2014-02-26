//////////
//
// /libsf/common/vvm_key_const.h
//
//////
// Version 0.70
// Copyright (c) 2012, 2014 by Rick C. Hodgin
//////
// Last update:
//     Feb.25.2014
//////
// Change log:
//     Feb.25.2014 - Development on 0.70 begins
//     Nov.07.2012 - 0.60 development begins
//     Oct.02.2012 - PBL v1.0 license included directly in source files.
//     Oct.02.2012 - Initial creation
//////
// See devhelp.txt.
//////
//
// This software is released as Liberty Software under a Repeat License, as governed
// by the Public Benefit License v1.0 or later (PBL).
//
// You are free to use, copy, modify and share this software.  However, it can only
// be released under the PBL version indicated, and every project must include a copy
// of the pbl.txt document for its version as is at http://www.libsf.org/licenses/.
//
// For additional information about this project, or to view the license, see:
//
//	  http://www.libsf.org/
//	  http://www.libsf.org/licenses/
//	  http://www.visual-freepro.org
//	  http://www.visual-freepro.org/blog/
//	  http://www.visual-freepro.org/forum/
//	  http://www.visual-freepro.org/wiki/
//	  http://www.visual-freepro.org/wiki/index.php/PBL
//	  http://www.visual-freepro.org/wiki/index.php/Repeat_License
//
// Thank you.  And may The Lord bless you richly as you lift up your life, your
// talents, your gifts, your praise, unto Him.  In Jesus' name I pray.  Amen.
//
//




//////////
// VVM known key definitions
//////
	#define	VVM_UNKNOWN							-1
	#define	VVM_LBUTTON							1
	#define	VVM_RBUTTON							2
	#define	VVM_CANCEL							3
	#define	VVM_MBUTTON							4
	#define	VVM_XBUTTON1						5
	#define	VVM_XBUTTON2						6
	#define	VVM_BACK							7
	#define	VVM_TAB								8
	#define	VVM_CLEAR							9
	#define	VVM_RETURN							10
	#define	VVM_SHIFT							11
	#define	VVM_CONTROL							12
	#define	VVM_MENU							13
	#define	VVM_PAUSE							14
	#define	VVM_CAPITAL							15
	#define	VVM_KANA							16
//	#define	VVM_
//	#define	VVM
	#define	VVM_JUNJA							19
	#define	VVM_FINAL							20
	#define	VVM_HANJA							21
//	#define	VVM_
	#define	VVM_ESCAPE							23
	#define	VVM_CONVERT							24
	#define	VVM_NONCONVERT						25
	#define	VVM_ACCEPT							26
	#define	VVM_MODECHANGE						27
	#define	VVM_SPACE							28
	#define	VVM_PRIOR							29
	#define	VVM_NEXT							30
	#define	VVM_END								31
	#define	VVM_HOME							32
	#define	VVM_LEFT							33
	#define	VVM_UP								34
	#define	VVM_RIGHT							35
	#define	VVM_DOWN							36
	#define	VVM_SELECT							37
	#define	VVM_PRINT							38
	#define	VVM_EXECUTE							39
	#define	VVM_SNAPSHOT						40
	#define	VVM_INSERT							41
	#define	VVM_DELETE							42
	#define	VVM_HELP							43
	#define	VVM_0								44
	#define	VVM_1								45
	#define	VVM_2								46
	#define	VVM_3								47
	#define	VVM_4								48
	#define	VVM_5								49
	#define	VVM_6								50
	#define	VVM_7								51
	#define	VVM_8								52
	#define	VVM_9								53
	#define	VVM_A								54
	#define	VVM_B								55
	#define	VVM_C								56
	#define	VVM_D								57
	#define	VVM_E								58
	#define	VVM_F								59
	#define	VVM_G								60
	#define	VVM_H								61
	#define	VVM_I								62
	#define	VVM_J								63
	#define	VVM_K								64
	#define	VVM_L								65
	#define	VVM_M								66
	#define	VVM_N								67
	#define	VVM_O								68
	#define	VVM_P								69
	#define	VVM_Q								70
	#define	VVM_R								71
	#define	VVM_S								72
	#define	VVM_T								73
	#define	VVM_U								74
	#define	VVM_V								75
	#define	VVM_W								76
	#define	VVM_X								77
	#define	VVM_Y								78
	#define	VVM_Z								79
	#define	VVM_LWIN							80
	#define	VVM_RWIN							81
	#define	VVM_APPS							82
	#define	VVM_SLEEP							83
	#define	VVM_NUMPAD0							84
	#define	VVM_NUMPAD1							85
	#define	VVM_NUMPAD2							86
	#define	VVM_NUMPAD3							87
	#define	VVM_NUMPAD4							88
	#define	VVM_NUMPAD5							89
	#define	VVM_NUMPAD6							90
	#define	VVM_NUMPAD7							91
	#define	VVM_NUMPAD8							92
	#define	VVM_NUMPAD9							93
	#define	VVM_MULTIPLY						94
	#define	VVM_ADD								95
	#define	VVM_SEPARATOR						96
	#define	VVM_SUBTRACT						97
	#define	VVM_DECIMAL							98
	#define	VVM_DIVIDE							99
	#define	VVM_F1								100
	#define	VVM_F2								101
	#define	VVM_F3								102
	#define	VVM_F4								103
	#define	VVM_F5								104
	#define	VVM_F6								105
	#define	VVM_F7								106
	#define	VVM_F8								107
	#define	VVM_F9								108
	#define	VVM_F10								109
	#define	VVM_F11								110
	#define	VVM_F12								111
	#define	VVM_F13								112
	#define	VVM_F14								113
	#define	VVM_F15								114
	#define	VVM_F16								115
	#define	VVM_F17								116
	#define	VVM_F18								117
	#define	VVM_F19								118
	#define	VVM_F20								119
	#define	VVM_F21								120
	#define	VVM_F22								121
	#define	VVM_F23								122
	#define	VVM_F24								123
	#define	VVM_NUMLOCK							124
	#define	VVM_SCROLL							125
	#define	VVM_LSHIFT							126
	#define	VVM_RSHIFT							127
	#define	VVM_LCONTROL						128
	#define	VVM_RCONTROL						129
	#define	VVM_LMENU							130
	#define	VVM_RMENU							131
	#define	VVM_BROWSER_BACK					132
	#define	VVM_BROWSER_FORWARD					133
	#define	VVM_BROWSER_REFRESH					134
	#define	VVM_BROWSER_STOP					135
	#define	VVM_BROWSER_SEARCH					136
	#define	VVM_BROWSER_FAVORITES				137
	#define	VVM_BROWSER_HOME					138
	#define	VVM_VOLUME_MUTE						139
	#define	VVM_VOLUME_DOWN						140
	#define	VVM_VOLUME_UP						141
	#define	VVM_MEDIA_NEXT_TRACK				142
	#define	VVM_MEDIA_PREV_TRACK				143
	#define	VVM_MEDIA_STOP						144
	#define	VVM_MEDIA_PLAY_PAUSE				145
	#define	VVM_LAUNCH_MAIL						146
	#define	VVM_LAUNCH_MEDIA_SELECT				147
	#define	VVM_LAUNCH_APP1						148
	#define	VVM_LAUNCH_APP2						149
	#define	VVM_OEM_1							150
	#define	VVM_OEM_PLUS						151
	#define	VVM_OEM_COMMA						152
	#define	VVM_OEM_MINUS						153
	#define	VVM_OEM_PERIOD						154
	#define	VVM_OEM_2							155
	#define	VVM_OEM_3							156
	#define	VVM_OEM_4							157
	#define	VVM_OEM_5							158
	#define	VVM_OEM_6							159
	#define	VVM_OEM_7							160
	#define	VVM_OEM_8							161
	#define	VVM_OEM_102							162
	#define	VVM_PROCESSKEY						163
	#define	VVM_PACKET							164
	#define	VVM_ATTN							165
	#define	VVM_CRSEL							166
	#define	VVM_EXSEL							167
	#define	VVM_EREOF							168
	#define	VVM_PLAY							169
	#define	VVM_ZOOM							170
	#define	VVM_NONAME							171
	#define	VVM_PA1								172
	#define	VVM_OEM_CLEAR						173
