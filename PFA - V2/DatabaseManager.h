#pragma once

#include <iostream>
#include <map>
#include "IEntity.h"
#include "sqlite3.h"

class DatabaseManager
{
public:
	DatabaseManager();
	bool openDatabase(std::string const&);
	void dumpTable(std::string const &tableName = "craft");
	bool askTable(Type, std::vector<IEntity *> &_craftContent);
	~DatabaseManager();

private:
	void resetContentCraftingTable();
	void createRequest(std::vector<IEntity *>&);

	std::string _filename;
	std::map<Type, int> _contentCraftingTable;
	sqlite3	*_db;
	char	*_error;
	std::string _sqlRequest;
};

