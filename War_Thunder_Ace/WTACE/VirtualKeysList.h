#pragma once

const char* KeyNames[] = 
{ 
"Left mouse button",
"Right mouse button",
"Middle mouse button",
"X1 mouse button",
"X2 mouse button",
"BACKSPACE key",
"TAB key",
"CLEAR key",
"ENTER key",
"SHIFT key",
"CTRL key",
"ALT key",
"PAUSE key",
"CAPS LOCK key",
"ESC key",
"SPACEBAR",
"PAGE UP key",
"PAGE DOWN key",
"END key",
"HOME key",
"LEFT ARROW key",
"UP ARROW key",
"RIGHT ARROW key",
"DOWN ARROW key",
"PRINT SCREEN key",
"INS key",
"DEL key",
"0 key",
"1 key",
"2 key",
"3 key",
"4 key",
"5 key",
"6 key",
"7 key",
"8 key",
"9 key",
"A key",
"B key",
"C key",
"D key",
"E key",
"F key",
"G key",
"H key",
"I key",
"J key",
"K key",
"L key",
"M key",
"N key",
"O key",
"P key",
"Q key",
"R key",
"S key",
"T key",
"U key",
"V key",
"W key",
"X key",
"Y key",
"Z key",
"Left Windows key",
"Right Windows key",
"F1 key",
"F2 key",
"F3 key",
"F4 key",
"F5 key",
"F6 key",
"F7 key",
"F8 key",
"F9 key",
"F10 key",
"F11 key",
"F12 key",
"NUM LOCK key",
"SCROLL LOCK key",
"Left SHIFT key",
"Right SHIFT key",
"Left CONTROL key",
"Right CONTROL key",
"Left ALT key",
"Right ALT key",
"+ key",
", key",
"- key",
". key",
};

std::map<std::string, int> KeyNameToVkeyCode = {
{"Left mouse button", VK_LBUTTON},
{"Right mouse button", VK_RBUTTON},
{"Middle mouse button", VK_MBUTTON},
{"X1 mouse button", VK_XBUTTON1},
{"X2 mouse button", VK_XBUTTON2},
{"BACKSPACE key", VK_BACK},
{"TAB key", VK_TAB},
{"CLEAR key", VK_CLEAR},
{"ENTER key", VK_RETURN},
{"SHIFT key", VK_SHIFT},
{"CTRL key", VK_CONTROL},
{"ALT key", VK_MENU},
{"PAUSE key", VK_PAUSE},
{"CAPS LOCK key", VK_CAPITAL},
{"ESC key", VK_ESCAPE},
{"SPACEBAR", VK_SPACE},
{"PAGE UP key", VK_PRIOR},
{"PAGE DOWN key", VK_NEXT},
{"END key", VK_END},
{"HOME key", VK_HOME},
{"LEFT ARROW key", VK_LEFT},
{"UP ARROW key", VK_UP},
{"RIGHT ARROW key", VK_RIGHT},
{"DOWN ARROW key", VK_DOWN},
{"SELECT key", VK_SELECT},
{"PRINT key", VK_PRINT},
{"EXECUTE key", VK_EXECUTE},
{"PRINT SCREEN key", VK_SNAPSHOT},
{"INS key", VK_INSERT},
{"DEL key", VK_DELETE},
{"0 key", 0x30},
{"1 key", 0x31},
{"2 key", 0x32},
{"3 key", 0x33},
{"4 key", 0x34},
{"5 key", 0x35},
{"6 key", 0x36},
{"7 key", 0x37},
{"8 key", 0x38},
{"9 key", 0x39},
{"A key", 0x41},
{"B key", 0x42},
{"C key", 0x43},
{"D key", 0x44},
{"E key", 0x45},
{"F key", 0x46},
{"G key", 0x47},
{"H key", 0x48},
{"I key", 0x49},
{"J key", 0x4A},
{"K key", 0x4B},
{"L key", 0x4C},
{"M key", 0x4D},
{"N key", 0x4E},
{"O key", 0x4F},
{"P key", 0x50},
{"Q key", 0x51},
{"R key", 0x52},
{"S key", 0x53},
{"T key", 0x54},
{"U key", 0x55},
{"V key", 0x56},
{"W key", 0x57},
{"X key", 0x58},
{"Y key", 0x59},
{"Z key", 0x5A},
{"Left Windows key", VK_LWIN},
{"Right Windows key", VK_RWIN},
{"F1 key", VK_F1},
{"F2 key", VK_F2},
{"F3 key", VK_F3},
{"F4 key", VK_F4},
{"F5 key", VK_F5},
{"F6 key", VK_F6},
{"F7 key", VK_F7},
{"F8 key", VK_F8},
{"F9 key", VK_F9},
{"F10 key", VK_F10},
{"F11 key", VK_F11},
{"F12 key", VK_F12},
{"NUM LOCK key", VK_NUMLOCK},
{"SCROLL LOCK key", VK_SCROLL},
{"Left SHIFT key", VK_LSHIFT},
{"Right SHIFT key", VK_RSHIFT},
{"Left CONTROL key", VK_LCONTROL},
{"Right CONTROL key", VK_RCONTROL},
{"Left ALT key", VK_LMENU},
{"Right ALT key", VK_RMENU},
{"+ key", 0xBB},
{", key", 0xBC},
{"- key", 0xBD},
{". key", 0xBE}
};

