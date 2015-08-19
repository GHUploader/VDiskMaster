
#include "stdafx.h"
#include "VDMasterFAT.h"


void FATFileSystem::init() {
	ZeroMemory(&fsStruct, sizeof(fsStruct));
}

void FATFileSystem::copy(const FATFileSystem& cpy) {
	fsStruct = cpy.fsStruct;
	bytesPerSector = cpy.bytesPerSector;
	clustSize = cpy.clustSize;
	maxSize = cpy.maxSize;
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

void FATFileSystem::checkFS() {
	dword mbCount = maxSize / MEGABYTE;

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