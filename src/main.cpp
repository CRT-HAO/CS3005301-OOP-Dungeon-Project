#include "core/KeyInput.hpp"
#include "core/ObjectsManager.hpp"
#include "core/Room.hpp"
#include "core/View.hpp"
#include "gui/WebViewUtil.hpp"

#include "lib/webview/webview.h"

#include <iostream>

using namespace std;
using namespace Dungeon;

webview::webview w(true, nullptr);
ObjectsManager manager;
View view;
KeyInput keyInput;

std::string logic(string args)
{
    manager.logic(&keyInput);
    return "\"Success\"";
}

std::string render(string args)
{
    manager.render(&view);
    return "\"Success\"";
}

std::string getView(string args)
{
    return view.data.dump();
}

std::string setKeyInput(string args)
{
    Json argsData = Json::parse(args);
    keyInput.setKey(argsData[0].get<char>(), argsData[1].get<bool>());

    return "\"Success\"";
}

int main(int argc, char *argv[])
{
    Room *room = new Room(Position(0, 0));
    manager.addObject(room);

    w.set_title("Basic Example");
    w.set_size(480, 320, WEBVIEW_HINT_NONE);
    w.navigate(WebViewUtil::getLocalPath("app.html"));
    w.bind("logic", logic);
    w.bind("render", render);
    w.bind("getView", getView);
    w.bind("setKeyInput", setKeyInput);
    w.run();

    manager.render(&view);

    return 0;
}