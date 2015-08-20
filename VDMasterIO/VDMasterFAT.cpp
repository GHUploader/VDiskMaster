
#include "stdafx.h"
#include "VDMasterFAT.h"


void FATFileSystem::init() {
	ZeroMemory(&fsStruct, sizeof(fsStruct));
	clustSize = 0;
	bytesPerSector = 0;
	maxSize = 0;
	rEnt = 0;
	isFSNew = true;
}

void FATFileSystem::copy(const FATFileSystem& cpy) {
	fsStruct = cpy.fsStruct;
	bytesPerSector = cpy.bytesPerSector;
	clustSize = cpy.clustSize;
	maxSize = cpy.maxSize;
	rEnt = cpy.rEnt;
	isFSNew = cpy.isFSNew;
}

void FATFileSystem::computeFATSize() {
	dword fatSz = 0;
	dword rtDirEnt = 0;
	dword clusterCount = 0;

}

qword FATFileSystem::computeSizeParam(dword fatSz, dword rDirEntries, dword clusterCount) {
	qword ret = fatSz + (rDirEntries * 32);
	qword dataSize = clusterCount * fsStruct.mbr.mbrUni.bpbSectorsPerCluster;
	ret += dataSize;
	return ret;
}

void FATFileSystem::checkFS() {				// check if the parameters passed will create a valid file system
	dword mbCount = maxSize / MEGABYTE;
	dword bpSector = clustSize * bytesPerSector;
	dword maxBpSect = 32 * KILOBYTE;
	if (bpSector > maxBpSect)
		throw InvalidFATParameter();
}

// public

FATFileSystem::FATFileSystem() {
	init();
}

FATFileSystem::FATFileSystem(const FATFileSystem& cpy) {
	init();
	copy(cpy);
}

FATFileSystem::FATFileSystem(qword fsSize, dword bytesPerCluster, dword bytesPerSector) {
	init();
	setSize(fsSize);
	setClusterSize(bytesPerSector);
	setBytesPerSector(bytesPerSector);
}

FATFileSystem::~FATFileSystem() {

}

void FATFileSystem::setSize(qword fsSize) {
	maxSize = fsSize;
	checkFS();
}

void FATFileSystem::setClusterSize(dword sectorsPerCluster) {
	clustSize = sectorsPerCluster;
	checkFS();
}

void FATFileSystem::setBytesPerSector(dword bytesPerSector) {
	this->bytesPerSector = bytesPerSector;
	checkFS();
}

dword FATFileSystem::getSize() const {
	return fsStruct.dataSectors;
}

FATFileSystem FATFileSystem::operator=(const FATFileSystem& cpy) {
	copy(cpy);
	return *this;
}