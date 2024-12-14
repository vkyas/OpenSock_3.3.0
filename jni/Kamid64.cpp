#include "INCLUDE/struct.h"

int glorbgmi = 0;
int vng = 0;

uintptr_t getMatrix64(uintptr_t base)
{
	if (glorbgmi == 0 && vng == 0) {
		return getA(getA(base + Offsets64::GWORLDGLOBAL) + 0xc0);
	} else if (glorbgmi == 1) {
		return getA(getA(base + Offsets64::GWORLDBGMI) + 0xc0);
	} else if (vng == 1) {
		return getA(getA(base + Offsets64::GWORLDVNG) + 0xc0);
	}
		return 0;
}

uintptr_t getEntityAddr64(uintptr_t base)
{
	uintptr_t level;
	if (glorbgmi == 0 && vng == 0) {
		level = getA(getA(getA(getA(base + Offsets64::GWORLDGLOBAL) + 0x58) + 0x78) + 0x30);
	} else if (glorbgmi == 1) {
		level = getA(getA(getA(getA(base + Offsets64::GWORLDBGMI) + 0x58) + 0x78) + 0x30);
	} else if (vng == 1) {
		level = getA(getA(getA(getA(base + Offsets64::GWORLDVNG) + 0x58) + 0x78) + 0x30);
	}
	return DecryptActorsArray64(level, 0xA0, 0x448);
}

PlayerBone getPlayerBone(uintptr_t pBase, struct D3DMatrix viewMatrix)
{
	PlayerBone b;
	b.isBone = true;
	struct D3DMatrix oMatrix;
	uintptr_t boneAddr = getA(pBase + Offsets64::Mesh);
	struct D3DMatrix baseMatrix = getOMatrix(boneAddr + Offsets64::FixAttachInfoList);
	boneAddr = getA(boneAddr + Offsets64::MinLOD) + 0x30;
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
	pvm(getA(base + Offsets64::Children), addr, sizeof(addr));

	if (isValid64(addr[0]) && Read <int>(addr[0] + Offsets64::DrawShootLineTime) == 2)
	{
		p.isWeapon = true;
		p.id = Read <int>(getA(addr[0] + Offsets64::ShootWeaponEntityComp) + Offsets64::UploadInterval);
		p.ammo = Read <int>(addr[0] + Offsets64::CurBulletNumInClip);
		p.maxammo = Read <int>(addr[0] + Offsets64::CurMaxBulletNumInOneClip);
	}
	else if (isValid64(addr[1]) && Read <int>(addr[1] + Offsets64::DrawShootLineTime) == 2)
	{
		p.isWeapon = true;
		p.id = Read <int>(getA(addr[1] + Offsets64::ShootWeaponEntityComp) + Offsets64::UploadInterval);
		p.ammo = Read <int>(addr[1] + Offsets64::CurBulletNumInClip);
		p.maxammo = Read <int>(addr[1] + Offsets64::CurMaxBulletNumInOneClip);
	}
	else if (isValid64(addr[2]) && Read <int>(addr[2] + Offsets64::DrawShootLineTime) == 2)
	{
		p.isWeapon = true;
		p.id = Read <int>(getA(addr[2] + Offsets64::ShootWeaponEntityComp) + Offsets64::UploadInterval);
		p.ammo = Read <int>(addr[2] + Offsets64::CurBulletNumInClip);
		p.maxammo = Read <int>(addr[2] + Offsets64::CurMaxBulletNumInOneClip);
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
		FromBase = getA(pBase + Offsets64::WeaponManagerComponent);
		Base = getA(FromBase + Offsets64::CurrWeapon);
		ShootWeaponEntity = getA(Base + Offsets64::ShootWeaponEntityComp);
	}

	void setAimbot()
	{
		Write(ShootWeaponEntity + Offsets64::AutoAimingConfig + 0x0, "1090519040", TYPE_DWORD);
		Write(ShootWeaponEntity + Offsets64::AutoAimingConfig + 0x4c, "1090519040", TYPE_DWORD);
		Write(ShootWeaponEntity + Offsets64::AutoAimingConfig + 0x4, "1082130432", TYPE_DWORD);
		Write(ShootWeaponEntity + Offsets64::AutoAimingConfig + 0x50, "1082130432", TYPE_DWORD);
	}

	/*void setLessRecoil()
	{
		Write(ShootWeaponEntity + Offsets64::RecoilInfo + Offsets64::RecoilModifierStand, "0.2F", TYPE_FLOAT);
		Write(ShootWeaponEntity + Offsets64::RecoilInfo + Offsets64::RecoilModifierCrouch, "0.2F", TYPE_FLOAT);
		Write(ShootWeaponEntity + Offsets64::RecoilInfo + Offsets64::RecoilModifierProne, "0.2F", TYPE_FLOAT);
	}*/
	
	void setLessRecoil()
	{
		if (getF(ShootWeaponEntity + Offsets64::RecoilInfo + Offsets64::RecoilModifierStand) != 0.3)
		{
			Write(ShootWeaponEntity + Offsets64::RecoilInfo + Offsets64::RecoilModifierStand, "0.3",TYPE_FLOAT);
		}
		if (getF(ShootWeaponEntity + Offsets64::RecoilInfo + Offsets64::RecoilModifierCrouch) != 0.3)
		{
			Write(ShootWeaponEntity + Offsets64::RecoilInfo + Offsets64::RecoilModifierCrouch, "0.3",TYPE_FLOAT);
		}
		if (getF(ShootWeaponEntity + Offsets64::RecoilInfo + Offsets64::RecoilModifierProne) != 0.3)
		{
			Write(ShootWeaponEntity + Offsets64::RecoilInfo + Offsets64::RecoilModifierProne, "0.3",TYPE_FLOAT);
		}
	}
	
	void setZeroRecoil()
	{
		Write(ShootWeaponEntity + Offsets64::RecoilKickADS, "0", TYPE_FLOAT);
	}

	void setNoShake()
	{
		Write(ShootWeaponEntity + Offsets64::AnimationKick, "0", TYPE_FLOAT);
	}

	void setSmallCrosshair()
	{
		Write(ShootWeaponEntity + Offsets64::GameDeviationFactor, "0", TYPE_FLOAT);
	}

	void setInstantHit()
	{
		Write(ShootWeaponEntity + Offsets64::BulletFireSpeed, "910000", TYPE_FLOAT);
	}

	void setFastShoot()
	{
		Write(ShootWeaponEntity + Offsets64::ShootInterval, "0.048000", TYPE_FLOAT);
	}

	void setHitX()
	{
		Write(ShootWeaponEntity + Offsets64::ExtraHitPerformScale, "50", TYPE_FLOAT);
	}

	bool isValid64()
	{
		return (Base != 0);
	}
};

