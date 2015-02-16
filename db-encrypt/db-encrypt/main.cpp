#include "wxSqlite/sqlite3.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>
#include <codecvt>
#include <Windows.h>
#include <fstream>
#include <sstream>
#include <vector>

std::string UTF8ToGBK(const char* strUTF8) {
    int len = MultiByteToWideChar(CP_UTF8, 0, strUTF8, -1, NULL, 0);
    wchar_t* wszGBK = new wchar_t[len + 1];
    memset(wszGBK, 0, len * 2 + 2);
    MultiByteToWideChar(CP_UTF8, 0, strUTF8, -1, wszGBK, len);
    len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
    char* szGBK = new char[len + 1];
    memset(szGBK, 0, len + 1);
    WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, NULL, NULL);
    std::string strTemp(szGBK);
    if(wszGBK) delete[] wszGBK;
    if(szGBK) delete[] szGBK;
    return strTemp;
}

std::string GBKToUTF8(const char* strGBK) {
    int len = MultiByteToWideChar(CP_ACP, 0, strGBK, -1, NULL, 0);
    wchar_t* wstr = new wchar_t[len + 1];
    memset(wstr, 0, len + 1);
    MultiByteToWideChar(CP_ACP, 0, strGBK, -1, wstr, len);
    len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
    char* str = new char[len + 1];
    memset(str, 0, len + 1);
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
    std::string strTemp = str;
    if(wstr) delete[] wstr;
    if(str) delete[] str;
    return strTemp;
}
inline bool is_file_exists (const char* name) {
    std::ifstream f(name);
    if (f.good()) {
        f.close();
        return true;
    } else {
        f.close();
        return false;
    }
}
void encrypt_db(const char* path, const char* password) {
    if(!is_file_exists(path)) {
        std::cout << "encrypt failed. Can not find file " << path << std::endl;
        return;
    }

    int result = 0;
    sqlite3 *db = nullptr;
    sqlite3_stmt* stmt;
    result = sqlite3_open(path, &db);
    if(result == SQLITE_OK) {
        result = sqlite3_rekey(db, password, strlen(password));
        //result = sqlite3_key(db, "abcd", 4);
        if(result == SQLITE_OK) {
            sqlite3_close(db);
            std::cout << path << " has been encrypted password is " << password;
        } else {
            sqlite3_close(db);
            if(result == SQLITE_NOTADB) {
                std::cout << "encrypt failed not a db(may be file has been encrypted?)" << std::endl;
            } else {
                std::cout << "encrypt failed.";
            }
            return;
        }
        //result=sqlite3_rekey(db,NULL,0); //清空密码
        //result=sqlite3_exec(db,"PRAGMA synchronous = OFF",0,0,0);    //提高性能
        //result=sqlite3_exec(db,"PRAGMA cache_size = 8000",0,0,0); //加大缓存
        //result=sqlite3_exec(db,"PRAGMA count_changes = 1",0,0,0); //返回改变记录数
        //result=sqlite3_exec(db,"PRAGMA case_sensitive_like = 1",0,0,0); //支持中文LIKE查询

        /* result=sqlite3_exec(db,"CREATE TABLE [MyTable] ([ID] INTEGER PRIMARY KEY NOT NULL,[MyText] TEXT NULL)",0,0,0);
         result=sqlite3_exec(db,"INSERT INTO MyTable (MyText) VALUES ('测试!')",0,0,0);    */
        char* sql = "select * from diseases";
        result = sqlite3_prepare(db, sql, strlen(sql), &stmt, 0);
        if(result != SQLITE_OK) {
            sqlite3_close(db);
        }
        //::SetConsoleOutputCP(1252);
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            const unsigned char* text = sqlite3_column_text(stmt, 0);
            std::string str = UTF8ToGBK((char*)text); // "是阿斯蒂芬阿斯蒂芬";
            //str = (char*)text;
            //std::codecvt_utf8<char16_t> c;
            //char asdfasdfasfdasdf[] = u8"sdf";
            //f(u"a")
            //std::u16string
            std::cout << str << std::endl;
            //wprintf_s(L"%ls", text);
            // printf("%s\n", text);
        }

        sqlite3_finalize(stmt);
        sqlite3_close(db);
    }
}
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

void main() {
    std::cout << "sqlite version:" << SQLITE_VERSION << std::endl;
    std::ifstream fs;
    fs.open("encrypt.txt");
    if(!fs.is_open()) {
        std::cout << "Can not find encrypt.txt" << std::endl;
    }
    std::stringstream ss;
    ss << fs.rdbuf();
    std::string info = ss.str();
    auto lines = split(info, '\n');
    for(auto line : lines) {
        std::vector<std::string> words = split(line, '=');
        std::string dbPath = words[0];
        std::string password = words[1];
        std::cout << "encrypting " << dbPath << std::endl;
        encrypt_db(dbPath.c_str(), password.c_str());
    }
    //std::cout << a[0];
    // std::cout << ss.str() << std::endl;
    system("pause");
}