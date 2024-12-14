#ifndef KAMID_SUPPORT_H
#define KAMID_SUPPORT_H

#include "socket.h"

#define PI 3.141592653589793238

ssize_t process_v(pid_t __pid, struct iovec* __local_iov, unsigned long __local_iov_count, struct iovec* __remote_iov, unsigned long __remote_iov_count, unsigned long __flags) {
	return syscall(process_vm_readv_syscall, __pid, __local_iov, __local_iov_count, __remote_iov, __remote_iov_count, __flags);
}

ssize_t process_v2(pid_t __pid, struct iovec* __local_iov, unsigned long __local_iov_count, struct iovec* __remote_iov, unsigned long __remote_iov_count, unsigned long __flags) {
	return syscall(process_vm_writev_syscall, __pid, __local_iov, __local_iov_count, __remote_iov, __remote_iov_count, __flags);
}

int pvm(uintptr_t address, void* buffer,int size) {
	struct iovec local[1];
	struct iovec remote[1];

	local[0].iov_base = (void*)buffer;
	local[0].iov_len = size;
	remote[0].iov_base = (void*)address;
	remote[0].iov_len = size;
	ssize_t bytes = process_v(pid, local, 1, remote, 1, 0);
	return bytes == size;
}

void pvm2(uintptr_t address, void* buffer,int size) {
	struct iovec local[1];
	struct iovec remote[1];

	local[0].iov_base = (void*)buffer;
	local[0].iov_len = size;
	remote[0].iov_base = (void*)address;
	remote[0].iov_len = size;

	process_v2(pid, local, 1, remote, 1, 0);
}

struct D3DMatrix ToMatrixWithScale(struct Vec3 translation,struct Vec3 scale,struct Vec4 rot)
{
	struct D3DMatrix m;

	m._41 = translation.X;
	m._42 = translation.Y;
	m._43 = translation.Z;

	float x2 = rot.X + rot.X;
	float y2 = rot.Y + rot.Y;
	float z2 = rot.Z + rot.Z;

	float xx2 = rot.X * x2;
	float yy2 = rot.Y * y2;
	float zz2 = rot.Z * z2;

	m._11 = (1.0f - (yy2 + zz2)) * scale.X;
	m._22 = (1.0f - (xx2 + zz2)) * scale.Y;
	m._33 = (1.0f - (xx2 + yy2)) * scale.Z;

	float wx2 = rot.W * x2;
	float yz2 = rot.Y * z2;

	m._23 = (yz2 + wx2) * scale.Y;
	m._32 = (yz2 - wx2) * scale.Z;

	float xy2 = rot.X * y2;
	float wz2 = rot.W * z2;

	m._12 = (xy2 + wz2) * scale.X;
	m._21 = (xy2 - wz2) * scale.Y;

	float xz2 = rot.X * z2;
	float wy2 = rot.W * y2;

	m._13 = (xz2 - wy2) * scale.X;
	m._31 = (xz2 + wy2) * scale.Z;

	m._14 = 0.0f;
	m._24 = 0.0f;
	m._34 = 0.0f;
	m._44 = 1.0f;

	return m;
}

struct Vec3 mat2Cord(struct D3DMatrix pM1,struct D3DMatrix pM2)
{
	struct  Vec3 pOut;

	pOut.X = pM1._41 * pM2._11 + pM1._42 * pM2._21 + pM1._43 * pM2._31 + pM1._44 * pM2._41;
	pOut.Y = pM1._41 * pM2._12 + pM1._42 * pM2._22 + pM1._43 * pM2._32 + pM1._44 * pM2._42;
	pOut.Z = pM1._41 * pM2._13 + pM1._42 * pM2._23 + pM1._43 * pM2._33 + pM1._44 * pM2._43;

	return pOut;
}

uintptr_t getBase()
{
    FILE *fp;
    uintptr_t addr = 0;
    char filename[40], buffer[1024];
    snprintf(filename, sizeof(filename), "/proc/%d/maps", pid);
    fp = fopen(filename, "rt");
    if (fp != NULL)
    {
        while (fgets(buffer, sizeof(buffer), fp)) {
            if (strstr(buffer, "libUE4.so")) {
                addr = (uintptr_t)strtoul(buffer, NULL, 16);
                break;
            }
        }
        fclose(fp);
    }
    return addr;
}

