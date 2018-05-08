#pragma once
#include "PlayerListener.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace LCOpenSDK_CSharp
{
	public struct VideoPlayUnman {
	public:
		[DllImport("LCOpenSDKmd.dll",
			EntryPoint = "??0LCOpenSDK_VideoPlay@@QAE@XZ",
			CallingConvention = CallingConvention::ThisCall)]
		static void ctor(VideoPlayUnman*);

		[DllImport("LCOpenSDKmd.dll",
			EntryPoint = "??1LCOpenSDK_VideoPlay@@QAE@XZ",
			CallingConvention = CallingConvention::ThisCall)]
		static void dtor(VideoPlayUnman*);

		[DllImport("LCOpenSDKmd.dll",
			EntryPoint = "?initVideoPlay@LCOpenSDK_VideoPlay@@QAEHHPAX@Z",
			CallingConvention = CallingConvention::ThisCall)]
		static int initVideoPlay(VideoPlayUnman*, int, void*);

		[DllImport("LCOpenSDKmd.dll",
			EntryPoint = "?uninitVideoPlay@LCOpenSDK_VideoPlay@@QAEXXZ",
			CallingConvention = CallingConvention::ThisCall)]
		static void uninitVideoPlay(VideoPlayUnman*);

		[DllImport("LCOpenSDKmd.dll",
			EntryPoint = "?setPlayerListener@LCOpenSDK_VideoPlay@@QAEXPAVLCOpenSDK_PlayerListener@@@Z",
			CallingConvention = CallingConvention::ThisCall)]
		static void setPlayerListener(VideoPlayUnman*, LCOpenSDK_PlayerListener*);

		[DllImport("LCOpenSDKmd.dll",
			EntryPoint = "?playRtspReal@LCOpenSDK_VideoPlay@@QAEHPBD00HH@Z",
			CallingConvention = CallingConvention::ThisCall)]
		static int playRtspReal(VideoPlayUnman*, const char*, const char*, const char*, int, int);
	};

	public ref class VideoPlay {
	public:
		VideoPlay() {
			videoPlay = new VideoPlayUnman();
			VideoPlayUnman::ctor(videoPlay);
		}

		~VideoPlay() {
			VideoPlayUnman::dtor(videoPlay);
		}

		int InitVideoPlay(int index, IntPtr hwndHandle) {
			return VideoPlayUnman::initVideoPlay(videoPlay, index, hwndHandle.ToPointer());
		}

		void UninitVideoPlay() {
			VideoPlayUnman::uninitVideoPlay(videoPlay);
		}

		void SetPlayerListener(PlayerListener^ listener)
		{
			VideoPlayUnman::setPlayerListener(videoPlay, listener->GetUnManagedListener());
		}

		int PlayRtspReal(String^ token, String^ deviceID, String^ decryptKey, int channelID, int definitionMode) {
			IntPtr tokenNativeString = Marshal::StringToHGlobalAnsi(token);
			IntPtr deviceIDNativeString = Marshal::StringToHGlobalAnsi(deviceID);
			IntPtr decryptKeyNativeString = Marshal::StringToHGlobalAnsi(decryptKey);

			return VideoPlayUnman::playRtspReal(
				videoPlay,
				static_cast<char*>(tokenNativeString.ToPointer()),
				static_cast<char*>(deviceIDNativeString.ToPointer()),
				static_cast<char*>(decryptKeyNativeString.ToPointer()),
				channelID, definitionMode);
		}

	private:
		VideoPlayUnman * videoPlay;
	};
}