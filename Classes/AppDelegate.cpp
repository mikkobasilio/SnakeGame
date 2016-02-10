#include "AppDelegate.h"
#include "FirstScene.h"
#include "HelloWorldScene.h"
#include "NiceScene.h"
USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate()
{
}
std::wstring AppDelegate::s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}
bool AppDelegate::applicationDidFinishLaunching() {
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	glview->setFrameSize(736, 576);
	if (!glview) {
		glview = GLViewImpl::create("Human Centipede");
		glview->setFrameSize(736, 576);
		director->setOpenGLView(glview);
	}
	std::ostringstream buffer;
	buffer << "HAHAHAHHAHA";
	std::wstring waw = s2ws(buffer.str());
	LPCWSTR result = waw.c_str();
	OutputDebugString(result);
	auto scene = HelloWorld::createScene();
	director->runWithScene(scene);
	return true;
}

void AppDelegate::applicationDidEnterBackground() {
}

void AppDelegate::applicationWillEnterForeground() {
}