struct CameraComponent
{
	uintptr_t Base;

	  CameraComponent(uintptr_t uMyObject)
	{
		Base = getA(uMyObject + Offsets64::ThirdPersonCameraComponent);
	}

	void setWideView()
	{
		Write(Base + Offsets64::FieldOfView, "120", TYPE_FLOAT);
	}

	bool isValid64()
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
			vng = 1;
			if (pid == 0)
			{
				pid = getPid("com.rekoo.pubgm");
				if (pid == 0)
				{
					pid = getPid("com.pubg.imobile");
					glorbgmi = 1;
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
	uintptr_t vMatrix = getMatrix64(base);
	
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
	uintptr_t cLoc = vMatrix + 0x750;
	uintptr_t fovPntr = vMatrix + 0x660;
	vMatrix = vMatrix + 0x590;
	char name[100];
	uintptr_t gname_buff[30];
	uintptr_t gname;
	
	if (glorbgmi == 0 && vng == 0) {
		gname = getA(getA(base + Offsets64::GNamesGlobal) + 0x110);
	} else if (glorbgmi == 1) {
		gname = getA(getA(base + Offsets64::GNamesBgmi) + 0x110);
	} else if (vng == 1) {
		gname = getA(getA(base + Offsets64::GNamesVng) + 0x110);
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
	Request request	{	};
	Response response	{	};

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
			enAddrPntr = getEntityAddr64(base);
			changed = 0;
		}
		Ulevel ulevel;
		pvm(enAddrPntr, &ulevel, sizeof(ulevel));
		if (ulevel.size < 1 || ulevel.size > 0x1000 || !isValid64(ulevel.addr))
		{
			changed = 1;
			send((void *)&response, sizeof(response));
			continue;
		}

		float nearest = -1.0f;
		for (int i = 0; i < ulevel.size; i++)
		{
			uintptr_t pBase = getA(ulevel.addr + i * SIZE);
			if (!isValid64(pBase))
			{
				continue;
			}

			if (Read <int>(pBase + SIZE) != 8)
			{
				continue;
			}

			int ids = Read <int>(pBase + 8 + 2 * SIZE);
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
				int oType = Read <int>(pBase + 0x88);
				if (!isValidPlayer(oType))
				{
					// continue;
				}

				if (Read < bool > (pBase + Offsets64::bDead))
				{
					continue;
				}

				PlayerData *data = &response.Players[response.PlayerCount];
				data->TeamID = Read <int>(pBase + Offsets64::TeamID);
				char role = Read <char>(pBase + Offsets64::Role);

				if (role == 2)
				{
					if (aimbot)
					{
						if (aimWhen == 3 || aimWhen == 2)
						{
							pvm(pBase + Offsets64::bIsWeaponFiring, &firing, 1);
						}
						if (aimWhen == 3 || aimWhen == 1)
						{
							pvm(pBase + Offsets64::bIsGunADS, &ads, 1);
						}
						yawPitch = getA(pBase + Offsets64::Controller) + Offsets64::ControlRotation;
					}

					ShootWeaponBase shootWeaponBase(pBase);
					if (shootWeaponBase.isValid64())
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
							// Write(pBase + Offsets64::SwitchWeaponSpeedScale, "100",
							// TYPE_FLOAT);
						}
					}

					CameraComponent cameraComponent(pBase);
					if (cameraComponent.isValid64())
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

				uintptr_t boneAddr = getA(pBase + Offsets64::Mesh);
				exyz =
					mat2Cord(getOMatrix(getA(boneAddr + Offsets64::MinLOD) + 6 * 48),
							 getOMatrix(boneAddr + Offsets64::FixAttachInfoList));

				pvm(pBase + Offsets64::bIsAI, &data->isBot, sizeof(data->isBot));
				pvm(pBase + Offsets64::Health, healthbuff, sizeof(healthbuff));
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
						strcpy(data->PlayerNameByte, getNameByte(getA(pBase + Offsets64::PlayerName)));
						if (strlen(data->PlayerNameByte) < 4)
						{
							continue;
						}
					}
				}

