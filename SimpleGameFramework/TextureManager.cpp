#include"TextureManager.h"
#include"Texture.h"
#include"Window.h"
#include"Animation.h"
#include"Camera.h"
#include<cmath>
#include<iostream>
#include<fstream>
#include<filesystem>
using std::cout;
using std::endl;
using std::make_pair;
using std::ifstream;
namespace fs = std::filesystem;

//nullptr
TextureManager* TextureManager::_instance = nullptr;

void TextureManager::init()
{
	_instance = new TextureManager(Window::instance()->_renderer);
}

Texture* TextureManager::create(string name)
{
	//优先返回动画
	if (_instance->animations.find(name) != _instance->animations.end()) {
		cout << "return animation " << name << '\n';
		return new Animation(_instance->animations[name]);
	}

	//返回纹理
	if (_instance->_textures.find(name) != _instance->_textures.end()) {
		return new Texture(_instance->_textures[name]);
	}

	return new Texture;
}

SDL_Renderer* TextureManager::getSDL_Renderer()
{
	if (_instance != nullptr)
		return _instance->_renderer;
	else
		return nullptr;
}

void TextureManager::drawLine(Point p1, Point p2,Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	static Camera& camera = *Camera::instance();
	p1 = camera.transform2win(p1);
	p2 = camera.transform2win(p2);

	SDL_SetRenderDrawColor(_instance->_renderer, r, g, b, a);
	SDL_RenderDrawLine(_instance->_renderer, round(p1.x), round(p1.y), round(p2.x), round(p2.y));
	SDL_SetRenderDrawColor(_instance->_renderer, 0, 0, 0, 0);
}

TextureManager::TextureManager(SDL_Renderer* renderer) : _renderer(renderer)
{
	_loadTextures();
	_loadAnimations();
}

TextureManager::~TextureManager()
{
	//释放纹理资源
	for (auto i : _textures) {
		SDL_DestroyTexture(i.second._texture);
	}
}


//加载res下的全部纹理资源，并建立名字到纹理的映射
void TextureManager::_loadTextures()
{
	fs::path path_res = ".\\res";
	cout <<"Load resource at: "<< path_res.string() << endl;
	for (auto& f : fs::directory_iterator(path_res)) {
		if (!f.is_directory()) {
			string stem = f.path().stem().string();				//文件名，不带扩展名
			string filename = f.path().filename().string();		//文件名，带扩展名
			string extension = f.path().extension().string();		//扩展名

			//检测扩展名
			if (!_checkExtension(extension)) continue;

			_textures.insert({ stem, _loadTexture(filename) });
		}
	}
}

void TextureManager::_loadAnimations()
{
	ifstream animation_file;
	animation_file.open("res\\Animations.txt", std::ios::in);
	char t;
	string name;
	int width_frame;
	int interval;

	if (!animation_file) {
		std::cout << "Can't open Animations.txt\n";
	}

	while (animation_file>>name) {
		animation_file >> width_frame >> interval;
		std::cout << "Load animation :" << name << '\n';
		if (_textures.find(name) == _textures.end()) {
			std::cout << "Can't find texture: " << name << '\n';
			continue;
		}

		Animation animation(width_frame, interval, _textures[name]._texture, _renderer);
		animations.insert({ name, animation });
	}
}

//加载res\path图片文件
Texture TextureManager::_loadTexture(string path)
{
	//static string base_path = SDL_GetBasePath();
	path = string("res\\") + path;	//加载res文件夹下的资源
	cout << "Load texture: " << path << endl;

	//SDL_image支持的多种图片格式
	SDL_Texture* sdl_texture = IMG_LoadTexture(_renderer, path.c_str());
	if (sdl_texture == nullptr) {
		cout << "Can't load " << path <<" Error: " << SDL_GetError() <<endl;
	}

	return Texture(sdl_texture, _renderer);
}

bool TextureManager::_checkExtension(string extension)
{
	return extension == string(".bmp") ||
		   extension == string(".png");
}
