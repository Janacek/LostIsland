#pragma once

#include <iostream>
#include <map>
#include "AEntity.h"
#include "sqlite3.h"

class DatabaseManager
{
public:
	DatabaseManager();
	bool openDatabase(std::string const&);
	void dumpTable(std::string const &tableName = "craft");
	bool askTable(Type, std::vector<AEntity *> &_craftContent);
	~DatabaseManager();

private:
	void resetContentCraftingTable();
	void createRequest(std::vector<AEntity *>&);

	std::string _filename;
	std::map<Type, int> _contentCraftingTable;
	sqlite3	*_db;
	char	*_error;
	std::string _sqlRequest;
};

