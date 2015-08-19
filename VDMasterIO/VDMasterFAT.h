#pragma once

#ifdef VDMASTERIO_EXPORTS
#define VDMASTERIO_API __declspec(dllexport)
#else
#define VDMASTERIO_API __declspec(dllimport)
#endif

#include "BasicTypes.h"

byte* oemName[8] = {};

struct MBRFAT12 
{
	byte bsDriveNumber;
	byte bsReserved;
	byte bsBootSignature;
	dword bsVolumeID;
	byte bsVolumeLabel[11];
	byte bsFSType[8];
};

struct MBRFAT32 
{
	dword bpbSectorsPerFAT32;
	word bpbExtraFlags;
	word bpbFileSystemVersion;
	dword bpbRootCluster;
	word bpbFileSystemInfo;
	word bpbBackupBootSector;
	qword bpbReserved[3];				// 12 bytes, should be always 0
	byte bsDriveNumber;
	byte bsReserved;					// sould always be 0, used by Windows NT
	byte bsBootSignature;
	dword bsVolumeID;
	byte bsVolumeLabel[11];				// string
	byte bsFSType[8];					// string: FAT32   , 16 or 12
};

struct MBRUni
{
	byte jmpIns[3];
	byte bsOEM[8];
	word bpbBytesPerSector;
	byte bpbSectorsPerCluster;
	word bpbReservedSectors;
	byte bpbNumberofFAT;
	word bpbRootEntryCount;
	word bpbTotalSectors16;
	byte bpbMedia;						// lagal values are: 0xF0, 0xF8, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE, and 0xFF
	word bpbSectorsPerFAT16;			// 0 for FAT32, for FAT12/16 contains 16-bit count of the sectors
	word bpbSectorsPerTrack;
	word bpbNumberOfHeads;
	dword bpbHiddenSectors;
	dword bpbTotalSectors32;			// 0 for FAT12/16, for FAT32 containd 32-bit count of the total sectors on the disk ( offset 36 bytes )
};

struct MBR1216
{
	MBRUni mbrUni;
	MBRFAT12 mbrFat;					// size = 62
};

struct MBR
{
	MBRUni mbrUni;
	MBRFAT32 mbrFat;					// size = 90
};

typedef MBR BootLdr, *LPBootLdr;
typedef MBR1216 SBootLdr, *LPSBootLdr;


struct FAT1216
{
	MBR1216 mbr;
	dword dataSectors;
};

typedef FAT1216 *LPFAT1216;

struct FAT32
{
	MBR mbr;
	dword dataSectors;
};

typedef FAT32 *LPFAT32;

#define MEGABYTE 1000000


VDMASTERIO_API class FATFileSystem {
private:
	FAT32 fsStruct;
	dword clustSize;
	dword bytesPerSector;
	qword maxSize;
	
	void init();
	void copy(const FATFileSystem& cpy);
	void computeFATSize();
	qword computeSizeParam(dword fatSz, dword rDirEntries, dword clusterCount);
	void checkFS();

public:
	FATFileSystem();
	FATFileSystem(const FATFileSystem& cpy);
	FATFileSystem(qword fsSize, dword sectorsPerCluster, dword bytesPerSector);

	void setSize(qword size);
	void setClusterSize(dword sectorsPerCluster);
	void setBytesPerSector(dword bytesPerSector);
	
	dword getSize() const;

	FATFileSystem operator=(const FATFileSystem& cpy);

};
