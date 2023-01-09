using namespace std;

void setColor(int text, int background) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, (background * 16) + text);
}
void setColorDefault() {
    setColor(light_gray, black);
}

void coloredText(string text, int color) {
    setColor(color, black);
    cout << text;
    setColorDefault();
}