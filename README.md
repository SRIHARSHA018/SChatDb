# SChatDb

## Introduction:

- Schat is the chat application built in QT6. QT makes life simple with Graphical User Interfaces and other operations performed by Signals and Slots features.

- Qt also porvides networking like TCP/UDP protocals, Managing databases and many other.

- This Application uses the [Postegresql 9.6](https://www.postgresql.org/about/news/postgresql-96-released-1703/) as server. This provides flexible communication cross plaform devices.

- Postegresql also provides notification system. It automatically notify the clients.
- With [Qt6](https://www.qt.io/product/qt6) and [Postegresql 9.6](https://www.postgresql.org/about/news/postgresql-96-released-1703/) It will be a flexible system to make a client server model.

- Most of the code functionality is based on generating queries and accesing ui elements in Qt.

## Prerequisites:

1. [Qt6](https://www.qt.io/product/qt6)
2. [Postegresql 9.6](https://www.postgresql.org/about/news/postgresql-96-released-1703/)
3. pgAdmin4 (optional)
4. Ubuntu OS

## Building App:

- Using qmake requires Qt6 to be installed in the desktop. Use this snippet of code to build. Build files are already in the BUILD folder.

```
$ qmake SRC/ClientWithDb.pro
```

- With above command it will generate makefile in the output directory.Now, this is time to generate the app with specific configurations. Use the below command in same directory of MakeFile.

```
$ make
```

- After Running the make file go to directory where the executable files are generated. In this BUILD/debug or BUILD/release. These two folders depend on how you use make command to generate.
- Use the below command to run the App. go to specific configuration outputs of make. Use this command to run the app.

```
$ ./ClientWithDb
```

## Notes:

- Testcases will run before the app run. This may not affect from running app (Please make sure why testcases are failed).
- Make sure to start server in postegres using pgadmin4 or command line.
- Qt6 sometimes throw error on Qpsql driver not found. So make sure to give the Qt6/plugins/sqldrivers as a environment path variable. So it will detect the drivers.
- Please make sure of server schema should match the app configuration.
- Inorder to avoid problems i also included the server database of postegresql in SRC/database/ folder. This a backup file so, restore in pgadmin4 under a database.
