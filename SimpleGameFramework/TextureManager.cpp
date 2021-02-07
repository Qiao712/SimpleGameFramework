#include "TextureManager.h"
#include"Texture.h"
#include"Window.h"
#include<iostream>
#include<filesystem>
using std::cout;
using std::endl;
using std::make_pair;
namespace fs = std::filesystem;

//nullptr
TextureManager* TextureManager::_instance = nullptr;

void TextureManager::init(const Window& window)
{
	_instance = new TextureManager(window._renderer);
}

Texture TextureManager::create(string name)
{
	if (_instance->_textures.find(name) == _instance->_textures.end()) {
		cout << "TextureManager::create: no texture named " << name << endl;
		return Texture(nullptr);
	}
	return _instance->_textures[name];
}

SDL_Renderer* TextureManager::getSDL_Renderer()
{
	if (_instance != nullptr)
		return _instance->_renderer;
	else
		return nullptr;
}

void TextureManager::drawLine(int x1, int y1, int x2, int y2, char r, char g, char b, char a)
{
	SDL_SetRenderDrawColor(_instance->_renderer, r, g, b, a);
	SDL_RenderDrawLine(_instance->_renderer, x1, y1, x2, y2);
	SDL_SetRenderDrawColor(_instance->_renderer, 0, 0, 0, 0);
}

TextureManager::TextureManager(SDL_Renderer* renderer) : _renderer(renderer)
{
	loadTextures();
}

TextureManager::~TextureManager()
{
	//�ͷ�������Դ
	for (auto i : _textures) {
		SDL_DestroyTexture(i.second._texture);
	}
}


//����res�µ�ȫ��������Դ�����������ֵ������ӳ��
void TextureManager::loadTextures()
{
	fs::path path_res = ".\\res";
	cout <<"Load resource at: "<< path_res.string() << endl;
	for (auto& f : fs::directory_iterator(path_res)) {
		if (!f.is_directory()) {
			string stem = f.path().stem().string();				//�ļ�����������չ��
			string filename = f.path().filename().string();		//�ļ���������չ��
			_textures.insert({ stem, loadTexture(filename) });
		}
	}
}

//����res\pathͼƬ�ļ�
Texture TextureManager::loadTexture(string path)
{
	//static string base_path = SDL_GetBasePath();
	path = string("res\\") + path;	//����res�ļ����µ���Դ
	cout << "Load texture: " << path << endl;

	//SDL֧�ֵ�BMP
	/*SDL_Surface* image = SDL_LoadBMP(path.c_str());
	if (image == nullptr) {
		cout << "Can't load " << path << endl;
	}
	
	SDL_Texture* sdl_texture = SDL_CreateTextureFromSurface(_renderer, image);
	if (sdl_texture == nullptr) {
		cout << "Can't create texture from surface." << endl;
	}*/

	//SDL_image֧�ֵĶ���ͼƬ��ʽ
	SDL_Texture* sdl_texture = IMG_LoadTexture(_renderer, path.c_str());
	if (sdl_texture == nullptr) {
		cout << "Can't load " << path <<" Error: " << SDL_GetError() <<endl;
	}

	return Texture(sdl_texture, _renderer);
}
