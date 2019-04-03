#include "PlayerListener.h"

LCOpenSDK_CSharp::PlayerListener::PlayerListener()
{
	_unmanagedListener = new LCOpenSDK_PlayerListenerImp(this);
}

LCOpenSDK_CSharp::PlayerListener::~PlayerListener()
{
	delete _unmanagedListener;
}
