

#ifndef CHERRYBERKELEYDB_H_
#define CHERRYBERKELEYDB_H_



#ifdef BERKELEYDB_EXPORTS
#define BERKELEYDB_API __declspec(dllexport)
#else
#define BERKELEYDB_API __declspec(dllimport)
#endif

#include <string>
#include "db_cxx.h"

#pragma comment(lib, "libdb62.lib")


class BERKELEYDB_API BerkeleyDb
{
public:
	// Constructor requires a path to the database,
	// and a database name.
	BerkeleyDb(std::string &path, std::string &dbName,
		bool isSecondary = false);

	// Our destructor just calls our private close method.
	~BerkeleyDb() { close(); }

	inline Db &getDb() { return db_; }

private:
	Db db_;
	std::string dbFileName_;
	u_int32_t cFlags_;

	// Make sure the default constructor is private
	// We don't want it used.
	BerkeleyDb() : db_(NULL, 0) {}

	// We put our database close activity here.
	// This is called from our destructor. In
	// a more complicated example, we might want
	// to make this method public, but a private
	// method is more appropriate for this example.
	void close();
};



#endif

