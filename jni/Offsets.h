#ifndef KAMID_OFFSETS_H
#define KAMID_OFFSETS_H

namespace Offsets32
{
	// GLOBAL_3.4.0
	uintptr_t GNamesGlobal = 0x925D434;
	uintptr_t VMatrix = 0x96162A0;
	uintptr_t GWorld = 0x962E4E4;
	
	// BGMI_3.4.0
	uintptr_t GNamesBgmi = 0x8997924;
	uintptr_t GWorldb = 0x8eb7224;
	
	uintptr_t MinLOD = 0x6f4;
	uintptr_t FixAttachInfoList = 0x150;
	uintptr_t ParachuteEquipItems = 0x160;
	
	uintptr_t ReplicatedMovement = 0x80;
	uintptr_t Role = 0x108;
	uintptr_t Children = 0x14c;
	uintptr_t RootComponent = 0x158;
	uintptr_t AttachSocket = 0x28;
	uintptr_t LastRenderTime = 0x398;
	uintptr_t LastRenderTimeOnScreen = 0x39c;
	uintptr_t Controller = 0x35c;
	uintptr_t ControlRotation = 0x358;
	uintptr_t Mesh = 0x380;
	uintptr_t MovementCharacter = 0x384;
	uintptr_t MaxWalkSpeed = 0x184;
	uintptr_t MaxWalkSpeedCrouched = 0x188;
	uintptr_t DrawShootLineTime = 0xfc;
	uintptr_t Velocity = 0xd0;
	uintptr_t AcknowledgedPawn = 0x390;
	uintptr_t PlayerCameraManager = 0x3a0;
	uintptr_t CameraCache = 0x3b0;
	uintptr_t CameraCache2 = 0xed0;
	uintptr_t ViewPitchMin = 0x1ad0;
	uintptr_t ViewPitchMax = 0x1ad4;
	uintptr_t ViewYawMin = 0x1ad8;
	uintptr_t ViewYawMax = 0x1adc;
	uintptr_t FieldOfView = 0x2cc;
	uintptr_t ParachuteComponent = 0x1098;
	uintptr_t bIsWeaponFiring = 0x10a4;
	uintptr_t NearDeatchComponent = 0x1330;
	uintptr_t NearDeathBreath = 0x1344;
	uintptr_t CustomSpringArmComponent = 0x1460;
	uintptr_t ThirdPersonCameraComponent = 0x1468;
	uintptr_t STCharacterMovement = 0x1538;
	uintptr_t WeaponManagerComponent = 0x1b40;
	uintptr_t WalkSpeed = 0x1ef8;
	uintptr_t SwitchWeaponSpeedScale = 0x1fac;
	uintptr_t Health = 0xa54;
	uintptr_t bDead = 0xa6c;
	uintptr_t CurrentVehicle = 0xa8c;
	uintptr_t bIsGunADS = 0xc31;
	uintptr_t PlayerName = 0x6b0;
	uintptr_t Nation = 0x6bc;
	uintptr_t PlayerUID = 0x6cc;
	uintptr_t TeamID = 0x6e4;
	uintptr_t CampID = 0x6ec;
	uintptr_t bIsAI = 0x77d;
	uintptr_t VehicleCommon = 0x850;
	uintptr_t CurBulletNumInClip = 0xbac;
	uintptr_t CurMaxBulletNumInOneClip = 0xbc0;
	uintptr_t ShootWeaponEntityComp = 0xcd8;
	uintptr_t STPlayerController = 0x32dc;
	uintptr_t LocalTeamID = 0x6b4;
	uintptr_t CurrWeapon = 0x40c;
	uintptr_t RecoilModifierStand = 0x48;
	uintptr_t RecoilModifierCrouch = 0x4c;
	uintptr_t RecoilModifierProne = 0x50;
	uintptr_t BulletFireSpeed = 0x424;
	uintptr_t ShootInterval = 0x450;
	uintptr_t WeaponWarnUpTime = 0x518;
	uintptr_t WeaponHitPartCoff = 0x520;
	uintptr_t WeaponHitPartCoffZombie = 0x534;
	uintptr_t BaseImpactDamage = 0x548;
	uintptr_t BulletMomentum = 0x550;
	uintptr_t MaxDamageRate = 0x610;
	uintptr_t DamageImpulse = 0x708;
	uintptr_t AutoAimingConfig = 0x7b8;
	uintptr_t RecoilInfo = 0x8b8;
	uintptr_t AccessoriesVRecoilFactor = 0x91c;
	uintptr_t AccessoriesHRecoilFactor = 0x920;
	uintptr_t AccessoriesRecoveryFactor = 0x924;
	uintptr_t GameDeviationFactor = 0x984;
	uintptr_t RecoilKickADS = 0xa30;
	uintptr_t ExtraHitPerformScale = 0xa34;
	uintptr_t AnimationKick = 0xa4c;
	uintptr_t CurrentFallSpeed = 0x14c;
	uintptr_t UploadInterval = 0x108;
	uintptr_t VHealthMax = 0x1fc;
	uintptr_t VHealth = 0x200;
	uintptr_t VFuelMax = 0x258;
	uintptr_t VFuel = 0x260;
	uintptr_t BreathMax = 0x10c;
	uintptr_t MinimalViewInfo = 0x10;

}

