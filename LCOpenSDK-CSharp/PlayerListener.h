#pragma once

using namespace System;
using namespace System::Runtime::InteropServices;

namespace LCOpenSDK_CSharp
{
#ifndef _LCOPENSDK_PLAYERLISTENER_H_
#define _LCOPENSDK_PLAYERLISTENER_H_
	class LCOpenSDK_PlayerListener
	{
	public:
		virtual ~LCOpenSDK_PlayerListener() {};
		virtual void onPlayerResult(int index, const char* code, int resultSource) = 0;
		virtual void onResolutionChanged(int index, int width, int height) = 0;
		virtual void onPlayBegan(int index) = 0;
		virtual void onReceiveData(int index, int len) = 0;
		virtual void onStreamCallback(int index, const unsigned char* data, unsigned int dataLen) = 0;
		virtual void onPlayFinished(int index) = 0;
		virtual void onPlayerTime(int index, long time) = 0;
	};
#endif /* _LCOPENSDK_PLAYERLISTENER_H_ */

	public ref class PlayerListener abstract {
	public:
		PlayerListener();
		~PlayerListener();

		virtual void onPlayerResult(int index, String^ code, int resultSource) = 0;
		virtual void onResolutionChanged(int index, int width, int height) = 0;
		virtual void onPlayBegan(int index) = 0;
		virtual void onReceiveData(int index, int len) = 0;
		virtual void onStreamCallback(int index, String^ data, int dataLen) = 0;
		virtual void onPlayFinished(int index) = 0;
		virtual void onPlayerTime(int index, long time) = 0;

		LCOpenSDK_PlayerListener* GetUnManagedListener()
		{
			return _unmanagedListener;
		}

	private:
		LCOpenSDK_PlayerListener * _unmanagedListener;
	};

	//Implementation for LCOpenSDK_PlayerListener abstract class
	//This Class is used for delegating callback methods to a PlayerListener managed object
	class LCOpenSDK_PlayerListenerImp :public LCOpenSDK_PlayerListener
	{
	public:
		LCOpenSDK_PlayerListenerImp(PlayerListener^ l) {
			_listenerHandle = static_cast<IntPtr>(GCHandle::Alloc(l));
		}
		~LCOpenSDK_PlayerListenerImp() {
			static_cast<GCHandle>(_listenerHandle).Free();
		}
		
		virtual void onPlayerResult(int index, const char * code, int resultSource)
		{
			PlayerListener^ _listener = safe_cast<PlayerListener ^>(static_cast<GCHandle>(_listenerHandle).Target);
			_listener->onPlayerResult(index, gcnew String(code), resultSource);
		};
		virtual void onResolutionChanged(int index, int width, int height)
		{
			PlayerListener^ _listener = safe_cast<PlayerListener ^>(static_cast<GCHandle>(_listenerHandle).Target);
			_listener->onResolutionChanged(index, width, height);
		}
		virtual void onPlayBegan(int index) {
			PlayerListener^ _listener = safe_cast<PlayerListener ^>(static_cast<GCHandle>(_listenerHandle).Target);
			_listener->onPlayBegan(index);
		};
		virtual void onReceiveData(int index, int len) {
			PlayerListener^ _listener = safe_cast<PlayerListener ^>(static_cast<GCHandle>(_listenerHandle).Target);
			_listener->onReceiveData(index, len);
		};
		virtual void onStreamCallback(int index, const unsigned char * data, unsigned int dataLen) {
			PlayerListener^ _listener = safe_cast<PlayerListener ^>(static_cast<GCHandle>(_listenerHandle).Target);
			_listener->onStreamCallback(index, gcnew String(reinterpret_cast<const char*>(data)), dataLen);
		};
		virtual void onPlayFinished(int index) {
			PlayerListener^ _listener = safe_cast<PlayerListener ^>(static_cast<GCHandle>(_listenerHandle).Target);
			_listener->onPlayFinished(index);
		};
		virtual void onPlayerTime(int index, long time) {
			PlayerListener^ _listener = safe_cast<PlayerListener ^>(static_cast<GCHandle>(_listenerHandle).Target);
			_listener->onPlayerTime(index, time);
		};
	private:
		IntPtr _listenerHandle;
	};
}
