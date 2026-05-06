#pragma once

#include <array>
#include <cstdio>
#include <fstream> 
#include <iostream>
#include <cctype>
#include <cstdint>
#include <algorithm>
#include <string>
#include <vector>
#include <cassert>
#include <map>

#include "ATree.hpp"
#include "Reporter.hpp"

#define GetBytes(Source, Destination, Index, BytesToCopy) memcpy(&Destination, (Source + Index), BytesToCopy), Index+=BytesToCopy

#define CA_DATABASE_VERSION 2

class BuildManager
{
public:
	typedef struct
	{
		float x;
		float y;
		float z;
	} Vertex;

	typedef struct
	{
		Vertex center;
		float radius;
	} ColSphere;

	typedef struct
	{
		Vertex min;
		Vertex max;
	} ColBox;

	typedef struct
	{
		Vertex* a;
		Vertex* b;
		Vertex* c;
	} ColFace;

	typedef struct
	{
		std::string name;
		uint16_t modelid;

		uint32_t num_spheres;
		uint32_t num_boxes;
		uint32_t num_faces;

		ColSphere* spheres;
		ColBox* boxes;
		ColFace* faces;
	} ColModel;

	typedef struct
	{
		float x;
		float y;
		float z;
		float w;
	} IPLRot;

	typedef struct
	{
		uint16_t modelid;
		Vertex Position;
		IPLRot Rotation;
		std::string Modelname;
	} IPLObject;

	typedef struct
	{
		uint16_t modelid;
		std::string ModelName;
		float DrawDist;
	} Modelid_Modelname_Struct;

private:
	Reporter* reporter;					 // <<< NOVO: ponteiro para o reporter
	std::string GTAInstallDirectory;
	std::string OutfileDirectory;

	std::vector<IPLObject> IPLArray;
	std::vector<ColModel> COLArray;
	ATree<int> modelnameLookup;
	std::map<int, std::string> modelidLookup;
	std::vector<Modelid_Modelname_Struct> Modelid_Modelname_Vector;

	std::vector<std::string> ImageFileNames;
	std::vector<std::string> CollisionFileNames;
	std::vector<std::string> ItemPlacementFileNames;
	std::vector<std::string> ItemDefinitionFileNames;

	bool ReadItemDefinitionFile(const char fname[]);
	bool ReadItemPlacementData(const char fname[]);
	void ReadBinaryItemPlacementData(char* RawIPLData);

	bool ReadColFile(const char fname[]);
	void InitDirectoryNames();

	bool UsingSAMPObjects;
	bool UsingCustomObjects;
	
public:
	BuildManager(Reporter* rep, std::string& GTADirectory, std::string& OutDirectory, bool SAMPObjects, bool CustomObjects);

	bool ExtractImageFiles();
	bool ExtractCollisionFiles();
	bool ExtractItemPlacementFiles();
	bool ExtractItemDefinitionFiles();
	void PrepareDatabaseStructures();

	bool WriteBinaryFile(const char fname[]);

private:
    bool file_exists(const std::string& path);
};