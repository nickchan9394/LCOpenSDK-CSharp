#pragma once

using namespace System;
using namespace System::Runtime::InteropServices;

namespace LCOpenSDK_CSharp
{
	public struct OpenApiUnman {
	public:
		[DllImport("LCOpenSDKmd.dll",
			EntryPoint = "?GetInstance@LCOpenSDK_Api@@SAPAV1@XZ",
			CallingConvention = CallingConvention::ThisCall)]
		static OpenApiUnman* GetInstance(OpenApiUnman*);

		[DllImport("LCOpenSDKmd.dll",
			EntryPoint = "?initOpenApi@LCOpenSDK_Api@@QAEXPBDH0@Z",
			CallingConvention = CallingConvention::ThisCall)]
		static void initOpenApi(OpenApiUnman*, const char*, int, const char*);
	};


	public ref class OpenApi {
	public:
		OpenApi() {
			sdk = OpenApiUnman::GetInstance(sdk);
		}

		//Do not use this API, request restful apis instead
		void InitOpenApi(String^ host, int port, String^ caPath)
		{
			IntPtr hostNativeString = Marshal::StringToHGlobalAnsi(host);
			IntPtr caPathNativeString = Marshal::StringToHGlobalAnsi(caPath);

			try
			{
				OpenApiUnman::initOpenApi(sdk,
					static_cast<char*>(hostNativeString.ToPointer()),
					port,
					static_cast<char*>(caPathNativeString.ToPointer()));
			}
			finally{
				Marshal::FreeHGlobal(hostNativeString);
			Marshal::FreeHGlobal(caPathNativeString);
			}
		}

	private:
		OpenApiUnman * sdk;
	};
}
