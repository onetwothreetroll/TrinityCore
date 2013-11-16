
#include "ScriptMgr.h"
#include <Player.h>
#include <Chat.h>
#include <Config.h>
#include <string>

class first_login_announce : public PlayerScript {
  
public:  
  first_login_announce() : PlayerScript("first_login_announce") {
    m_GlobalFormat = sConfigMgr->GetStringDefault("FirstLogin.GloabalAnnounceFormatString", "Hello, %s!");
    m_PlayerFormat = sConfigMgr->GetStringDefault("FirstLogin.PlayerAnnounceFormatString", "Hello, %s!");
  }
  
  virtual void OnLogin(Player * player) OVERRIDE {
    if(!player->HasAtLoginFlag(AT_LOGIN_FIRST)) return;
    
    ChatHandler chatHander(player->GetSession());
    
    char buf[2048];
    
    snprintf(buf, sizeof(buf), m_GlobalFormat.c_str(), player->GetName().c_str());
    chatHander.SendGlobalSysMessage(buf);
    
    snprintf(buf, sizeof(buf), m_PlayerFormat.c_str(), player->GetName().c_str());
    chatHander.SendSysMessage(buf);
    
    player->RemoveAtLoginFlag(AT_LOGIN_FIRST);
  }
  
private:
  std::string m_GlobalFormat, m_PlayerFormat;
};

void AddSC_first_login_announce() {
  if(sConfigMgr->GetBoolDefault("FirstLogin.Announce", false)) {
    if(!sConfigMgr->GetBoolDefault("FirstLogin.FlagEnable", false))//TODO 
      return;
    new first_login_announce();
  }
}

