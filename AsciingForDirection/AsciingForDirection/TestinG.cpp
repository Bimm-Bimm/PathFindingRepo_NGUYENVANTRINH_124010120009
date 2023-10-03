#include <iostream>
#include <Windows.h>
#include <math.h>
#include <corecrt_wstring.h>
#include <chrono>

//screen seting
int _screen_width = 120;
int _screen_height = 40;
float _FOV = 3.14159 / 2.0;
float _view_dis = 16.0f;

//player numbers
float _player_x = 8.0f;
float _player_y = 8.0f;
float _player_alpha = 0.0f;

//map numbers
int _map_d1_height = 16;
int _map_d1_width = 16;

int main (){
	wchar_t* screen = new wchar_t[_screen_height * _screen_width];
	HANDLE h_con = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(h_con);
	DWORD dwBytesWritten = 0;

	wstring _map_d1;

	_map_d1 += L"################";
	_map_d1 += L"#..............#";
	_map_d1 += L"#..............#";
	_map_d1 += L"#..............#";
	_map_d1 += L"#..............#";
	_map_d1 += L"#..............#";
	_map_d1 += L"#..............#";
	_map_d1 += L"######.........#";
	_map_d1 += L"#..............#";
	_map_d1 += L"#..............#";
	_map_d1 += L"#..............#";
	_map_d1 += L"#..............#";
	_map_d1 += L"#..............#";
	_map_d1 += L"#..............#";
	_map_d1 += L"#..............#";
	_map_d1 += L"################";

	auto _tp1 = chrono::system_clock::now();
	auto _tp2 = chrono::system_clock::now();

	while (1) {

		_tp2 = chrono::system_clock::now();
		chrono::duration<float> _elapsedTime = _tp2 - _tp1;
		_tp1 = _tp2;
		float _fElapsedTime = _elapsedTime.count();

		if (GetAsyncKeyState((unsigned short)'A') & 0x8000) {
			_player_alpha -= 0.75f * _fElapsedTime;
		}
		if (GetAsyncKeyState((unsigned short)'D') & 0x8000) {
			_player_alpha += 0.75f * _fElapsedTime;
		}
		if (GetAsyncKeyState((unsigned short)'W') & 0x8000) {
			_player_x += sinf(_player_alpha) * 2.f * _fElapsedTime;
			_player_y += cosf(_player_alpha) * 2.f * _fElapsedTime;
		}
		if (GetAsyncKeyState((unsigned short)'S') & 0x8000) {
			_player_x -= sinf(_player_alpha) * 2.f * _fElapsedTime;
			_player_y -= cosf(_player_alpha) * 2.f * _fElapsedTime;
		}
		

		for (int x = 0; x < _screen_width; x++) {
			float _ray_alpha = (_player_alpha - _FOV / 2.0f) + ((float)x / (float)_screen_width) * _FOV;
			float _distance_towall = 0;

			float _eye_x = sinf(_ray_alpha);
			float _eye_y = cosf(_ray_alpha);

			boolean _bwall = false;
			while (!_bwall && _distance_towall < _view_dis) {
				_distance_towall += 0.1f;

				int _test_x = int(_player_x + _eye_x * _distance_towall);
				int _test_y = int(_player_y + _eye_y * _distance_towall);
				

				if (_test_x < 0 || _test_x >= _map_d1_width || _test_y < 0 || _test_y >= _map_d1_height) {
					_bwall = true;
					_distance_towall = _view_dis;
				}
				else {
					if (_map_d1[_test_y * _map_d1_width + _test_x] == '#') {
						_bwall = true;
					}
				}
			}

			int _ceiling = float(_screen_height / 2.0) - _screen_height / float(_distance_towall);
			int _floor = _screen_height - _ceiling; 

			short _shade = ' ';
			short _shade_floor = ' ';
			if (_distance_towall < _view_dis / 4.f) _shade = 0x2588; 
			else if (_distance_towall < _view_dis / 3.f) _shade = 0x2593; 
			else if (_distance_towall < _view_dis / 2.f) _shade = 0x2592; 
			else if (_distance_towall < _view_dis) _shade = 0x2591; 
			else _shade = ' '; 

			for (int y = 0; y < _screen_height; y++) {
				if (y <= _ceiling) {
					screen[y * _screen_width + x] = ' ';
				}
				else if (y > _ceiling && y <= _floor) {
					screen[y * _screen_width + x] = _shade;
				}
				else {
					float b = 1.0f - (((float)y - _screen_height / 2.0f) / ((float)_screen_height / 2.0f));
					if (b < 0.15)		_shade_floor = '#';
					else if (b < 0.45)	_shade_floor = 'x';
					else if (b < 0.7)	_shade_floor = '.';
					else if (b < 0.9)	_shade_floor = '-';
					else				_shade_floor = ' ';
					screen[y * _screen_width + x] = _shade_floor;
				}
			}
		}

		screen[_screen_width * _screen_height - 1] = '\0';
		WriteConsoleOutputCharacter(h_con, screen, _screen_width * _screen_height, { 0,0 }, &dwBytesWritten);

	}

	return 0;
}
