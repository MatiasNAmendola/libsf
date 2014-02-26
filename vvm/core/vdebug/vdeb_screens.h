//////////
//
// /libsf/vvm/vdebug/vdebug/vdeb_screens.h
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
//     Oct.21.2012 - PBL v1.0 license included directly in source files.
//     Oct.21.2012 - Initial creation
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
//     http://www.libsf.org/
//     http://www.libsf.org/licenses/
//     http://www.visual-freepro.org
//     http://www.visual-freepro.org/blog/
//     http://www.visual-freepro.org/forum/
//     http://www.visual-freepro.org/wiki/
//     http://www.visual-freepro.org/wiki/index.php/PBL
//     http://www.visual-freepro.org/wiki/index.php/Repeat_License
//
// Thank you.  And may The Lord bless you richly as you lift up your life, your
// talents, your gifts, your praise, unto Him.  In Jesus' name I pray.  Amen.
//
//




//////////
// Ready window
//////
	s8	gcReady01[]					= "ɘ���������������������������Ready Window���������������������������͚�";
	s8	gcReady02[]					= "�             �                                                       �";
	s8	gcReady03[]					= "�             �                                                       �";
	s8	gcReady04[]					= "�             �                                                       �";
	s8	gcReady05[]					= "�             �                                                       �";
	s8	gcReady06[]					= "�             �                                                       �";
	s8	gcReady07[]					= "�             �                                                       �";
	s8	gcReady08[]					= "�             �                                                       �";
	s8	gcReady09[]					= "�             �                                                       �";
	s8	gcReady10[]					= "�             �                                                       �";
	s8	gcReady11[]					= "�             �                                                       �";
	s8	gcReady12[]					= "�             �                                                       �";
	s8	gcReady13[]					= "�             �                                                       �";
	s8	gcReady14[]					= "�����������������������������������������������������������������������";
	s8	gcReady15[]					= "�             �                                                       �";
	s8	gcReady16[]					= "�             �                                                       �";
	s8	gcReady17[]					= "�             �                                                       �";
	s8	gcReady18[]					= "���������������������������������������������������������������������ʼ";




