# Milioners game
## Project for first semester of Informatics on faculty of Automatic control, Robotics and Computer Science on Silesian University of Technology

## Project made for learning purposes, not for commercial use.

## For contact regarding this game please use following e-mail address: [hannapotepa@icloud.com](mailto:hannapotepa@icloud.com)

## To run app please use console

## To compile this app please use cmake
### Proper file's tree of compiled game:
```
├── databse/
│   ├── .env
│   ├── dbQuest.sql
│   └── dbSchem.sql
└── mil (depending on operating system)
```

## Remember! This app use mysql xdevapi, you must enable this in your database
### Content of the database/.env file
```
DB_HOST=<your_mysql_host>
DB_PORT=<your_mysql_xdevapi_port>
DB_USER=<your_mysql_user>
DB_PASS=<your_mysql_password>
DB_NAME=<your_mysql_database_name>
```

## This app need active connection to database
### It generates automatically schema with tables and inserts questions, u can change it in database/dbInit.cpp file and database/*.sql files

### This app has one file that executes mysql querys, this file is database/dbQuerys.cpp
1. `dbQuerys::selRows(mysqlx::string)` method need query string as argument and return `std::optional<mysqlx::RowResult> value
2. `dbQuerys::insertLine(mysqlx::string)` method need query string as argument and return `int64_t` value as id of inserted line to database
3. `dbQuerys::updateLine(mysqlx::string)` method need query string as argument and return `bool` value as success of updating rows