pid_t getPid(char * name)
{
	char text[69];
	pid_t pid = 0;
	sprintf(text,"pidof %s",name);
	FILE *chkRun = popen(text, "r");
	if (chkRun)
	{
		char output[10];
		fgets(output ,10,chkRun);
		pclose(chkRun);
		pid= atoi(output);
	}
	if (pid < 10)
	{
		DIR* dir = NULL;
		struct dirent* ptr = NULL;
		FILE* fp = NULL;
		char filepath[256];
		char filetext[128];
		dir = opendir("/proc");
		if (NULL != dir)
		{
			while ((ptr = readdir(dir)) != NULL)
			{
				if ((strcmp(ptr->d_name, ".") == 0) || (strcmp(ptr->d_name, "..") == 0))
					continue;
				if (ptr->d_type != DT_DIR)
					continue;
				sprintf(filepath, "/proc/%s/cmdline", ptr->d_name);
				fp = fopen(filepath, "r");
				if (NULL != fp)
				{
					fgets(filetext, sizeof(filetext), fp);
					if (strcmp(filetext, name) == 0)
					{
						fclose(fp);
						break;
					}
					fclose(fp);
				}
			}
		}
		if (readdir(dir) == NULL)
		{
			closedir(dir);
			return 0;
		}
		closedir(dir);
		pid= atoi(ptr->d_name);
	}
	return pid;
}

int isValidPlayer(int oType) {
	if (oType == 0x3ec2a00 || oType == 0x3ec2800)
		return 1;
    return 0;
}

uintptr_t getA(uintptr_t address)
{
	uintptr_t buff;
    pvm(address, &buff, SIZE);
    return buff;
}

float getF(uintptr_t address)
{
	float buff;
	pvm(address, &buff, 4);
	return buff;
}

template<typename T>
T Read(uintptr_t address) {
    T data;
    pvm(address, &data, sizeof(T));
    return data;
}

int isValid(uintptr_t addr)
{
    if (addr < 0x10000000 || addr>0xEFFFFFFF || addr % SIZE != 0)
        return 0;
    return 1;
}

int isValid64(uintptr_t addr)
{
    if (addr < 0x1000000000 || addr>0xEFFFFFFFFF || addr % SIZE != 0)
        return 0;
    return 1;
}

float getDistance(struct Vec3 mxyz,struct Vec3 exyz)
{
	return sqrt ((mxyz.X-exyz.X)*(mxyz.X-exyz.X)+(mxyz.Y-exyz.Y)*(mxyz.Y-exyz.Y)+(mxyz.Z-exyz.Z)*(mxyz.Z-exyz.Z))/100;
}

struct Vec3 World2Screen(struct D3DMatrix viewMatrix, struct Vec3 pos)
{
	struct Vec3 screen;
	float screenW = (viewMatrix._14 * pos.X) + (viewMatrix._24 * pos.Y) + (viewMatrix._34 * pos.Z) + viewMatrix._44;

	if (screenW < 0.01f)
		screen.Z = 1;
	else
		screen.Z = 0;

	float screenX = (viewMatrix._11 * pos.X) + (viewMatrix._21 * pos.Y) + (viewMatrix._31 * pos.Z) + viewMatrix._41;
	float screenY = (viewMatrix._12 * pos.X) + (viewMatrix._22 * pos.Y) + (viewMatrix._32 * pos.Z) + viewMatrix._42;
	
	screen.Y = (height / 2) - (height / 2) * screenY / screenW;
	screen.X = (width / 2) + (width / 2) * screenX / screenW;

	return screen;
}

struct Vec2 World2ScreenMain(struct D3DMatrix viewMatrix, struct Vec3 pos)
{
	struct Vec2 screen;
	float screenW = (viewMatrix._14 * pos.X) + (viewMatrix._24 * pos.Y) + (viewMatrix._34 * pos.Z) + viewMatrix._44;
	float screenX = (viewMatrix._11 * pos.X) + (viewMatrix._21 * pos.Y) + (viewMatrix._31 * pos.Z) + viewMatrix._41;
	float screenY = (viewMatrix._12 * pos.X) + (viewMatrix._22 * pos.Y) + (viewMatrix._32 * pos.Z) + viewMatrix._42;
	
