#include "CEntity.h"

std::vector<CEntityInfo> CEntityInfo::EntityInfoList;

CEntityInfo::CEntityInfo()
{
	//
}

int CEntityInfo::OnLoad(char* File)
{
	EntityInfoList.clear();

	// Always load commons first
	if (!LoadCommons()) return -1;

	FILE* FileHandle = fopen(File, "r");

	if (FileHandle == NULL) return -1;

	int TableID;
	fscanf(FileHandle, "%d\n", &TableID);

	CEntityInfo tempInfo;
	while (fscanf(FileHandle, "%d:%d:%d:%d:%d:%d\n", &tempInfo.Xo, &tempInfo.Yo, &tempInfo.W, &tempInfo.H,
		&tempInfo.NumCols, &tempInfo.NumRows) == 6)
	{
		tempInfo.Common = false;
		EntityInfoList.push_back(tempInfo);
	}
	fclose(FileHandle);
	return TableID;
}

bool CEntityInfo::LoadCommons()
{
	FILE* FileHandle = fopen("../res/npc/common.tbl", "r");
	if (FileHandle == NULL) return false;

	int ID;
	fscanf(FileHandle, "%d\n", &ID);

	CEntityInfo tempInfo;
	while (fscanf(FileHandle, "%d:%d:%d:%d:%d:%d\n", &tempInfo.Xo, &tempInfo.Yo, &tempInfo.W, &tempInfo.H,
		&tempInfo.NumCols, &tempInfo.NumRows) == 6)
	{
		tempInfo.Common = true;
		EntityInfoList.push_back(tempInfo);
	}
	fclose(FileHandle);
	return true;
}
