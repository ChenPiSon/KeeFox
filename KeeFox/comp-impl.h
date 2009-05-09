/*
  KeeFox - Allows Firefox to communicate with KeePass (via the KeeICE KeePass-plugin)
  Copyright 2008 Chris Tomlinson <keefox@christomlinson.name>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

// This is the definition of the XPCOM methods described in comp.idl

#ifndef __KEEFOX_IMPL_H__
#define __KEEFOX_IMPL_H__

#if _MSC_VER
#pragma warning( push, 0 )
#pragma warning( disable : 4512 )
#pragma warning( disable : 4100 )
#pragma warning( disable : 4702 )
#endif

#include "comp.h"
#include "nsStringAPI.h"
#include <string>
#include <vector>

#include <IceE/IceE.h>
//#include <IceUtil/IceUtil.h>
#include "generated/KeeICE.h"
//#include "nsILoginInfo.h"
#include "nsCOMPtr.h"

#if _MSC_VER
#pragma warning( pop ) 
#endif

using std::string;
using std::vector;
using namespace KeeICE::KFlib;

#define KEEFOX_CONTRACTID "@christomlinson.name/keefox;1"
#define KEEFOX_CLASSNAME "KeeFox"
#define KEEFOX_CID { 0x245626, 0x5cc1, 0x11db, { 0x96, 0x73, 0x0, 0xe0, 0x81, 0x61, 0x16, 0x5f } }

class KeeFoxCallBackHelper {
public:

	static KeeFoxObserver *_observer;
	static bool javascriptCallBacksReady;
};

class KeeICEProxy {
public:
	Ice::CommunicatorPtr ic;
	KPPrx KP;
	//KPDatabasePrx DB;
    virtual int run(int, char*[]);
	int establishICEConnection();
	int main(int argc, char* argv[]);

};

class CKeeFox : public IKeeFox
{
public:
	NS_DECL_ISUPPORTS
	NS_DECL_IKEEFOX
	//int Add2(int a, int b);

	CKeeFox();
	//NS_DECL_NSILOGINMANAGERSTORAGE

private:
	~CKeeFox();
	void WriteLocationToCache(string url); // TODO: add realm, etc?
	bool IsLocationInCache(string url);
	int CountLocationsInCache(string url);
	void DeleteLocationFromCache(string url);
	KeeICE::KFlib::KPEntry ConvertLoginInfoToKPEntry (kfILoginInfo *aLogin);
	nsCOMPtr<kfILoginInfo> ConvertKPEntryToLoginInfo (KeeICE::KFlib::KPEntry aLogin);
	KeeICE::KFlib::KPGroup ConvertGroupInfoToKPGroup (kfIGroupInfo *aGroup);
	nsCOMPtr<kfIGroupInfo> ConvertKPGroupToGroupInfo (KeeICE::KFlib::KPGroup group);

protected:
	/* additional members */
	nsString mName;
	KeeICEProxy KeeICE;
};


#endif