	screen.Y = (height / 2) - (height / 2) * screenY / screenW;
	screen.X = (width / 2) + (width / 2) * screenX / screenW;

	return screen;
}

struct D3DMatrix getOMatrix(uintptr_t boneAddr)
{
  float oMat[11];
  pvm(boneAddr,&oMat,sizeof(oMat));
  
  rot.X=oMat[0];
	rot.Y=oMat[1];
	rot.Z=oMat[2];
	rot.W=oMat[3];
			
	tran.X=oMat[4];
	tran.Y=oMat[5];
	tran.Z=oMat[6];
			
	scale.X=oMat[8];
	scale.Y=oMat[9];
	scale.Z=oMat[10];
	
	return ToMatrixWithScale(tran,scale,rot);
}

struct Vec2 getPointingAngle(struct Vec3 camera, struct Vec3 xyz, float distance)
{
	struct Vec2 PointingAngle;
	float ytime = distance / 88000;

	xyz.Z = xyz.Z + 360 * ytime * ytime;

	float zbcx = xyz.X - camera.X;
	float zbcy = xyz.Y - camera.Y;
	float zbcz = xyz.Z - camera.Z;
	PointingAngle.Y = atan2(zbcy, zbcx) * 180 / PI;	// 57.3
	PointingAngle.X = atan2(zbcz, sqrt(zbcx * zbcx + zbcy * zbcy)) * 180 / PI;

	return PointingAngle;
}

char* getText(uintptr_t addr)
{
	static char txt[42];
	memset(txt, 0, 42);
	char buff[41];
	pvm(addr + 4+SIZE, &buff, 41);
	int i;
	for (i = 0; i < 41; i++) {
		if (buff[i] == 0)
			break;
		txt[i] = buff[i];
		if (buff[i] == 67 && i > 10)
			break;
	}
	txt[i + 1] = '\0';
	return txt;
}

char *getNameByte(uintptr_t address)
{
	char static lj[64];
	memset(lj, 0, 64);
	unsigned short int nameI[32];
	pvm(address, nameI, sizeof(nameI));
	char s[10];
	int i;
	for (i = 0; i < 32; i++)
	{
		if (nameI[i] == 0)
			break;
		sprintf(s, "%d:", nameI[i]);
		strcat(lj, s);
	}
	lj[63] = '\0';

	return lj;
}

enum type {
	TYPE_DWORD,
	TYPE_FLOAT
};

void WriteDword(uintptr_t address, int value) {
	pvm2(address, &value, 4);
}

void WriteFloat(uintptr_t address, float value) {
	pvm2(address, &value, 4);
}

void Write(uintptr_t address, const char *value, type TYPE) {
	switch(TYPE) {
		case TYPE_DWORD:
			WriteDword(address, atoi(value));
			break;
		case TYPE_FLOAT:
			WriteFloat(address, atoi(value));
			break;
	}
}

// START 32
struct Actors32
{
	uint32_t Enc_1, Enc_2;
	uint32_t Enc_3, Enc_4;
};

struct Chunk32
{
	uint32_t val_1, val_2;
	uint32_t val_3, val_4;
};

uint32_t DecryptActorsArray32(uint32_t uLevel, int Actors_Offset, int EncryptedActors_Offset)
{
	if (uLevel < 0x10000000)
		return 0;

	if (Read<uint32_t>(uLevel + Actors_Offset) > 0)
		return uLevel + Actors_Offset;

	if (Read<uint32_t>(uLevel + EncryptedActors_Offset) > 0)
		return uLevel + EncryptedActors_Offset;

	auto AActors = Read < Actors32 > (uLevel + EncryptedActors_Offset + 0x0C);

	if (AActors.Enc_1 > 0)
	{
		auto Enc = Read < Chunk32 > (AActors.Enc_1 + 0x80);

		return (Read<uint8_t>(AActors.Enc_1 + Enc.val_1)
				| (Read<uint8_t>(AActors.Enc_1 + Enc.val_2) << 8)
				| (Read<uint8_t>(AActors.Enc_1 + Enc.val_3) << 0x10)
				| (Read<uint8_t>(AActors.Enc_1 + Enc.val_4) << 0x18));
	}
	else if (AActors.Enc_2 > 0)
	{
		auto Lost_Actors = Read<uint32_t>(AActors.Enc_2);
		if (Lost_Actors > 0)
		{
			return ((unsigned short)Lost_Actors - 0x400) & 0xFF00
				| (unsigned char)(Lost_Actors - 0x04)
				| (Lost_Actors + 0xFC0000) & 0xFF0000
				| (Lost_Actors - 0x4000000) & 0xFF000000;
		}
	}
	else if (AActors.Enc_3 > 0)
	{
		auto Lost_Actors = Read<uint32_t>(AActors.Enc_3);
		if (Lost_Actors > 0)
		{
			return (Lost_Actors >> 0x18) | (Lost_Actors << (32 - 0x18));
		}
	}
	else if (AActors.Enc_4 > 0)
	{
		auto Lost_Actors = Read<uint32_t>(AActors.Enc_4);
		if (Lost_Actors > 0)
		{
			return Lost_Actors ^ 0xCDCD00;
		}
	}
	return 0;
}
// END 32

