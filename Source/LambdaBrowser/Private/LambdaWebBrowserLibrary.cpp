// Copyright Lambda Works, Samuel Metters 2019. All rights reserved.


#include "LambdaWebBrowserLibrary.h"
#include "Misc/FileHelper.h"
#include "GenericPlatform/GenericPlatformHttp.h"

FString ULambdaWebBrowserLibrary::EncodeStringToURL(FString URL)
{
	return FGenericPlatformHttp::UrlEncode(URL);
}

FString ULambdaWebBrowserLibrary::DecodeURLToString(FString URL)
{
	return FGenericPlatformHttp::UrlDecode(URL);
}

bool ULambdaWebBrowserLibrary::isValidURL(FString URL)
{
	if (URL != "")
	{
		if (FGenericPlatformHttp::GetUrlDomain(URL) != "")
		{
			if (URL.Contains("http://") || URL.Contains("https://") || URL.Contains("www."))
			{
				return true;
			}
		}
	}
	return false;
}

bool ULambdaWebBrowserLibrary::SaveStringArrayToFile(FString PathToFile, TArray<FString> FileContent)
{
	IFileManager &FileManager = IFileManager::Get();

	uint32 Flags = 0;

	if (FFileHelper::SaveStringArrayToFile(FileContent, *PathToFile, FFileHelper::EEncodingOptions::AutoDetect, &FileManager, Flags))
	{
		// Success
		return true;
	}

	// File not created
	return false;
}

bool ULambdaWebBrowserLibrary::SaveStringToFile(FString PathToFile, FString FileContent)
{
	TArray<FString> tempStringArray;
	tempStringArray.Add(FileContent);

	return SaveStringArrayToFile(PathToFile, tempStringArray);
}
