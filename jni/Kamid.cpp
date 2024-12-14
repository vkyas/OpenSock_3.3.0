#include "INCLUDE/struct.h"

int isbgmi;

uintptr_t getMatrix32(uintptr_t base)
{
	if (isbgmi)	{
		return getA(getA(base + Offsets32::GWorldb) + 0x7c);
	}	else	{
		return getA(getA(base + Offsets32::VMatrix) + 0x7c);
	}
}

uintptr_t getEntityAddr32(uintptr_t base)
{
	uintptr_t level;
	if (isbgmi)	{
		level = getA(getA(getA(getA(base + Offsets32::GWorldb) + 0x38) + 0x58) + 0x20);
	}	else	{
		level = getA(getA(getA(base + Offsets32::GWorld) + 0x3c) + 0x20);
		// level = getA(getA(getA(getA(base + Offsets32::VMatrix) + 0x38) + 0x58) + 0x20);
	}
	return DecryptActorsArray32(level, 0x70, 0x334);
}

PlayerBone getPlayerBone(uintptr_t pBase, struct D3DMatrix viewMatrix)
{
	PlayerBone b;
	b.isBone = true;
	struct D3DMatrix oMatrix;
	uintptr_t boneAddr = getA(pBase + Offsets32::Mesh);
	struct D3DMatrix baseMatrix = getOMatrix(boneAddr + Offsets32::FixAttachInfoList);
	boneAddr = getA(boneAddr + Offsets32::MinLOD) + 0x30;
	// neck 0
	oMatrix = getOMatrix(boneAddr + 4 * 48);
	b.neck = World2ScreenMain(viewMatrix, mat2Cord(oMatrix, baseMatrix));
	// cheast 1
	oMatrix = getOMatrix(boneAddr + 4 * 48);
	b.cheast = World2ScreenMain(viewMatrix, mat2Cord(oMatrix, baseMatrix));
	// pelvis 2
	oMatrix = getOMatrix(boneAddr + 1 * 48);
	b.pelvis = World2ScreenMain(viewMatrix, mat2Cord(oMatrix, baseMatrix));
	// lSh 3
	oMatrix = getOMatrix(boneAddr + 11 * 48);
	b.lSh = World2ScreenMain(viewMatrix, mat2Cord(oMatrix, baseMatrix));
	// rSh 4
	oMatrix = getOMatrix(boneAddr + 32 * 48);
	b.rSh = World2ScreenMain(viewMatrix, mat2Cord(oMatrix, baseMatrix));
	// lElb 5
	oMatrix = getOMatrix(boneAddr + 12 * 48);
	b.lElb = World2ScreenMain(viewMatrix, mat2Cord(oMatrix, baseMatrix));
	// rElb 6
	oMatrix = getOMatrix(boneAddr + 33 * 48);
	b.rElb = World2ScreenMain(viewMatrix, mat2Cord(oMatrix, baseMatrix));
	// lWr 7
	oMatrix = getOMatrix(boneAddr + 63 * 48);
	b.lWr = World2ScreenMain(viewMatrix, mat2Cord(oMatrix, baseMatrix));
	// rWr 8
	oMatrix = getOMatrix(boneAddr + 62 * 48);
	b.rWr = World2ScreenMain(viewMatrix, mat2Cord(oMatrix, baseMatrix));
	// lTh 9
	oMatrix = getOMatrix(boneAddr + 52 * 48);
	b.lTh = World2ScreenMain(viewMatrix, mat2Cord(oMatrix, baseMatrix));
	// rTh 10
	oMatrix = getOMatrix(boneAddr + 56 * 48);
	b.rTh = World2ScreenMain(viewMatrix, mat2Cord(oMatrix, baseMatrix));
	// lKn 11
	oMatrix = getOMatrix(boneAddr + 53 * 48);
	b.lKn = World2ScreenMain(viewMatrix, mat2Cord(oMatrix, baseMatrix));
	// rKn 12
	oMatrix = getOMatrix(boneAddr + 57 * 48);
	b.rKn = World2ScreenMain(viewMatrix, mat2Cord(oMatrix, baseMatrix));
	// lAn 13 
	oMatrix = getOMatrix(boneAddr + 54 * 48);
	b.lAn = World2ScreenMain(viewMatrix, mat2Cord(oMatrix, baseMatrix));
	// rAn 14
	oMatrix = getOMatrix(boneAddr + 58 * 48);
	b.rAn = World2ScreenMain(viewMatrix, mat2Cord(oMatrix, baseMatrix));

	return b;
}