//////////
// Registers
//////
	s8	gcProgramRegisters01[]			= "���������Registers������͚��";
	s8	gcProgramRegisters02[]			= "   SNIP ��������:Xxx       �";
	s8	gcProgramRegisters03[]			= "     IP ��������:��������  �";
	s8	gcProgramRegisters04[]			= "     SP ��������:��������  �";
	s8	gcProgramRegisters05[]			= "     BP ��������:��������  �";
	s8	gcProgramRegisters06[]			= "   PRED ��������:��������  �";
	s8	gcProgramRegisters07[]			= "           COUNT ��        �";
	s8	gcProgramRegisters08[]			= " EXSNIP ��������:Xxx       �";
	s8	gcProgramRegisters09[]			= "  ERROR ��������:��������  �";
	s8	gcProgramRegisters10[]			= "                           �";
	s8	gcProgramRegisters11[]			= "  FLAGS                    �";
	s8	gcProgramRegisters12[]			= "    ����-����-����-����    �";
	s8	gcProgramRegisters13[]			= "    ����-����-����-����    �";
	s8	gcProgramRegisters14[]			= "    ����-����-����-����    �";
	s8	gcProgramRegisters15[]			= "    ����-����-����-����    �";
	s8	gcProgramRegisters16[]			= "      ov? cy? ab? app?     �";
	s8	gcProgramRegisters17[]			= "      un? eq? be?          �";

	s8	gcIntegerRegisters01[]			= "����������Integer�������͚��";
	s8	gcIntegerRegisters02[]			= "  A  ����:����:����:��:��  �";
	s8	gcIntegerRegisters03[]			= "  B  ����:����:����:��:��  �";
	s8	gcIntegerRegisters04[]			= "  C  ����:����:����:��:��  �";
	s8	gcIntegerRegisters05[]			= "  D  ����:����:����:��:��  �";
	s8	gcIntegerRegisters06[]			= "  E  ����:����:����:��:��  �";
	s8	gcIntegerRegisters07[]			= "  F  ����:����:����:��:��  �";
	s8	gcIntegerRegisters08[]			= "  G  ����:����:����:��:��  �";
	s8	gcIntegerRegisters09[]			= "  H  ����:����:����:��:��  �";
	s8	gcIntegerRegisters10[]			= "  I  ����:����:����:��:��  �";
	s8	gcIntegerRegisters11[]			= "  J  ����:����:����:��:��  �";
	s8	gcIntegerRegisters12[]			= "  K  ����:����:����:��:��  �";
	s8	gcIntegerRegisters13[]			= "  L  ����:����:����:��:��  �";
	s8	gcIntegerRegisters14[]			= "  M  ����:����:����:��:��  �";
	s8	gcIntegerRegisters15[]			= "  N  ����:����:����:��:��  �";
	s8	gcIntegerRegisters16[]			= "  O  ����:����:����:��:��  �";
	s8	gcIntegerRegisters17[]			= "  P  ����:����:����:��:��  �";

	s8	gcFloatingPointRegisters01[]	= "������Floating Point�����͚�";
	s8	gcFloatingPointRegisters02[]	= "  FA +�.�����������������  �";
	s8	gcFloatingPointRegisters03[]	= "  FB +�.�����������������  �";
	s8	gcFloatingPointRegisters04[]	= "  FC +�.�����������������  �";
	s8	gcFloatingPointRegisters05[]	= "  FD +�.�����������������  �";
	s8	gcFloatingPointRegisters06[]	= "  FE +�.�����������������  �";
	s8	gcFloatingPointRegisters07[]	= "  FF +�.�����������������  �";
	s8	gcFloatingPointRegisters08[]	= "  FG +�.�����������������  �";
	s8	gcFloatingPointRegisters09[]	= "  FH +�.�����������������  �";
	s8	gcFloatingPointRegisters10[]	= "  FI +�.�����������������  �";
	s8	gcFloatingPointRegisters11[]	= "  FJ +�.�����������������  �";
	s8	gcFloatingPointRegisters12[]	= "  FK +�.�����������������  �";
	s8	gcFloatingPointRegisters13[]	= "  FL +�.�����������������  �";
	s8	gcFloatingPointRegisters14[]	= "  FM +�.�����������������  �";
	s8	gcFloatingPointRegisters15[]	= "  FN +�.�����������������  �";
	s8	gcFloatingPointRegisters16[]	= "  FO +�.�����������������  �";
	s8	gcFloatingPointRegisters17[]	= "  FP +�.�����������������  �";




//////////
// Stack
//////
	s8	gcStack01[]					= "�����������Stack����������͚�";
	s8	gcStack02[]					= " �������� ��������:�������� �";
	s8	gcStack03[]					= " �������� ��������:�������� �";
	s8	gcStack04[]					= " �������� ��������:�������� �";
	s8	gcStack05[]					= " �������� ��������:�������� �";
	s8	gcStack06[]					= " �������� ��������:�������� �";
	s8	gcStack07[]					= " �������� ��������:�������� �";
	s8	gcStack08[]					= " �������� ��������:�������� �";
	s8	gcStack09[]					= " �������� ��������:�������� �";
	s8	gcStack10[]					= " �������� ��������:�������� �";
	s8	gcStack11[]					= " �������� ��������:�������� �";
	s8	gcStack12[]					= " �������� ��������:�������� �";
	s8	gcStack13[]					= " �������� ��������:�������� �";
	s8	gcStack14[]					= " �������� ��������:�������� �";
	s8	gcStack15[]					= " �������� ��������:�������� �";
	s8	gcStack16[]					= " �������� ��������:�������� �";
	s8	gcStack17[]					= " �������� ��������:�������� �";