namespace Offsets64
{
	// PUBG_3.5.0
	uintptr_t GNamesGlobal = 0xCCA7020;
	uintptr_t GWORLDGLOBAL = 0xD3E9A70;
	// BGMI_3.5.0
	uintptr_t GNamesBgmi = 0xC646620;
	uintptr_t GWORLDBGMI = 0xCD88FF0;
	// VNG_3.5.0
	uintptr_t GNamesVng = 0xCCE70A0;
	uintptr_t GWORLDVNG = 0xD429AF0;
	
	uintptr_t MinLOD = 0x888;
	uintptr_t FixAttachInfoList = 0x1b0;
	uintptr_t ParachuteEquipItems = 0x1c0;
	
	uintptr_t ReplicatedMovement = 0xb0;
	uintptr_t Role = 0x150;
	uintptr_t Children = 0x1a0;
	uintptr_t RootComponent = 0x1b0;
	uintptr_t AttachSocket = 0x30;
	uintptr_t LastRenderTime = 0x410;
	uintptr_t LastRenderTimeOnScreen = 0x414;
	uintptr_t Controller = 0x470;
	uintptr_t ControlRotation = 0x468;
	uintptr_t Mesh = 0x498;
	uintptr_t MovementCharacter = 0x4a0;
	uintptr_t MaxWalkSpeed = 0x1f4;
	uintptr_t MaxWalkSpeedCrouched = 0x1f8;
	uintptr_t Velocity = 0x12c;
	uintptr_t AcknowledgedPawn = 0x4b0;
	uintptr_t PlayerCameraManager = 0x4d0;
	uintptr_t CameraCache = 0x4b0;
	uintptr_t CameraCache2 = 0x1030;
	uintptr_t ViewPitchMin = 0x1cdc;
	uintptr_t ViewPitchMax = 0x1ce0;
	uintptr_t ViewYawMin = 0x1ce4;
	uintptr_t ViewYawMax = 0x1ce8;
	uintptr_t DrawShootLineTime = 0x13c;
	uintptr_t FieldOfView = 0x33c;
	uintptr_t ParachuteComponent = 0x1628;
	uintptr_t bIsWeaponFiring = 0x1640;
	uintptr_t NearDeatchComponent = 0x1960;
	uintptr_t NearDeathBreath = 0x1980;
	uintptr_t CustomSpringArmComponent = 0x1ac0;
	uintptr_t ThirdPersonCameraComponent = 0x1ad0;
	uintptr_t STCharacterMovement = 0x1bf8;
	uintptr_t WeaponManagerComponent = 0x2328;
	uintptr_t WalkSpeed = 0x2868;
	uintptr_t SwitchWeaponSpeedScale = 0x2940;
	uintptr_t Health = 0xdc0;
	uintptr_t bDead = 0xddc;
	uintptr_t CurrentVehicle = 0xe08;
	uintptr_t bIsGunADS = 0x1051;
	uintptr_t PlayerName = 0x8f0;
	uintptr_t Nation = 0x900;
	uintptr_t PlayerUID = 0x918;
	uintptr_t TeamID = 0x938;
	uintptr_t CampID = 0x940;
	uintptr_t bIsAI = 0x9e9;
	uintptr_t VehicleCommon = 0xac0;
	uintptr_t CurBulletNumInClip = 0xed0;
	uintptr_t CurMaxBulletNumInOneClip = 0xef0;
	uintptr_t ShootWeaponEntityComp = 0x1038;
	uintptr_t STPlayerController = 0x4090;
	uintptr_t LocalTeamID = 0x8b8;
	uintptr_t CurrWeapon = 0x500;
	uintptr_t RecoilModifierStand = 0x50;
	uintptr_t RecoilModifierCrouch = 0x54;
	uintptr_t RecoilModifierProne = 0x58;
	uintptr_t BulletFireSpeed = 0x508;
	uintptr_t ShootInterval = 0x540;
	uintptr_t WeaponWarnUpTime = 0x630;
	uintptr_t WeaponHitPartCoff = 0x638;
	uintptr_t WeaponHitPartCoffZombie = 0x64c;
	uintptr_t BaseImpactDamage = 0x660;
	uintptr_t BulletMomentum = 0x668;
	uintptr_t MaxDamageRate = 0x758;
	uintptr_t DamageImpulse = 0x8dc;
	uintptr_t AutoAimingConfig = 0x9a0;
	uintptr_t RecoilInfo = 0xab8;
	uintptr_t AccessoriesVRecoilFactor = 0xb28;
	uintptr_t AccessoriesHRecoilFactor = 0xb2c;
	uintptr_t AccessoriesRecoveryFactor = 0xb30;
	uintptr_t GameDeviationFactor = 0xba0;
	uintptr_t RecoilKickADS = 0xc58;
	uintptr_t ExtraHitPerformScale = 0xc5c;
	uintptr_t AnimationKick = 0xc74;
	uintptr_t CurrentFallSpeed = 0x1cc;
	uintptr_t UploadInterval = 0x178;
	uintptr_t VHealthMax = 0x2c0;
	uintptr_t VHealth = 0x2c4;
	uintptr_t VFuelMax = 0x334;
	uintptr_t VFuel = 0x33c;
	uintptr_t BreathMax = 0x16c;
	uintptr_t MinimalViewInfo = 0x10;

}

#endif // KAMID_OFFSETS_H
