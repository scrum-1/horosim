#include "Led_UI.h"
#include "Defines.h"
#include <string>


extern "C" {
#include "coppeliasim/remoteapi/extApi.h"
}
extern int clientID;

//Vector with the handles of joints and sensors
extern std::vector<HardwareDevice*> handles;

Led_UI::Led_UI(int pin_i, std::string str):HardwareDevice{str} {
	pin=pin_i;
	type=Led_UI_t;
	handles.push_back(this);
}

Led_UI::Led_UI(int pin_i, std::string str, enum LedColor color_i):
HardwareDevice{str} {
	pin=pin_i;
	color=color_i;
	type=Led_UI_t;
	handles.push_back(this);
}

void Led_UI::updateGUI(){
    ImVec2 p = ImGui::GetCursorScreenPos();
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    float height = ImGui::GetFrameHeight();
    float width = height * 1.55f;
    float radius = height * 0.50f;

    ImU32 col_bg;
    if(color==LED_RED)
    	col_bg =IM_COL32(120+state, 20, 20, 255);
    if(color==LED_GREEN)
    	col_bg =IM_COL32(20, 120+state, 20, 255);

    ImGui::InvisibleButton(handle_name.c_str(), ImVec2(width, height));
    //draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), col_bg, height * 0.5f);
    draw_list->AddCircleFilled(ImVec2(p.x + radius, p.y + radius), radius , IM_COL32(255, 255, 255, 255));
    draw_list->AddCircleFilled(ImVec2(p.x + radius, p.y + radius), radius - 1.5f, col_bg);
    ImGui::SameLine();
    ImGui::Text(handle_name.c_str());  
}

void Led_UI::digitalWrite(int pin_i, int val) {
	if(pin_i!=pin)
		return;

	if(!set2output)
		return;

	if(val>0)
		state=100;
	else
		state=0;
}

void Led_UI::analogWrite(int pin_i, int val) {
	if(pin_i!=pin)
		return;
	if(!set2output)
		return;
	if(pin_i==3||pin_i==5||pin_i==6||pin_i==9||pin_i==10||pin_i==11) {
		state=(val%256)/255.0*100;
	}
	if(state<0)
		state=0;
}

void Led_UI::pinMode(char pin_i, char mode) {
	if(pin_i!=pin)
		return;
	if(mode==OUTPUT)
		set2output=true;
	else
		set2output=false;
}
