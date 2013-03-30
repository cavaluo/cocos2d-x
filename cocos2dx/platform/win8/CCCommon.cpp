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

#include "platform/CCCommon.h"

#define MAX_LEN         (cocos2d::kMaxLogLen + 1)

#include <Windows.h>

#include <stdio.h>
#include <varargs.h>

NS_CC_BEGIN;

void CCLog(const char * pszFormat, ...)
{
    char szBuf[MAX_LEN];

    va_list ap;
    va_start(ap, pszFormat);
    vsnprintf_s(szBuf, MAX_LEN, MAX_LEN, pszFormat, ap);
    va_end(ap);

    WCHAR wszBuf[MAX_LEN] = {0};
    MultiByteToWideChar(CP_UTF8, 0, szBuf, -1, wszBuf, sizeof(wszBuf));
    OutputDebugStringW(wszBuf);
    OutputDebugStringW(L"\n");
}

void CCMessageBox(const char * pszMsg, const char * pszTitle)
{
    // Create the message dialog and set its content
//     Platform::String^ message = ref new Platform::String(CCUtf8ToUnicode(pszMsg).c_str());
//     Platform::String^ title = ref new Platform::String(CCUtf8ToUnicode(pszTitle).c_str());
    //Windows::UI::Popups::MessageDialog^ msg = ref new Windows::UI::Popups::MessageDialog(message, title);

    // Set the command to be invoked when a user presses 'ESC'
    //msg->CancelCommandIndex = 1;

    // Show the message dialog
    //msg->ShowAsync();
}

NS_CC_END;
