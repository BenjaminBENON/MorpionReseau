#include "web_sThread.h"
//#include "httplib.h"

#include "GameInstance.cpp"

//retourne l'état actuel du jeu en format JSON.
extern std::string getGameStateAsJson();

web_sThread::web_sThread()
{
}

web_sThread::~web_sThread()
{
}

void web_sThread::OnEnter()
{
  /*  httplib::Server svr;

    svr.Get("/game-state", [&](const httplib::Request&, httplib::Response& res) {
        std::string gameState = getGameStateAsJson(); 
        res.set_content(gameState, "application/json");
        });

    
    svr.listen("0.0.0.0", 7985);*/
}