//////////
// Watch Window
//////
	s8	gcWatch01[]					= "����������������������������Watch Window���������������������������͚�";
	s8	gcWatch02[]					= "             �                                                       �";
	s8	gcWatch03[]					= "             �                                                       �";
	s8	gcWatch04[]					= "             �                                                       �";
	s8	gcWatch05[]					= "             �                                                       �";
	s8	gcWatch06[]					= "             �                                                       �";
	s8	gcWatch07[]					= "             �                                                       �";
	s8	gcWatch08[]					= "             �                                                       �";
	s8	gcWatch09[]					= "             �                                                       �";
	s8	gcWatch10[]					= "             �                                                       �";
	s8	gcWatch11[]					= "             �                                                       �";
	s8	gcWatch12[]					= "             �                                                       �";
	s8	gcWatch13[]					= "             �                                                       �";
	s8	gcWatch14[]					= "             �                                                       �";
	s8	gcWatch15[]					= "             �                                                       �";
	s8	gcWatch16[]					= "             �                                                       �";
	s8	gcWatch17[]					= "             �                                                       �";




//////////
// Hover Window
//////
	s8	gcHover01[]					= "ɘ�����������������Hover Window����������������͚�";
	s8	gcHover02[]					= "�             �                                  �";
	s8	gcHover03[]					= "�             �                                  �";
	s8	gcHover04[]					= "�             �                                  �";
	s8	gcHover05[]					= "�             �                                  �";
	s8	gcHover06[]					= "�             �                                  �";
	s8	gcHover07[]					= "�             �                                  �";
	s8	gcHover08[]					= "�             �                                  �";
	s8	gcHover09[]					= "�             �                                  �";
	s8	gcHover10[]					= "�             �                                  �";
	s8	gcHover11[]					= "�             �                                  �";
	s8	gcHover12[]					= "�             �                                  �";
	s8	gcHover13[]					= "�             �                                  �";
	s8	gcHover14[]					= "�             �                                  �";
	s8	gcHover15[]					= "�             �                                  �";
	s8	gcHover16[]					= "�             �                                  �";
	s8	gcHover17[]					= "�             �                                  �";
	s8	gcHover18[]					= "������������������������������������������������ʼ";




//////////
// Locals
//////
	s8	gcLocals01[]				= "ɘ��������������������Locals�������������������͚�";
	s8	gcLocals02[]				= "�             �    �                             �";
	s8	gcLocals03[]				= "�             �    �                             �";
	s8	gcLocals04[]				= "�             �    �                             �";
	s8	gcLocals05[]				= "�             �    �                             �";
	s8	gcLocals06[]				= "�             �    �                             �";
	s8	gcLocals07[]				= "�             �    �                             �";
	s8	gcLocals08[]				= "�             �    �                             �";
	s8	gcLocals09[]				= "�             �    �                             �";
	s8	gcLocals10[]				= "�             �    �                             �";
	s8	gcLocals11[]				= "�             �    �                             �";
	s8	gcLocals12[]				= "�             �    �                             �";
	s8	gcLocals13[]				= "�             �    �                             �";
	s8	gcLocals14[]				= "�             �    �                             �";
	s8	gcLocals15[]				= "�             �    �                             �";
	s8	gcLocals16[]				= "�             �    �                             �";
	s8	gcLocals17[]				= "�             �    �                             �";
	s8	gcLocals18[]				= "������������������������������������������������ʼ";




//////////
// Autos
//////
	s8	gcAutos01[]					= "ɘ���������������������Autos�������������������͚�";
	s8	gcAutos02[]					= "�             �    �                             �";
	s8	gcAutos03[]					= "�             �    �                             �";
	s8	gcAutos04[]					= "�             �    �                             �";
	s8	gcAutos05[]					= "�             �    �                             �";
	s8	gcAutos06[]					= "�             �    �                             �";
	s8	gcAutos07[]					= "�             �    �                             �";
	s8	gcAutos08[]					= "�             �    �                             �";
	s8	gcAutos09[]					= "�             �    �                             �";
	s8	gcAutos10[]					= "�             �    �                             �";
	s8	gcAutos11[]					= "�             �    �                             �";
	s8	gcAutos12[]					= "�             �    �                             �";
	s8	gcAutos13[]					= "�             �    �                             �";
	s8	gcAutos14[]					= "�             �    �                             �";
	s8	gcAutos15[]					= "�             �    �                             �";
	s8	gcAutos16[]					= "�             �    �                             �";
	s8	gcAutos17[]					= "�             �    �                             �";
	s8	gcAutos18[]					= "������������������������������������������������ʼ";