std::map<int, std::string > VkeyCodeToKeyName = {
{VK_LBUTTON, "Left mouse button"},
{VK_RBUTTON, "Right mouse button"},
{VK_MBUTTON, "Middle mouse button"},
{VK_XBUTTON1, "X1 mouse button"},
{VK_XBUTTON2, "X2 mouse button"},
{VK_BACK, "BACKSPACE key"},
{VK_TAB, "TAB key"},
{VK_CLEAR, "CLEAR key"},
{VK_RETURN, "ENTER key"},
{VK_SHIFT, "SHIFT key"},
{VK_CONTROL, "CTRL key"},
{VK_MENU, "ALT key"},
{VK_PAUSE, "PAUSE key"},
{VK_CAPITAL, "CAPS LOCK key"},
{VK_ESCAPE, "ESC key"},
{VK_SPACE, "SPACEBAR"},
{VK_PRIOR, "PAGE UP key"},
{VK_NEXT, "PAGE DOWN key"},
{VK_END, "END key"},
{VK_HOME, "HOME key"},
{VK_LEFT, "LEFT ARROW key"},
{VK_UP, "UP ARROW key"},
{VK_RIGHT, "RIGHT ARROW key"},
{VK_DOWN, "DOWN ARROW key"},
{VK_SELECT, "SELECT key"},
{VK_PRINT, "PRINT key"},
{VK_EXECUTE, "EXECUTE key"},
{VK_SNAPSHOT, "PRINT SCREEN key"},
{VK_INSERT, "INS key"},
{VK_DELETE, "DEL key"},
{0x30, "0 key"},
{0x31, "1 key"},
{0x32, "2 key"},
{0x33, "3 key"},
{0x34, "4 key"},
{0x35, "5 key"},
{0x36, "6 key"},
{0x37, "7 key"},
{0x38, "8 key"},
{0x39, "9 key"},
{0x41, "A key"},
{0x42, "B key"},
{0x43, "C key"},
{0x44, "D key"},
{0x45, "E key"},
{0x46, "F key"},
{0x47, "G key"},
{0x48, "H key"},
{0x49, "I key"},
{0x4A, "J key"},
{0x4B, "K key"},
{0x4C, "L key"},
{0x4D, "M key"},
{0x4E, "N key"},
{0x4F, "O key"},
{0x50, "P key"},
{0x51, "Q key"},
{0x52, "R key"},
{0x53, "S key"},
{0x54, "T key"},
{0x55, "U key"},
{0x56, "V key"},
{0x57, "W key"},
{0x58, "X key"},
{0x59, "Y key"},
{0x5A, "Z key"},
{VK_LWIN, "Left Windows key"},
{VK_RWIN, "Right Windows key"},
{VK_F1, "F1 key"},
{VK_F2, "F2 key"},
{VK_F3, "F3 key"},
{VK_F4, "F4 key"},
{VK_F5, "F5 key"},
{VK_F6, "F6 key"},
{VK_F7, "F7 key"},
{VK_F8, "F8 key"},
{VK_F9, "F9 key"},
{VK_F10, "F10 key"},
{VK_F11, "F11 key"},
{VK_F12, "F12 key"},
{VK_NUMLOCK, "NUM LOCK key"},
{VK_SCROLL, "SCROLL LOCK key"},
{VK_LSHIFT, "Left SHIFT key"},
{VK_RSHIFT, "Right SHIFT key"},
{VK_LCONTROL, "Left CONTROL key"},
{VK_RCONTROL, "Right CONTROL key"},
{VK_LMENU, "Left ALT key"},
{VK_RMENU, "Right ALT key"},
{0xBB, "+ key"},
{0xBC, ", key"},
{0xBD, "- key"},
{0xBE, ". key"},
};

int GetVkeyCodeByName(std::string name)
{
    try {
        return KeyNameToVkeyCode.at(name);
    }
    catch (const std::out_of_range) {
        return 0;
    }
}

std::string GetNameByVkeyCode(int VkeyCode)
{
    try {
        return VkeyCodeToKeyName.at(VkeyCode);
    }
    catch (const std::out_of_range) {
        return 0;
    }
}

template <typename T, size_t N>
int getposition(const T(&array)[N], const T c)
{
    const T* match = std::find(array, array + N, c);
    return (array + N == match) ? -1 : std::distance(array, match);
}