PlayerWeapon getPlayerWeapon(uintptr_t base)
{
	PlayerWeapon p;
	uintptr_t addr[3];
	pvm(getA(base + Offsets32::Children), addr, sizeof(addr));

	if (isValid(addr[0]) && Read<int>(addr[0] + Offsets32::DrawShootLineTime) == 2)
	{
		p.isWeapon = true;
		p.id = Read<int>(getA(addr[0] + Offsets32::ShootWeaponEntityComp) + Offsets32::UploadInterval);
		p.ammo = Read<int>(addr[0] + Offsets32::CurBulletNumInClip);
		p.maxammo = Read<int>(addr[0] + Offsets32::CurMaxBulletNumInOneClip);
	}
	else if (isValid(addr[1]) && Read<int>(addr[1] + Offsets32::DrawShootLineTime) == 2)
	{
		p.isWeapon = true;
		p.id = Read<int>(getA(addr[1] + Offsets32::ShootWeaponEntityComp) + Offsets32::UploadInterval);
		p.ammo = Read<int>(addr[1] + Offsets32::CurBulletNumInClip);
		p.maxammo = Read<int>(addr[1] + Offsets32::CurMaxBulletNumInOneClip);
	}
	else if (isValid(addr[2]) && Read<int>(addr[2] + Offsets32::DrawShootLineTime) == 2)
	{
		p.isWeapon = true;
		p.id = Read<int>(getA(addr[2] + Offsets32::ShootWeaponEntityComp) + Offsets32::UploadInterval);
		p.ammo = Read<int>(addr[2] + Offsets32::CurBulletNumInClip);
		p.maxammo = Read<int>(addr[2] + Offsets32::CurMaxBulletNumInOneClip);
	}
	return p;
}

struct ShootWeaponBase
{
	uintptr_t FromBase;
	uintptr_t Base;
	uintptr_t ShootWeaponEntity;

	  ShootWeaponBase(uintptr_t pBase)
	{
		FromBase = getA(pBase + Offsets32::WeaponManagerComponent);
		Base = getA(FromBase + Offsets32::CurrWeapon);
		ShootWeaponEntity = getA(Base + Offsets32::ShootWeaponEntityComp);
	}

	void setAimbot()
	{
		Write(ShootWeaponEntity + Offsets32::AutoAimingConfig + 0x0, "1090519040", TYPE_DWORD);
		Write(ShootWeaponEntity + Offsets32::AutoAimingConfig + 0x4c, "1090519040", TYPE_DWORD);
		Write(ShootWeaponEntity + Offsets32::AutoAimingConfig + 0x4, "1082130432", TYPE_DWORD);
		Write(ShootWeaponEntity + Offsets32::AutoAimingConfig + 0x50, "1082130432", TYPE_DWORD);
	}
	
	void setLessRecoil()
	{
		if (getF(ShootWeaponEntity + Offsets32::RecoilInfo + Offsets32::RecoilModifierStand) != 0.3)
		{
			Write(ShootWeaponEntity + Offsets32::RecoilInfo + Offsets32::RecoilModifierStand, "0.3F",TYPE_FLOAT);
		}
		if (getF(ShootWeaponEntity + Offsets32::RecoilInfo + Offsets32::RecoilModifierCrouch) != 0.3)
		{
			Write(ShootWeaponEntity + Offsets32::RecoilInfo + Offsets32::RecoilModifierCrouch, "0.3F",TYPE_FLOAT);
		}
		if (getF(ShootWeaponEntity + Offsets32::RecoilInfo + Offsets32::RecoilModifierProne) != 0.3)
		{
			Write(ShootWeaponEntity + Offsets32::RecoilInfo + Offsets32::RecoilModifierProne, "0.3F",TYPE_FLOAT);
		}
	}
	
	void setZeroRecoil()
	{
		Write(ShootWeaponEntity + Offsets32::RecoilKickADS, "0", TYPE_FLOAT);
	}