				if (data->HeadLocation.Z != 1.0f && (aimKnoced || data->Health > 0) && aimbot)
				{
					float centerDist =
						sqrt((data->HeadLocation.X - width / 2) * (data->HeadLocation.X -
																   width / 2) +
							 (data->HeadLocation.Y - height / 2) * (data->HeadLocation.Y -
																	height / 2));
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
								uintptr_t boneAddr = getA(pBase + Offsets64::Mesh);
								struct D3DMatrix baseMatrix =
									getOMatrix(boneAddr + Offsets64::FixAttachInfoList);
								boneAddr = getA(boneAddr + Offsets64::MinLOD);
								struct D3DMatrix oMatrix = getOMatrix(boneAddr + 4 * 48);
								pointingAngle =
									getPointingAngle(xyz, mat2Cord(oMatrix, baseMatrix),
													 data->Distance);
							}
							else
							{
								uintptr_t boneAddr = getA(pBase + Offsets64::Mesh);
								struct D3DMatrix baseMatrix =
									getOMatrix(boneAddr + Offsets64::FixAttachInfoList);
								boneAddr = getA(boneAddr + Offsets64::MinLOD);
								struct D3DMatrix oMatrix = getOMatrix(boneAddr + 2 * 48);
								pointingAngle =
									getPointingAngle(xyz, mat2Cord(oMatrix, baseMatrix),
													 data->Distance);
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
				pvm(getA(pBase + Offsets64::RootComponent) + Offsets64::ParachuteEquipItems, &exyz, sizeof(exyz));
				data->Location = World2Screen(vMat, exyz);
				if (data->Location.Z == 1.0f || data->Location.X > width + 200
					|| data->Location.X < -200)
				{
					continue;
				}

				uintptr_t Vehicle = getA(pBase + Offsets64::VehicleCommon);
				data->Fuel =
					Read <float>(Vehicle + Offsets64::VFuel) / Read <float>(Vehicle + Offsets64::VFuelMax) * 100;
				data->Health =
					Read <float>(Vehicle + Offsets64::VHealth) / Read <float>(Vehicle + Offsets64::VHealthMax) * 100;

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
				pvm(getA(pBase + Offsets64::RootComponent) + Offsets64::ParachuteEquipItems, &exyz, sizeof(exyz));
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
			else if (strstr(name, "BP_AirDropPlane_C") || strstr(name, "PlayerDeadInventoryBox_C")
					 || strstr(name, "BP_AirDropBox_C"))
			{
				if (!isPremium)
				{
					continue;
				}

				ItemData *data = &response.Items[response.ItemsCount];
				pvm(getA(pBase + Offsets64::RootComponent) + Offsets64::ParachuteEquipItems, &exyz, sizeof(exyz));
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
			else if (strstr(name, "BP_Grenade_Shoulei_") || strstr(name, "BP_Grenade_Burn_")
					 || strstr(name, "BP_Grenade_Stun_"))
			{
				if (!isPremium)
					continue;

				GrenadeData *data = &response.Grenade[response.GrenadeCount];
				pvm(getA(pBase + Offsets64::RootComponent) + Offsets64::ParachuteEquipItems, &exyz, sizeof(exyz));
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
