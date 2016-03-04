#include "ReadFile.h"
#include "json/document.h"
#include "json/rapidjson.h"
#include "json/prettywriter.h"
#include "json/stringbuffer.h"
#include "cocos2d.h"
#include "Sound.h"
using namespace cocos2d;
static CReadFile * _Instance = nullptr;
CReadFile::CReadFile(void)
{
}


CReadFile::~CReadFile(void)
{
}

CReadFile * CReadFile::getInstance()
{
	if (!_Instance)
	{
		_Instance = new CReadFile;
	}
	return _Instance;
}


void CReadFile::init()
{
	if (!_isFileExist("wangbaoku.json"))
	{//如果没有文件时拷贝一份
		string data = FileUtils::getInstance()->getStringFromFile("wangbaoku.json");
		_saveFile(data.c_str(), "wangbaoku.json");
	}

	loadSpec();
}

bool CReadFile::loadSpec()
{
	string data = _getFileByName("wangbaoku.json");	// 读取文件内容

	rapidjson::Document doc;

	doc.Parse<0>(data.c_str());

	if (doc.HasParseError())
	{// 解析错误
		CCLOG("%s",doc.GetParseError());
		return false;
	}
	else
	{// 开始解析文件
		int j = 0;
		m_boss_time = doc["boss"][j]["time"].GetInt();
		m_boss_hp = doc["boss"][j]["hp"].GetInt();
		setBossTime(m_boss_time);
		setBossHp(m_boss_hp);
		int i = 0;
		m_enemy_time = doc["enemy"][i]["time"].GetDouble();
		setEnemyTime(m_enemy_time);

		
		
	}

	return true;
}

void CReadFile::saveUserInfo()
{
	//*** 生成 json 文件，存储在 getWritablePath 文件夹下 ***
	rapidjson::Document writedoc;
	writedoc.SetObject();
	rapidjson::Document::AllocatorType& allocator = writedoc.GetAllocator();
	rapidjson::Value array1(rapidjson::kArrayType);
	rapidjson::Value array2(rapidjson::kArrayType);

	//rapidjson::Value object(rapidjson::kObjectType);

	rapidjson::Value object1(rapidjson::kObjectType);

	// json object 格式添加 “名称/值” 对
	object1.AddMember("time", getBossTime(),	allocator);
	object1.AddMember("hp", getBossHp(),allocator);
	// json 加入数组
	array1.PushBack(object1, allocator);

	rapidjson::Value object(rapidjson::kObjectType);

	// json object 格式添加 “名称/值” 对
	object.AddMember("time",getEnemyTime(),	allocator);
		
	// json 加入数组
	array2.PushBack(object, allocator);

	// json object 格式添加 “名称/值” 对
	writedoc.AddMember("boss", array1, allocator);
	writedoc.AddMember("enemy", array2, allocator);

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	writedoc.Accept(writer);

	auto path = FileUtils::getInstance()->getWritablePath();	// 写入路径
	path.append("wangbaoku.json");	// 写入文件名
	FILE* file = fopen(path.c_str(), "wb");
	if(file)
	{
		fputs(buffer.GetString(), file);
		fclose(file);
	}
}

string CReadFile::_getFileByName(string pFileName)
{  
	//第一先获取文件的路径  
	string path = FileUtils::getInstance()->getWritablePath() + pFileName;  
	CCLOG("path = %s",path.c_str());  

	//创建一个文件指针  
	FILE* file = fopen(path.c_str(), "r");  

	if (file) {  
		char* buf;  //要获取的字符串  
		int len;    //获取的长度  
		/*获取长度*/  
		fseek(file, 0, SEEK_END);   //移到尾部  
		len = ftell(file);          //提取长度  
		rewind(file);               //回归原位  
		CCLOG("count the file content len = %d",len);  
		//分配buf空间  
		buf = (char*)malloc(sizeof(char) * len + 1);  
		if (!buf) {  
			CCLOG("malloc space is not enough.");  
			return NULL;  
		}  

		//读取文件  
		//读取进的buf，单位大小，长度，文件指针  
		int rLen = fread(buf, sizeof(char), len, file);  
		buf[rLen] = '\0';  
		CCLOG("has read Length = %d",rLen);  
		CCLOG("has read content = %s",buf);  

		string result = buf;  
		fclose(file);  
		free(buf);  
		return result;  
	}  
	else  
		CCLOG("open file error.");  

	return NULL;  
}  

bool CReadFile::_saveFile(const char *pContent, string pFileName)
{  
	//第一获取储存的文件路径  
	string path = FileUtils::getInstance()->getWritablePath() + pFileName;  
	CCLOG("wanna save file path = %s",path.c_str());  

	//创建一个文件指针  
	//路径、模式  
	FILE* file = fopen(path.c_str(), "w");  
	if (file) {  
		fputs(pContent, file);  
		fclose(file);  
	}  
	else  
		CCLOG("save file error.");  

	return false;  
}

bool CReadFile::_isFileExist(string pFileName)
{
	string path = FileUtils::getInstance()->getWritablePath() + pFileName;  
	return FileUtils::getInstance()->isFileExist(path);
}
