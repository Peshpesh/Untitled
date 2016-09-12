#include "CEntity.h"

// std::vector<CEntityInfo> CEntityInfo::EntityInfoList;
std::vector<CEntityInfo> CEntityInfo::Com_EntityInfo;
std::vector<CEntityInfo> CEntityInfo::Unq_EntityInfo;


CEntityInfo::CEntityInfo()
{
	//
}

// int CEntityInfo::OnLoad(char* File)
// {
// 	EntityInfoList.clear();
//
// 	// Always load commons first
// 	if (!LoadCommons()) return -1;
//
// 	FILE* FileHandle = fopen(File, "r");
//
// 	if (FileHandle == NULL) return -1;
//
// 	int TableID;
// 	fscanf(FileHandle, "%d\n", &TableID);
//
// 	CEntityInfo tempInfo;
// 	while (fscanf(FileHandle, "%d:%d:%d:%d:%d:%d\n", &tempInfo.Xo, &tempInfo.Yo, &tempInfo.W, &tempInfo.H,
// 		&tempInfo.NumCols, &tempInfo.NumRows) == 6)
// 	{
// 		tempInfo.Common = false;
// 		EntityInfoList.push_back(tempInfo);
// 	}
// 	fclose(FileHandle);
// 	return TableID;
// }

// bool CEntityInfo::LoadCommons()
bool CEntityInfo::LoadCommon()
{
	Com_EntityInfo.clear();

	FILE* FileHandle = fopen("../res/npc/common.tbl", "r");
	if (FileHandle == NULL) return false;

	CEntityInfo tempInfo;
	while (fscanf(FileHandle, "%d:%d:%d:%d:%d:%d\n", &tempInfo.Xo, &tempInfo.Yo, &tempInfo.W, &tempInfo.H,
		&tempInfo.NumCols, &tempInfo.NumRows) == 6)
	{
		Com_EntityInfo.push_back(tempInfo);
	}
	fclose(FileHandle);
	return true;
}

int CEntityInfo::LoadUnique(char* File)
{
	Unq_EntityInfo.clear();

	FILE* FileHandle = fopen(File, "r");
	if (FileHandle == NULL) return -1;

	int TableID;
	fscanf(FileHandle, "%d\n", &TableID);

	CEntityInfo tempInfo;
	while (fscanf(FileHandle, "%d:%d:%d:%d:%d:%d\n", &tempInfo.Xo, &tempInfo.Yo, &tempInfo.W, &tempInfo.H,
		&tempInfo.NumCols, &tempInfo.NumRows) == 6)
	{
		Unq_EntityInfo.push_back(tempInfo);
	}
	fclose(FileHandle);
	return TableID;
}
