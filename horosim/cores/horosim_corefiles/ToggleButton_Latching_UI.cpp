#include "ToggleButton_Latching_UI.h"
#include "Defines.h"
#include <string>


extern "C" {
#include "coppeliasim/remoteapi/extApi.h"
}
extern int clientID;

//Vector with the handles of joints and sensors
extern std::vector<HardwareDevice*> handles;

ToggleButton_Latching_UI::ToggleButton_Latching_UI(int pin_i, std::string str, enum ButtonType b_type_i):
HardwareDevice{str} {
	pin=pin_i;
	b_type=b_type_i;
	if(b_type==PULL_DOWN)
		state=false;
	else
		state=true;
	type=ToggleButton_Latching_UI_t;
	handles.push_back(this);
}

void ToggleButton_Latching_UI::updateGUI()
{
    ImVec2 p = ImGui::GetCursorScreenPos();
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    float height = ImGui::GetFrameHeight();
    float width = height * 1.55f;
    float radius = height * 0.50f;

    if (ImGui::InvisibleButton(handle_name.c_str(), ImVec2(width, height)))
        state = !state;
    ImU32 col_bg;
    if (ImGui::IsItemHovered())
        col_bg = state ? IM_COL32(145+20, 211, 68+20, 255) : IM_COL32(218-20, 218-20, 218-20, 255);
    else
        col_bg = state ? IM_COL32(145, 211, 68, 255) : IM_COL32(218, 218, 218, 255);

    draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), col_bg, height * 0.5f);
    draw_list->AddCircleFilled(ImVec2(state ? (p.x + width - radius) : (p.x + radius), p.y + radius), radius - 1.5f, IM_COL32(255, 255, 255, 255));
    ImGui::SameLine();
    ImGui::Text(handle_name.c_str());  
}

bool* ToggleButton_Latching_UI::getState() {
	return &state;
}

int ToggleButton_Latching_UI::digitalRead(int pin_i) {
	if(pin_i!=pin)
		return -1;

	if(!set2input)
		return 0;

	if(state)
		return 1;
	else
		return 0;
}

int ToggleButton_Latching_UI::analogRead(int pin_i) {
	if(pin_i!=pin)
		return -1;

	if(!set2input)
		return 0;

	//It is not an analog sensor!
	if(state)
		return 1023;
	else
		return 0;
}

void ToggleButton_Latching_UI::pinMode(char pin_i, char mode) {
	if(pin_i!=pin)
		return;
	if(mode==OUTPUT)
		set2input=false;
	else
		set2input=true;
}