//////////
// Timers
//////
	s8	gcTimers01[]				= "ɘ���������������������Timers�������������������͚�";
	s8	gcTimers02[]				= "�         �     �     �                          �";
	s8	gcTimers03[]				= "�         �     �     �                          �";
	s8	gcTimers04[]				= "�         �     �     �                          �";
	s8	gcTimers05[]				= "�         �     �     �                          �";
	s8	gcTimers06[]				= "�         �     �     �                          �";
	s8	gcTimers07[]				= "�         �     �     �                          �";
	s8	gcTimers08[]				= "�         �     �     �                          �";
	s8	gcTimers09[]				= "�         �     �     �                          �";
	s8	gcTimers10[]				= "�         �     �     �                          �";
	s8	gcTimers11[]				= "�         �     �     �                          �";
	s8	gcTimers12[]				= "�         �     �     �                          �";
	s8	gcTimers13[]				= "�         �     �     �                          �";
	s8	gcTimers14[]				= "�         �     �     �                          �";
	s8	gcTimers15[]				= "�         �     �     �                          �";
	s8	gcTimers16[]				= "�         �     �     �                          �";
	s8	gcTimers17[]				= "�         �     �     �                          �";
	s8	gcTimers18[]				= "������������������������������������������������ʼ";




//////////
// Memory Window
//////
	s8	gcMemory01[]				= "ɘ����������������������Memory ���������������������͚�";
	s8	gcMemory02[]				= "�00000���:��:��:��:��:��:��:��:��:��:��:��:��:��:��:���";
	s8	gcMemory03[]				= "�00000���:��:��:��:��:��:��:��:��:��:��:��:��:��:��:���";
	s8	gcMemory04[]				= "�00000���:��:��:��:��:��:��:��:��:��:��:��:��:��:��:���";
	s8	gcMemory05[]				= "�00000���:��:��:��:��:��:��:��:��:��:��:��:��:��:��:���";
	s8	gcMemory06[]				= "�00000���:��:��:��:��:��:��:��:��:��:��:��:��:��:��:���";
	s8	gcMemory07[]				= "�00000���:��:��:��:��:��:��:��:��:��:��:��:��:��:��:���";
	s8	gcMemory08[]				= "�00000���:��:��:��:��:��:��:��:��:��:��:��:��:��:��:���";
	s8	gcMemory09[]				= "�00000���:��:��:��:��:��:��:��:��:��:��:��:��:��:��:���";
	s8	gcMemory10[]				= "�00000���:��:��:��:��:��:��:��:��:��:��:��:��:��:��:���";
	s8	gcMemory11[]				= "�00000���:��:��:��:��:��:��:��:��:��:��:��:��:��:��:���";
	s8	gcMemory12[]				= "�00000���:��:��:��:��:��:��:��:��:��:��:��:��:��:��:���";
	s8	gcMemory13[]				= "�00000���:��:��:��:��:��:��:��:��:��:��:��:��:��:��:���";
	s8	gcMemory14[]				= "�00000���:��:��:��:��:��:��:��:��:��:��:��:��:��:��:���";
	s8	gcMemory15[]				= "�00000���:��:��:��:��:��:��:��:��:��:��:��:��:��:��:���";
	s8	gcMemory16[]				= "�00000���:��:��:��:��:��:��:��:��:��:��:��:��:��:��:���";
	s8	gcMemory17[]				= "�00000���:��:��:��:��:��:��:��:��:��:��:��:��:��:��:���";
	s8	gcMemory18[]				= "�����������������������������������������������������ʼ";




