#include "DatabaseManager.h"
#include <string>
#include <map>
#include <sstream>

DatabaseManager::DatabaseManager()
{
	resetContentCraftingTable();
}

void DatabaseManager::resetContentCraftingTable()
{
	//TODO mettre les autres types
	this->_contentCraftingTable[BERRY] = 0;
	this->_contentCraftingTable[HERB] = 0;
	this->_contentCraftingTable[WATERBUCKET] = 0;
	this->_contentCraftingTable[MUSHROOM] = 0;
	this->_contentCraftingTable[BOWL] = 0;
	this->_contentCraftingTable[ROPE] = 0;
	this->_contentCraftingTable[FABRIC] = 0;
	this->_contentCraftingTable[FUR] = 0;
	this->_contentCraftingTable[WOODEN_PLANK] = 0;
	this->_contentCraftingTable[SILEX] = 0;
	this->_contentCraftingTable[WOOD] = 0;
	this->_contentCraftingTable[ROCK] = 0;

}

bool DatabaseManager::openDatabase(std::string const&filename)
{
	this->_filename = filename;
	int rc = sqlite3_open(filename.c_str(), &this->_db);
	if (rc)
	{
		std::cout << "ERROR OPEN DATABASE " << std::endl;
		std::cerr << "Error executing SQLite3 query: " << sqlite3_errmsg(this->_db) << std::endl;
	}
	return rc == 0 ? true : false;
}

void DatabaseManager::dumpTable(std::string const &nameTable)
{
	this->_sqlRequest = "SELECT * FROM " + nameTable + ";";
	std::cout << "Retrieving values in " << nameTable << std::endl;
	char **results = NULL;
	int rc;
	int rows, columns;
	sqlite3_get_table(this->_db, this->_sqlRequest.c_str(), &results, &rows, &columns, &this->_error);

	// Display Table
	for (int rowCtr = 0; rowCtr <= rows; ++rowCtr)
	{
		for (int colCtr = 0; colCtr < columns; ++colCtr)
		{
			// Determine Cell Position
			int cellPosition = (rowCtr * columns) + colCtr;

			// Display Cell Value
			std::cout.width(12);
			std::cout.setf(std::ios::left);
			std::cout << results[cellPosition] << " ";
		}

		// End Line
		std::cout << std::endl;

		// Display Separator For Header
		if (0 == rowCtr)
		{
			for (int colCtr = 0; colCtr < columns; ++colCtr)
			{
				std::cout.width(12);
				std::cout.setf(std::ios::left);
				std::cout << "~~~~~~~~~~~~ ";
			}
			std::cout << std::endl;
		}
	}
	sqlite3_free_table(results);
}

bool DatabaseManager::askTable(Type type, std::vector<AEntity *> &craftContent)
{
	char **results = NULL;
	int rows, columns;

	createRequest(craftContent);
	sqlite3_get_table(this->_db, this->_sqlRequest.c_str(), &results, &rows, &columns, &this->_error);
	if (results != NULL)
	{
		std::cout << "RESULT : " << "nbr col : " << columns << " OBEJECT : " << results[1] << std::endl;
	}
	this->resetContentCraftingTable();
	return true;
}

void DatabaseManager::createRequest(std::vector<AEntity *>&list)
{
	std::ostringstream os;
	for (AEntity *u : list)
	{
		this->_contentCraftingTable[u->getType()] += 1;
	}
	this->_sqlRequest = "SELECT OBJECT FROM craft WHERE ";
	auto it = this->_contentCraftingTable.begin();

	while (it != this->_contentCraftingTable.end())
	{
		if (it != this->_contentCraftingTable.begin())
			this->_sqlRequest += " AND ";
		os << (*it).second;
		this->_sqlRequest += typetoString((*it).first);
		this->_sqlRequest += " == ";
		this->_sqlRequest += os.str();
		os.str("");
		++it;
	}
	this->_sqlRequest += ";";
	std::cout << "REQUEST : " << this->_sqlRequest << std::endl;
}

DatabaseManager::~DatabaseManager()
{
}
