Bước 0. Tải thư viện graphics.h về máy tính cá nhân 
Link tải thư viện : https://github.com/thinhdoanvu/ComputerGraphics/tree/master/Coding/library

Bước 1. Cài đặt thư viện theo trình tự sau:

Step 1.
Copy:

6-ConsoleAppGraphics.template
ConsoleApp_cpp_graph.txt
Paste:
C:\Program Files\Dev-Cpp\Templates
Step 2.
Copy:
graphics.h
winbgim.h
Paste:
C:\Program Files\Dev-Cpp\MinGW64\x86_64-w64-mingw32\include
Step 3.
Copy:
libbgi.a
Paste:
C:\Program Files\Dev-Cpp\MinGW64\x86_64-w64-mingw32\lib

Thiết lập trên DevC++
Open DevC - New Project - Console Graphics Application
C++ File
Project name: Hello
Save in some where
Tools - Compiler Option:
 TDM-GCC 4.9.2 32bit Release

Viết chương trình vẽ đường thẳng trên màn hình đồ họa
Example code:
#include <graphics.h>

int main()
{
	initwindow(800,800);
	line(100,100,400,400);
	getch();
}
