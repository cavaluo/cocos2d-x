/*
* cocos2d-x   http://www.cocos2d-x.org
*
* Copyright (c) 2010-2011 - cocos2d-x community
* 
* Portions Copyright (c) Microsoft Open Technologies, Inc.
* All Rights Reserved
* 
* Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. 
* You may obtain a copy of the License at 
* 
* http://www.apache.org/licenses/LICENSE-2.0 
* 
* Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an 
* "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
* See the License for the specific language governing permissions and limitations under the License.
*/

//#include "CCDirector.h"
#include <ppltasks.h>

#include "platform/CCCommon.h"
#include "cocoa/CCString.h"
#include "CCFileUtilsWin8.h"
#include <wrl.h>
//#include <wincodec.h>

#include <mmreg.h>
#include <mfidl.h>
#include <mfapi.h>
//#include <mfreadwrite.h>
#include <mfmediaengine.h>
#include "support/ccUTF8.h"

using namespace Windows::Storage;
using namespace Windows::ApplicationModel;
using namespace std;

NS_CC_BEGIN

// record the resource path
static char s_pszResourcePath[MAX_PATH] = {0};

static void _CheckPath()
{
	if (! s_pszResourcePath[0])
	{
		//WCHAR  wszPath[MAX_PATH];
		//int nNum = WideCharToMultiByte(CP_ACP, 0, wszPath, 
		//	GetCurrentDirectoryW(sizeof(wszPath), wszPath), 
		//	s_pszResourcePath, MAX_PATH, NULL, NULL);
		//      s_pszResourcePath[nNum] = '\\';

		Windows::ApplicationModel::Package^ package = Windows::ApplicationModel::Package::Current;
		Windows::Storage::StorageFolder^ installedLocation = package->InstalledLocation;
		Platform::String^ resPath = installedLocation->Path + "\\Assets\\";
        char* utf8str = cc_utf16_to_utf8((unsigned short*)resPath->Data(), -1, NULL, NULL);
		strcpy_s(s_pszResourcePath, utf8str);
        CC_SAFE_DELETE_ARRAY(utf8str);
	}
}

CCFileUtils* CCFileUtils::sharedFileUtils()
{
    if (s_sharedFileUtils == NULL)
    {
        s_sharedFileUtils = new CCFileUtilsWin8();
        s_sharedFileUtils->init();
    }
    return s_sharedFileUtils;
}

CCFileUtilsWin8::CCFileUtilsWin8()
{
}

bool CCFileUtilsWin8::init()
{
    _CheckPath();
    m_strDefaultResRootPath = s_pszResourcePath;
    return CCFileUtils::init();
}


bool CCFileUtilsWin8::isFileExist(const std::string& strFilePath)
{
    _CheckPath();
    bool ret = false;
    FILE * pf = 0;
    if (strFilePath.length() > 0 && (pf = fopen(strFilePath.c_str(), "rb")))
    {
        ret = true;
        fclose(pf);
    }
    return ret;
}

bool CCFileUtilsWin8::isAbsolutePath(const std::string& strPath)
{
    if (   strPath.length() > 2 
        && ( (strPath[0] >= 'a' && strPath[0] <= 'z') || (strPath[0] >= 'A' && strPath[0] <= 'Z') )
           && strPath[1] == ':')
    {
        return true;
    }
    return false;
}

// unsigned char* CCFileUtilsWin8::getFileDataPlatform(const char* pszFileName, const char* pszMode, unsigned long * pSize)
// {
//     const char *pszPath = fullPathFromRelativePath(pszFileName);

// 	FILE_STANDARD_INFO fileStandardInfo = { 0 };
// 	HANDLE hFile;
// 	DWORD bytesRead = 0;
// 	uint32 dwFileSize = 0;
// 	BYTE* pBuffer = 0;
	
// 	std::wstring path = CCUtf8ToUnicode(pszPath);


// 	do 
// 	{
// 		CREATEFILE2_EXTENDED_PARAMETERS extendedParams = {0};
// 		extendedParams.dwSize = sizeof(CREATEFILE2_EXTENDED_PARAMETERS);
// 		extendedParams.dwFileAttributes = FILE_ATTRIBUTE_NORMAL;
// 		extendedParams.dwFileFlags = FILE_FLAG_SEQUENTIAL_SCAN;
// 		extendedParams.dwSecurityQosFlags = SECURITY_ANONYMOUS;
// 		extendedParams.lpSecurityAttributes = nullptr;
// 		extendedParams.hTemplateFile = nullptr;

// 		// read the file from hardware
// 		hFile = ::CreateFile2(path.c_str(), GENERIC_READ, FILE_SHARE_READ, OPEN_EXISTING, &extendedParams);
// 		if (INVALID_HANDLE_VALUE == hFile)
// 		{
// 			break;
// 		}


// 		BOOL result = ::GetFileInformationByHandleEx(
// 			hFile,
// 			FileStandardInfo,
// 			&fileStandardInfo,
// 			sizeof(fileStandardInfo)
// 			);

// 		//Read error
// 		if ((result == 0) || (fileStandardInfo.EndOfFile.HighPart != 0))
// 		{
// 			break;
// 		}

// 		dwFileSize = fileStandardInfo.EndOfFile.LowPart;
// 		//for read text
// 		pBuffer = new BYTE[dwFileSize+1];
// 		pBuffer[dwFileSize] = 0;
// 		if (!ReadFile(hFile, pBuffer, dwFileSize, &bytesRead, nullptr))
// 		{
// 			break;
// 		}
// 		*pSize = bytesRead;

// 	} while (0);

// 	if (! pBuffer && getIsPopupNotify())
// 	{
// 		std::string title = "Notification";
// 		std::string msg = "Get data from file(";
// 		msg.append(pszPath).append(") failed!");

// 		//CCMessageBox(msg.c_str(), title.c_str());
// 		OutputDebugStringA("CCFileUtils_win8_metro.cpp: Get data from file failed!\n");
// 	}

//     if (hFile != INVALID_HANDLE_VALUE)
//         CloseHandle(hFile);

// 	return pBuffer;
// }

string CCFileUtilsWin8::getWritablePath()
{
	//return the path of Application LocalFolor
	std::string ret;
	StorageFolder^ localFolder = ApplicationData::Current->LocalFolder;
	Platform::String^ folderPath = localFolder->Path + "\\";
	char* utf8str = cc_utf16_to_utf8((unsigned short*)folderPath->Data(), -1, NULL, NULL);
    ret = utf8str;
    CC_SAFE_DELETE_ARRAY(utf8str);
	return ret;
}

NS_CC_END
