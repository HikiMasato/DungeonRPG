//-------------------------------------------------------
//既存のもの
#include <time.h>
#include <string>
#include <numbers>
#include <functional>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
//-------------------------------------------------------
//個人的に追加した機能
#include <string_view>
#include <random>         
#include <iostream>  
#include <chrono>
//-------------------------------------------------------
//Object
#include "Factory.h"
#include "Object.h"
#include "MyCamera.h"
#include "Player.h"
//-------------------------------------------------------
//Scene
#include "SceneBase.h"
#include "SceneTitle.h"
#include "ScenePlay.h"
#include "SceneEnd.h"
//-------------------------------------------------------
//Manager
#include "GameManager.h"
#include "MapManager.h"
#include "SceneManager.h"


std::vector<int> SceneBase::minutes ;
std::vector<int> SceneBase::seconds ;
std::vector<int> SceneBase::dungeon_level ;
int SceneBase::max_diamond = 0;

SceneBase::SceneBase() {

	minutes.resize(5);
	seconds.resize(5);
	dungeon_level.resize(5);

}


