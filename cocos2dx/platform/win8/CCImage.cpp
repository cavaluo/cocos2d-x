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

#include "platform/CCImage.h"
#include "support/ccUTF8.h"
#include "DirectXRender.h"
#define __CC_PLATFORM_IMAGE_CPP__
#include "platform/CCImageCommon_cpp.h"

NS_CC_BEGIN;

#if WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP
typedef FTTextPainter TextPainter;
#else
typedef DXTextPainter TextPainter;
#endif

bool CCImage::initWithString(
	const char *    pText, 
	int             nWidth/* = 0*/, 
	int             nHeight/* = 0*/,
	ETextAlign      eAlignMask/* = kAlignCenter*/,
	const char *    pFontName/* = nil*/,
	int             nSize/* = 0*/)
{
	bool bRet = false;
	unsigned char * pImageData = 0;

	do{
		CC_BREAK_IF(! pText);  

		TextPainter^ painter = DirectXRender::SharedDXRender()->m_textPainter;
        wchar_t* utf16str = (wchar_t*)cc_utf8_to_utf16(pFontName);
		std::wstring wStrFontName = utf16str;
        CC_SAFE_DELETE_ARRAY(utf16str);

		bool isSuccess = painter->SetFont(ref new Platform::String(wStrFontName.c_str()), nSize);
		
		if (!isSuccess)
		{
			CCLog("Can't find font(%s), using system default", pFontName);
		}

		Windows::Foundation::Size size((float)nWidth, (float)nHeight);

		TextAlignment alignment = TextAlignment::TextAlignmentCenter;
		DWORD dwHoriFlag = eAlignMask & 0x0f;
		//set text alignment
		switch (dwHoriFlag)
		{
		case 1: // left
			alignment = TextAlignment::TextAlignmentLeft;
			break;
		case 2: // right
			alignment = TextAlignment::TextAlignmentRight;
			break;
		case 3: // center
			alignment = TextAlignment::TextAlignmentCenter;
			break;
		}

		Platform::Array<byte>^ pixelData;
        utf16str = (wchar_t*)cc_utf8_to_utf16(pText);
        std::wstring wStrText = utf16str;
        CC_SAFE_DELETE_ARRAY(utf16str);

		pixelData = painter->DrawTextToImage(ref new Platform::String(wStrText.c_str()), &size, alignment);

		if(pixelData == nullptr)
		{
			break;
		}

		pImageData = new unsigned char[(UINT)size.Width * (UINT)size.Height * 4];
		memcpy(pImageData, pixelData->Data, pixelData->Length);

		CC_BREAK_IF(! pImageData);

		m_nWidth    = (short)size.Width;
		m_nHeight   = (short)size.Height;
		m_bHasAlpha = true;
		m_bPreMulti = false;
		m_pData     = pImageData;
		pImageData  = 0;
		m_nBitsPerComponent = 8;

		bRet = true;

        painter = nullptr;

	}while(0);

	return bRet;
}

NS_CC_END;
