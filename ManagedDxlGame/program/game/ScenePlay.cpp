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
#include "DungeonScene.h"
#include "SceneEnd.h"
//-------------------------------------------------------
//Manager
#include "GameManager.h"
#include "ObjectManager.h"
#include "MapManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
//-------------------------------------------------------
//Collistion
#include "Collision.h" 
//-------------------------------------------------------
//Others
#include "Debug.h"


//------------------------------------------------------------------------------------------------------------
//コンストラクタ
ScenePlay::ScenePlay() {

	
	seq_dungeon = std::make_shared<DungeonScene>();
	//ダンジョン潜入時間計測
	seq_dungeon->ClearTimeCountStart(start_time);

}
ScenePlay::~ScenePlay() {
	
	//ダンジョン潜入時間計測終了
	//分を受け取る
	SetMinutes(0,seq_dungeon->ClearTimeCountEnd(start_time).first);
	//秒を受け取る
	SetSeconds(0,seq_dungeon->ClearTimeCountEnd(start_time).second);
	//ダンジョンレベルを受け取る
	SetDungeonLevel(0,seq_dungeon->GetDugeonLevel());
	//プレイヤーのダイアモンド数を取得
	SetMaxDiamondNum(SceneTitle::game_manager->GetObjectManager()->factory->GetPlayer()->GetCharaStetus(Character::Stetus::DIAMOND));
	
	tnl::DebugTrace("\n前回のクリアタイム : %d分秒%d\n", GetMinutes(), GetSeconds());
	tnl::DebugTrace("\n前回の到達階層 : %d階\n", GetDungeonLevel());
	
	seq_dungeon.reset();

}
//------------------------------------------------------------------------------------------------------------
// 毎フレーム実行されます
void ScenePlay::Update(float delta_time) {

	
	seq_dungeon->Update(delta_time);
	
}

//------------------------------------------------------------------------------------------------------------
//描画関数
void ScenePlay::Draw() {
	//DrawStringEx(10, 10, -1, "ScenePlay");
	seq_dungeon->Draw();
}