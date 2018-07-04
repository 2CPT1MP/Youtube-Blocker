#include <iostream>
#include <fstream>
#include <istream>
#include <string>

static bool BackupExists();
static void UnblockSite();
static void BlockSite();
static void BackupHosts();

static const char* FILENAME = "C:\\Windows\\System32\\drivers\\etc\\hosts";
static const char* BACKUP_NAME = "C:\\Windows\\System32\\drivers\\etc\\hosts.bk";
static const char* BLOCK_STR = "127.0.0.1 www.youtube.com";


int main()
{
	std::cout << "\nYoutube Blocker v0.1 by 2CPT1MP\n\n";

	bool invalidInput = false;

	do {
		std::cout << "1 Block  2 Unblock  3 Exit\nChoose operation: ";

		std::string strIn;
		std::getline(std::cin, strIn);

		switch (strIn[0])
		{
		case '1':
			BackupHosts();
			BlockSite();

			std::cout << "\nBlocking...\n";

			break;
		case '2':
			UnblockSite();
			std::remove(BACKUP_NAME);
			break;

		case '3':
			return 0;
		default:
			std::cout << "\nInvalid Input. Try again.\n\n";
			invalidInput = true;
		}

	} while (invalidInput);
	return 0;
}

static bool BackupExists()
{
	std::fstream checkStr(BACKUP_NAME);
	if (checkStr)
	{
		checkStr.close();
		return true;
	}
	checkStr.close();
	return false;
}


static void BackupHosts()
{
	if (BackupExists())
		return;

	//DUPLICATES
	std::ifstream inStream;
	inStream.open(FILENAME, std::ifstream::in);

	std::fstream backupOut;
	backupOut.open(BACKUP_NAME, std::fstream::out);

	char c = inStream.get();

	while (inStream.good())
	{
		backupOut << c;
		c = inStream.get();
	}

	inStream.close();
	backupOut.close();
}

static void BlockSite()
{

	std::fstream blockStream;
	blockStream.open(FILENAME, std::fstream::app);
	blockStream << std::endl << BLOCK_STR << std::endl;
	blockStream.close();
}



static void UnblockSite() {

	if (!BackupExists())
		return;


	std::ifstream backupReader;
	backupReader.open(BACKUP_NAME);

	std::fstream writeStream;
	writeStream.open(FILENAME, std::fstream::out);

	char readChar = backupReader.get();

	while (backupReader.good())
	{
		writeStream << readChar;
		readChar = backupReader.get();
	}

	writeStream.close();
	backupReader.close();
}