//////////
// Programs
//////
	s8	gcPrograms01[]				= "ɘ�������������������Programs������������������͚�";
	s8	gcPrograms02[]				= "�             �    �                             �";
	s8	gcPrograms03[]				= "�             �    �                             �";
	s8	gcPrograms04[]				= "�             �    �                             �";
	s8	gcPrograms05[]				= "�             �    �                             �";
	s8	gcPrograms06[]				= "�             �    �                             �";
	s8	gcPrograms07[]				= "�             �    �                             �";
	s8	gcPrograms08[]				= "�             �    �                             �";
	s8	gcPrograms09[]				= "�             �    �                             �";
	s8	gcPrograms10[]				= "�             �    �                             �";
	s8	gcPrograms11[]				= "�             �    �                             �";
	s8	gcPrograms12[]				= "�             �    �                             �";
	s8	gcPrograms13[]				= "�             �    �                             �";
	s8	gcPrograms14[]				= "�             �    �                             �";
	s8	gcPrograms15[]				= "�             �    �                             �";
	s8	gcPrograms16[]				= "�             �    �                             �";
	s8	gcPrograms17[]				= "�             �    �                             �";
	s8	gcPrograms18[]				= "������������������������������������������������ʼ";




//////////
// Threads
//////
	s8	gcThreads01[]				= "ɘ��������������������Threads������������������͚�";
	s8	gcThreads02[]				= "�             �    �                             �";
	s8	gcThreads03[]				= "�             �    �                             �";
	s8	gcThreads04[]				= "�             �    �                             �";
	s8	gcThreads05[]				= "�             �    �                             �";
	s8	gcThreads06[]				= "�             �    �                             �";
	s8	gcThreads07[]				= "�             �    �                             �";
	s8	gcThreads08[]				= "�             �    �                             �";
	s8	gcThreads09[]				= "�             �    �                             �";
	s8	gcThreads10[]				= "�             �    �                             �";
	s8	gcThreads11[]				= "�             �    �                             �";
	s8	gcThreads12[]				= "�             �    �                             �";
	s8	gcThreads13[]				= "�             �    �                             �";
	s8	gcThreads14[]				= "�             �    �                             �";
	s8	gcThreads15[]				= "�             �    �                             �";
	s8	gcThreads16[]				= "�             �    �                             �";
	s8	gcThreads17[]				= "�             �    �                             �";
	s8	gcThreads18[]				= "������������������������������������������������ʼ";




//////////
// Ascii chart
//////
	s8 gcAsciiChart01[]				= "ɘ���Ascii Chart��͚�";
	s8 gcAsciiChart02[]				= "�  0123456789ABCDEF �";
	s8 gcAsciiChart03[]				= "� 0                 �";
	s8 gcAsciiChart04[]				= "� 1                 �";
	s8 gcAsciiChart05[]				= "� 2                 �";
	s8 gcAsciiChart06[]				= "� 3                 �";
	s8 gcAsciiChart07[]				= "� 4                 �";
	s8 gcAsciiChart08[]				= "� 5                 �";
	s8 gcAsciiChart09[]				= "� 6                 �";
	s8 gcAsciiChart10[]				= "� 7                 �";
	s8 gcAsciiChart11[]				= "� 8                 �";
	s8 gcAsciiChart12[]				= "� 9                 �";
	s8 gcAsciiChart13[]				= "� A                 �";
	s8 gcAsciiChart14[]				= "� B                 �";
	s8 gcAsciiChart15[]				= "� C                 �";
	s8 gcAsciiChart16[]				= "� D                 �";
	s8 gcAsciiChart17[]				= "� E                 �";
	s8 gcAsciiChart18[]				= "� F                 �";
	s8 gcAsciiChart19[]				= "�������������������ʼ";