	void setNoShake()
	{
		Write(ShootWeaponEntity + Offsets32::AnimationKick, "0", TYPE_FLOAT);
	}

	void setSmallCrosshair()
	{
		Write(ShootWeaponEntity + Offsets32::GameDeviationFactor, "0", TYPE_FLOAT);
	}

	void setInstantHit()
	{
		Write(ShootWeaponEntity + Offsets32::BulletFireSpeed, "910000", TYPE_FLOAT);
	}

	void setFastShoot()
	{
		Write(ShootWeaponEntity + Offsets32::ShootInterval, "0.048000", TYPE_FLOAT);
	}

	void setHitX()
	{
		Write(ShootWeaponEntity + Offsets32::ExtraHitPerformScale, "50", TYPE_FLOAT);
	}

	bool isValid()
	{
		return (Base != 0);
	}
};

struct CameraComponent
{
	uintptr_t Base;

	  CameraComponent(uintptr_t uMyObject)
	{
		Base = getA(uMyObject + Offsets32::ThirdPersonCameraComponent);
	}

	void setWideView()
	{
		Write(Base + Offsets32::FieldOfView, "120", TYPE_FLOAT);
	}

	bool isValid()
	{
		return (Base != 0);
	}
};

int main(int argc, char *argv[])
{
	if (!Create())
	{
		perror("Creation Failed");
		return 0;
	}
	if (!Connect())
	{
		perror("Connection Failed");
		return 0;
	}

	pid = getPid("com.tencent.ig");
	if (pid == 0)
	{
		pid = getPid("com.pubg.krmobile");
		if (pid == 0)
		{
			pid = getPid("com.vng.pubgmobile");
			if (pid == 0)
			{
				pid = getPid("com.rekoo.pubgm");
				if (pid == 0)
				{
					pid = getPid("com.pubg.imobile");
					isbgmi = true;
					if (pid == 0)
					{
						printf("\nGame is not running");
						Close();
						return 0;
					}
				}
			}
		}
	}

	isPremium = true;
	uintptr_t base = getBase();
	uintptr_t vMatrix = getMatrix32(base);

	if (!vMatrix)
		return 0;
	bool aimbot = false;
	bool aimKnoced = false;
	int firing = 0, ads = 0;
	int aimBy = 1, aimFor = 1, aimWhen = 3;
	float aimRadius = 200;
	struct Vec2 pointingAngle;
	uintptr_t yawPitch = 0;
	uintptr_t enAddrPntr;
	struct Vec3 xyz, exyz;
	struct D3DMatrix vMat;
	int changed = 1;
	int myteamID = 101;
	uintptr_t cLoc = vMatrix + 0x6d0;
	uintptr_t fovPntr = vMatrix + 0x5e0;
	vMatrix = vMatrix + 0x510;
	char name[100];
	uintptr_t gname_buff[30];
	uintptr_t gname;

	if (isbgmi)	{
		gname = getA(getA(base + Offsets32::GNamesBgmi) + 0x88);
	}	else	{
		gname = getA(getA(base + Offsets32::GNamesGlobal) + 0x88);
	}

	pvm(gname, &gname_buff, sizeof(gname_buff));

	// Sdk Hacks
	bool isLessRecoil = false;
	bool isZeroRecoil = false;
	bool isNoShake = false;
	bool isSmallCrosshair = false;
	bool isInstantHit = false;
	bool isFastShootInterval = false;
	bool isHitX = false;
	bool isFastSwitchWeapon = false;
	bool isIpadView = false;
	bool isAimbot = false;

	// Communication 
	Request request
	{
		// 
	};
	Response response
	{
		// 
	};

	while (receive((void *)&request) > 0)
	{
		height = request.ScreenHeight;
		width = request.ScreenWidth;
		if (request.Mode == InitMode)
		{
			aimRadius = (float)request.options.aimingRange;
			aimFor = request.options.aimbotmode;
			aimbot = request.options.openState == 0;
			aimWhen = request.options.aimingState;
			aimBy = request.options.priority;
			aimKnoced = request.options.pour;

			isLessRecoil = request.memory.LessRecoil;
			isZeroRecoil = request.memory.ZeroRecoil;
			isNoShake = request.memory.NoShake;
			isSmallCrosshair = request.memory.SmallCrosshair;
			isInstantHit = request.memory.InstantHit;
			isFastShootInterval = request.memory.FastShootInterval;
			isHitX = request.memory.HitX;
			isFastSwitchWeapon = request.memory.FastSwitchWeapon;
			isIpadView = request.memory.IpadView;
			isAimbot = request.memory.Aimbot;
		}
		response.Success = false;
		response.PlayerCount = 0;
		response.VehicleCount = 0;
		response.ItemsCount = 0;
		response.GrenadeCount = 0;

		pvm(cLoc, &xyz, sizeof(xyz));
		if (xyz.Z == 88.441124f || xyz.X == 0 || xyz.Z == 5278.43f || xyz.Z == 88.440918f)
		{
			changed = 1;
			send((void *)&response, sizeof(response));
			continue;
		}
		pvm(fovPntr, &response.fov, 4);
		pvm(vMatrix, &vMat, sizeof(vMat));
		if (changed == 1)
		{
			enAddrPntr = getEntityAddr32(base);
			changed = 0;
		}
		Ulevel ulevel;
		pvm(enAddrPntr, &ulevel, sizeof(ulevel));
		if (ulevel.size < 1 || ulevel.size > 0x1000 || !isValid(ulevel.addr))
		{
			changed = 1;
			send((void *)&response, sizeof(response));
			continue;
		}

		float nearest = -1.0f;
		for (int i = 0; i < ulevel.size; i++)
		{
			uintptr_t pBase = getA(ulevel.addr + i * SIZE);
			if (!isValid(pBase))
			{
				continue;
			}

			if (Read<int>(pBase + SIZE) != 8)
			{
				continue;
			}

			int ids = Read<int>(pBase + 8 + 2 * SIZE);
			int page = ids / 0x4000;
			int index = ids % 0x4000;

			if (page < 1 || page > 30)
			{
				continue;
			}

			if (gname_buff[page] == 0)
			{
				gname_buff[page] = getA(gname + page * SIZE);
			}

			strcpy(name, getText(getA(gname_buff[page] + index * SIZE)));
			if (strlen(name) < 5)
			{
				continue;
			}

			if (strstr(name, "BP_PlayerPawn") || strstr(name, "BP_PlayerCharacter")
				|| strstr(name, "BP_CharacterModelTaget"))
			{
				int oType = Read<int>(pBase + 0x60);
				if (!isValidPlayer(oType))
				{
					// continue;
				}

				if (Read<bool>(pBase + Offsets32::bDead))
				{
					continue;
				}

				PlayerData *data = &response.Players[response.PlayerCount];
				data->TeamID = Read<int>(pBase + Offsets32::TeamID);
				char role = Read<char>(pBase + Offsets32::Role);

				if (role == 2)
				{
					if (aimbot)
					{
						if (aimWhen == 3 || aimWhen == 2)
						{
							pvm(pBase + Offsets32::bIsWeaponFiring, &firing, 1);
						}
						if (aimWhen == 3 || aimWhen == 1)
						{
							pvm(pBase + Offsets32::bIsGunADS, &ads, 1);
						}
						yawPitch = getA(pBase + Offsets32::Controller) + Offsets32::ControlRotation;
					}

					ShootWeaponBase shootWeaponBase(pBase);
					if (shootWeaponBase.isValid())
					{
						if (isLessRecoil || isZeroRecoil)
						{
							shootWeaponBase.setLessRecoil();
							if (isZeroRecoil)
							{
								shootWeaponBase.setZeroRecoil();
							}
						}
						if (isNoShake)
						{
							shootWeaponBase.setNoShake();
						}
						if (isInstantHit)
						{
							shootWeaponBase.setInstantHit();
						}
						if (isFastShootInterval)
						{
							shootWeaponBase.setFastShoot();
						}
						if (isAimbot)
						{
							shootWeaponBase.setAimbot();
						}
						if (isHitX)
						{
							shootWeaponBase.setHitX();
						}
						if (isSmallCrosshair)
						{
							shootWeaponBase.setSmallCrosshair();
						}
						if (isFastSwitchWeapon)
						{
							Write(pBase + Offsets32::SwitchWeaponSpeedScale, "100", TYPE_FLOAT);
						}
					}

					CameraComponent cameraComponent(pBase);
					if (cameraComponent.isValid())
					{
						if (isIpadView)
						{
							cameraComponent.setWideView();
						}
					}

					myteamID = data->TeamID;
					continue;
				}
				else if (role != 1)
				{
					continue;
				}

				if (data->TeamID == myteamID && myteamID <= 100)
				{
					continue;
				}

				uintptr_t boneAddr = getA(pBase + Offsets32::Mesh);
				exyz =
					mat2Cord(getOMatrix(getA(boneAddr + Offsets32::MinLOD) + 6 * 48),
							getOMatrix(boneAddr + Offsets32::FixAttachInfoList));

				pvm(pBase + Offsets32::bIsAI, &data->isBot, sizeof(data->isBot));
				pvm(pBase + Offsets32::Health, healthbuff, sizeof(healthbuff));
				data->Health = healthbuff[0] / healthbuff[1] * 100;
				data->HeadLocation = World2Screen(vMat, exyz);
				data->Distance = getDistance(xyz, exyz);

				if (healthbuff[1] > 200.0f || healthbuff[1] < 50.0f
					|| healthbuff[0] > healthbuff[1] || healthbuff[0] < 0.0f)
				{
					continue;
				}

				if (data->Distance > 600.0f)
				{
					continue;
				}

				if (data->HeadLocation.Z != 1.0f && data->HeadLocation.X < width + 100
					&& data->HeadLocation.X > -50)
				{
					data->Bone = getPlayerBone(pBase, vMat);
					data->Weapon = getPlayerWeapon(pBase);
					strcpy(data->PlayerNameByte, "66:79:84:");

					if (!data->isBot)
					{
						strcpy(data->PlayerNameByte, getNameByte(getA(pBase + Offsets32::PlayerName)));
						if (strlen(data->PlayerNameByte) < 4)
						{
							continue;
						}
					}
				}

				if (data->HeadLocation.Z != 1.0f && (aimKnoced || data->Health > 0) && aimbot)
				{
					float centerDist =	sqrt((data->HeadLocation.X - width / 2) * (data->HeadLocation.X - width / 2) + (data->HeadLocation.Y - height / 2) * (data->HeadLocation.Y - height / 2));
					if (centerDist < aimRadius)
					{
						if (aimBy != 1)
						{
							centerDist = data->Distance;
						}

						if (nearest > centerDist || nearest < 0)
						{
							nearest = centerDist;
							if (aimFor == 1)
							{
								pointingAngle = getPointingAngle(xyz, exyz, data->Distance);
							}
							else if (aimFor == 2)
							{
								uintptr_t boneAddr = getA(pBase + Offsets32::Mesh);
								struct D3DMatrix baseMatrix =	getOMatrix(boneAddr + Offsets32::FixAttachInfoList);
								boneAddr = getA(boneAddr + Offsets32::MinLOD);
								struct D3DMatrix oMatrix = getOMatrix(boneAddr + 4 * 48);
								pointingAngle =	getPointingAngle(xyz, mat2Cord(oMatrix, baseMatrix), data->Distance);
							}
							else
							{
								uintptr_t boneAddr = getA(pBase + Offsets32::Mesh);
								struct D3DMatrix baseMatrix =	getOMatrix(boneAddr + Offsets32::FixAttachInfoList);
								boneAddr = getA(boneAddr + Offsets32::MinLOD);
								struct D3DMatrix oMatrix = getOMatrix(boneAddr + 2 * 48);
								pointingAngle =	getPointingAngle(xyz, mat2Cord(oMatrix, baseMatrix), data->Distance);
							}
						}
					}
				}
				if (response.PlayerCount >= maxplayerCount)
				{
					continue;
				}
				response.PlayerCount++;
			}
			else if (strstr(name, "VH") || (strstr(name, "PickUp_") && !strstr(name, "BP"))
					|| strstr(name, "Rony") || strstr(name, "Mirado") || strstr(name, "LadaNiva")
					|| strstr(name, "AquaRail"))
			{
				if (!isPremium)
				{
					continue;
				}

				VehicleData *data = &response.Vehicles[response.VehicleCount];
				pvm(getA(pBase + Offsets32::RootComponent) + Offsets32::ParachuteEquipItems, &exyz, sizeof(exyz));
				data->Location = World2Screen(vMat, exyz);
				if (data->Location.Z == 1.0f || data->Location.X > width + 200
					|| data->Location.X < -200)
				{
					continue;
				}

				uintptr_t Vehicle = getA(pBase + Offsets32::VehicleCommon);
				data->Fuel =	Read<float>(Vehicle + Offsets32::VFuel) / Read<float>(Vehicle + Offsets32::VFuelMax) * 100;
				data->Health =	Read<float>(Vehicle + Offsets32::VHealth) / Read<float>(Vehicle + Offsets32::VHealthMax) * 100;

				data->Distance = getDistance(xyz, exyz);
				strcpy(data->VehicleName, name);

				if (response.VehicleCount >= maxvehicleCount)
				{
					continue;
				}
				response.VehicleCount++;
			}
			else if (strstr(name, "Pickup_C") || strstr(name, "PickUp") || strstr(name, "BP_Ammo")
					|| strstr(name, "BP_QK") || strstr(name, "Wrapper"))
			{
				if (!isPremium)
				{
					continue;
				}

				ItemData *data = &response.Items[response.ItemsCount];
				pvm(getA(pBase + Offsets32::RootComponent) + Offsets32::ParachuteEquipItems, &exyz, sizeof(exyz));
				data->Location = World2Screen(vMat, exyz);
				if (data->Location.Z == 1.0f || data->Location.X > width + 100
					|| data->Location.X < -50)
				{
					continue;
				}
				data->Distance = getDistance(xyz, exyz);
				if (data->Distance > 200.0f)
				{
					continue;
				}
				strcpy(data->ItemName, name);

				if (response.ItemsCount >= maxitemsCount)
				{
					continue;
				}
				response.ItemsCount++;
			}
			else if (strstr(name, "BP_AirDropPlane_") || strstr(name, "PlayerDeadInventoryBox_")
					|| strstr(name, "BP_AirDropBox_"))
			{
				if (!isPremium)
				{
					continue;
				}

				ItemData *data = &response.Items[response.ItemsCount];
				pvm(getA(pBase + Offsets32::RootComponent) + Offsets32::ParachuteEquipItems, &exyz, sizeof(exyz));
				data->Location = World2Screen(vMat, exyz);
				if (data->Location.Z == 1.0f || data->Location.X > width + 100
					|| data->Location.X < -50)
				{
					continue;
				}
				data->Distance = getDistance(xyz, exyz);
				strcpy(data->ItemName, name);

				if (response.ItemsCount >= maxitemsCount)
				{
					continue;
				}
				response.ItemsCount++;
			}
			else if (strstr(name, "BP_Grenade_Shoulei_C") || strstr(name, "BP_Grenade_Burn_C")
					|| strstr(name, "BP_Grenade_Stun_C"))
			{
				if (!isPremium)
					continue;

				GrenadeData *data = &response.Grenade[response.GrenadeCount];
				pvm(getA(pBase + Offsets32::RootComponent) + Offsets32::ParachuteEquipItems, &exyz, sizeof(exyz));
				data->Location = World2Screen(vMat, exyz);
				data->Distance = getDistance(xyz, exyz);

				if (data->Distance > 150.0f)
				{
					continue;
				}

				if (strstr(name, "Shoulei"))
				{
					data->type = 1;
				}
				else if (strstr(name, "Burn"))
				{
					data->type = 2;
				}
				else if (strstr(name, "Stun"))
				{
					data->type = 3;
				}

				if (response.GrenadeCount >= maxgrenadeCount)
				{
					continue;
				}
				response.GrenadeCount++;
			}
		}
		if (response.PlayerCount + response.ItemsCount + response.VehicleCount +
			response.GrenadeCount > 0)
		{
			response.Success = true;
		}

		send((void *)&response, sizeof(response));
		if ((firing || ads) && nearest > 0)
		{
			pvm2(yawPitch, &pointingAngle, 8);
		}
	}
}