// START 64
struct Actors64
{
	uint64_t Enc_1, Enc_2;
	uint64_t Enc_3, Enc_4;
};

struct Chunk64
{
	uint64_t val_1, val_2, val_3, val_4;
	uint64_t val_5, val_6, val_7, val_8;
};

uint64_t DecryptActorsArray64(uint64_t uLevel, int Actors_Offset, int EncryptedActors_Offset)
{
	if (uLevel < 0x10000000)
		return 0;

	if (Read<uint64_t>(uLevel + Actors_Offset) > 0)
		return uLevel + Actors_Offset;

	if (Read<uint64_t>(uLevel + EncryptedActors_Offset) > 0)
		return uLevel + EncryptedActors_Offset;

	auto AActors = Read < Actors64 > (uLevel + EncryptedActors_Offset + 0x10);

	if (AActors.Enc_1 > 0)
	{
		auto Enc = Read < Chunk64 > (AActors.Enc_1 + 0x80);
		return (((Read<uint8_t>(AActors.Enc_1 + Enc.val_1)
				| (Read<uint8_t>(AActors.Enc_1 + Enc.val_2) << 8))
				| (Read<uint8_t>(AActors.Enc_1 + Enc.val_3) << 0x10)) & 0xFFFFFF
				| ((uint64_t) Read<uint8_t>(AActors.Enc_1 + Enc.val_4) << 0x18)
				| ((uint64_t) Read<uint8_t>(AActors.Enc_1 + Enc.val_5) << 0x20)) & 0xFFFF00FFFFFFFFFF
				| ((uint64_t) Read<uint8_t>(AActors.Enc_1 + Enc.val_6) << 0x28)
				| ((uint64_t) Read<uint8_t>(AActors.Enc_1 + Enc.val_7) << 0x30) 
				| ((uint64_t) Read<uint8_t>(AActors.Enc_1 + Enc.val_8) << 0x38);
	}
	else if (AActors.Enc_2 > 0)
	{
		auto Lost_Actors = Read<uint64_t>(AActors.Enc_2);
		if (Lost_Actors > 0)
		{
			return (uint16_t) (Lost_Actors - 0x400) & 0xFF00
				| (uint8_t) (Lost_Actors - 0x04)
				| (Lost_Actors + 0xFC0000) & 0xFF0000
				| (Lost_Actors - 0x4000000) & 0xFF000000
				| (Lost_Actors + 0xFC00000000) & 0xFF00000000
				| (Lost_Actors + 0xFC0000000000) & 0xFF0000000000
				| (Lost_Actors + 0xFC000000000000) & 0xFF000000000000
				| (Lost_Actors - 0x400000000000000) & 0xFF00000000000000;
		}
	}
	else if (AActors.Enc_3 > 0)
	{
		auto Lost_Actors = Read<uint64_t>(AActors.Enc_3);
		if (Lost_Actors > 0)
		{
			return (Lost_Actors >> 0x38) | (Lost_Actors << (64 - 0x38));
		}
	}
	else if (AActors.Enc_4 > 0)
	{
		auto Lost_Actors = Read<uint64_t>(AActors.Enc_4);
		if (Lost_Actors > 0)
		{
			return Lost_Actors ^ 0xCDCD00;
		}
	}
	return 0;
}
// END 64
#endif
