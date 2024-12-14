#ifndef KAMID_STRUCT_H
#define KAMID_STRUCT_H

#include "support.h"
#include "init.h"

#define maxplayerCount 100
#define maxvehicleCount 50
#define maxitemsCount 400
#define maxgrenadeCount 10

struct PlayerBone
{
	bool isBone = false;
	Vec2 neck;
	Vec2 cheast;
	Vec2 pelvis;
	Vec2 lSh;
	Vec2 rSh;
	Vec2 lElb;
	Vec2 rElb;
	Vec2 lWr;
	Vec2 rWr;
	Vec2 lTh;
	Vec2 rTh;
	Vec2 lKn;
	Vec2 rKn;
	Vec2 lAn;
	Vec2 rAn;
	Vec2 root;
};

struct PlayerWeapon
{
	bool isWeapon = false;
	int id;
	int ammo;
	int maxammo;
};

enum Mode
{
	InitMode = 1,
	ESPMode = 2,
	HackMode = 3,
	StopMode = 4,
};

struct Options
{
	int aimbotmode;
	int openState;
	int aimingState;
	bool tracingStatus;
	int priority;
	bool pour;
	int aimingRange;
};

struct Memory
{
	bool LessRecoil;
	bool ZeroRecoil;
	bool InstantHit;
	bool FastShootInterval;
	bool HitX;
	bool SmallCrosshair;
	bool FastSwitchWeapon;
	bool NoShake;
	bool IpadView;
	bool Aimbot;
};

struct Request
{
	int Mode;
	Options options;
	Memory memory;
	int ScreenWidth;
	int ScreenHeight;
};

struct SetValue
{
	int mode;
	int type;
};

struct VehicleData
{
	char VehicleName[50];
	float Fuel;
	float Health;
	float Distance;
	Vec3 Location;
};

struct ItemData
{
	char ItemName[50];
	float Distance;
	Vec3 Location;
};

struct GrenadeData
{
	int type;
	float Distance;
	Vec3 Location;
};

struct PlayerData
{
	char PlayerNameByte[100];
	int TeamID;
	float Health;
	float Distance;
	bool isBot;
	Vec3 HeadLocation;
	PlayerWeapon Weapon;
	PlayerBone Bone;
};

struct Response
{
	bool Success;
	int PlayerCount;
	int VehicleCount;
	int ItemsCount;
	int GrenadeCount;
	float fov;
	PlayerData Players[maxplayerCount];
	VehicleData Vehicles[maxvehicleCount];
	ItemData Items[maxitemsCount];
	GrenadeData Grenade[maxgrenadeCount];
};

#endif
