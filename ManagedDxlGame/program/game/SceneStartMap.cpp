#include <functional>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
//-------------------------------------------------------
//個人的に追加した機能
#include <string_view>
#include <random>         
#include <iostream>  
#include <variant>
//-------------------------------------------------------
//Scene
#include "SceneBase.h"
#include "SceneTitle.h"
#include "SceneStartMap.h"
#include "ScenePlay.h"
#include "DungeonScene.h"
#include "SceneEnd.h"
//-------------------------------------------------------
//Manager
#include "ObjectManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "GameManager.h"
#include "EnemyManager.h"
#include "MapManager.h"
#include "SkillManager.h"
#include "EffectManager.h"
#include "SoundManager.h"
#include "ItemManager.h"
//-------------------------------------------------------
//Object
#include "Factory.h"
#include "Object.h"
#include "MapChip.h"
#include "Player.h"
#include "Enemy.h"
#include "MyCamera.h"
#include "MenuWindow.h"
#include "Item.h"
//-------------------------------------------------------
//Collistion
#include "Collision.h" 
//-------------------------------------------------------
//effect
#include "ActionEffect.h"
//-------------------------------------------------------
//others
#include "Stetus.h"
#include "Debug.h"
#include "Skill.h"
#include "Inventory.h"



//------------------------------------------------------------------------------------------------------------
//コンストラクタ
SceneStartMap::SceneStartMap()
{
	//スタートマップをインスタンス化
	SceneTitle::game_manager->GetObjectManager()->GenerateOrdersToStartMapChip();
	
	//スターとシーン初期化
	InitSceneStartMap();

}

//------------------------------------------------------------------------------------------------------------
//デストラクタ
SceneStartMap::~SceneStartMap()
{
	//BGMを終了
	StopSoundMem(SceneTitle::game_manager->GetSoundManager()->sound_csv[9]);
	//プレイヤーの最終座標を保存
	player_pos_buff = SceneTitle::game_manager->GetObjectManager()->factory->GetPlayer()->GetStartPostion();
}

//------------------------------------------------------------------------------------------------------------
//SceneStartMap初期化
void SceneStartMap::InitSceneStartMap() 
{
	//フォントサイズを戻す
	SetFontSize(16);
	//BGMを再生
	SceneTitle::game_manager->GetSoundManager()->ChosePlayBGMSound(SceneTitle::game_manager->GetSoundManager()->sound_csv[9]);
	
	//スターマップ用にスケールを変更
	if (SceneTitle::game_manager->GetNowScale() != GameManager::ScaleMode::NOMAL) {
		SceneTitle::game_manager->ScaleChange();
	}

	//プレイヤーのスポーンタイプを変更する
	SceneTitle::game_manager->GetObjectManager()->SetPlayerSpawnType(Factory::PlayerSpawn::STARTMAP);
	//スタートマップにプレイヤーを生成
	SceneTitle::game_manager->GetObjectManager()->GenerateOrders(SceneTitle::game_manager->GetObjectManager()->factory->GetPlayerSpawn());

	
	map_in_ui = std::make_shared<Menu>(300, 350, 300, 100, "using_graphics/window_ui.png");



}

//------------------------------------------------------------------------------------------------------------
//ダンジョンに入るかどうかのUiを出す判定をチェックする関数
bool SceneStartMap::CheckDungeonInUi(tnl::Vector3 pos)
{	
	//一番右の山	
	tnl::Vector3 open_ui_pos_01 = { 240,550,0 };
	tnl::Vector3 open_ui_pos_02 = { 280,600,0 };
		

	if (open_ui_pos_01.x <= pos.x && open_ui_pos_01.y <= pos.y 
		&& open_ui_pos_02.x >= pos.x && open_ui_pos_02.y >= pos.y) {
		return true;
	}

	return false;
}

//------------------------------------------------------------------------------------------------------------
//ダンジョン入場口とマウスのポインタが重なった時に、前回のダンジョンのクリアタイムを表示する
bool SceneStartMap::CheckDungeonClearTimeOpen(tnl::Vector3 pos)
{
	//一番右の山
	tnl::Vector3 open_ui_pos_01 = { 230,350,0 };
	tnl::Vector3 open_ui_pos_02 = { 280,400,0 };


	if (open_ui_pos_01.x <= pos.x && open_ui_pos_01.y <= pos.y
		&& open_ui_pos_02.x >= pos.x && open_ui_pos_02.y >= pos.y) {
		return true;
	}

	return false;
}

//------------------------------------------------------------------------------------------------------------
//プレイヤーがダンジョンに入る関数
void SceneStartMap::PlayerInDungeon()
{
	auto mgr = SceneManager::GetInstance();
	mgr->ChangeScene(new ScenePlay);
}

//------------------------------------------------------------------------------------------------------------
//毎フレーム処理
void SceneStartMap::Update(float delta_time)
{
	//すべてのObjectのUpdateを呼ぶ(インスタンス化し確保したもののみ)
	SceneTitle::game_manager->GetObjectManager()->Update(delta_time);

	//プレイヤーのポジションを取得(足場判定に使用)
	tnl::Vector3 pos = SceneTitle::game_manager->GetObjectManager()->factory->GetPlayer()->GetCharaPos();
	player_pos_buff = pos;

	//マウスのポジションを取得
	GetMousePoint(&mouce_x_buff, &mouce_y_buff);

	//ここのチェックを確認しよう
	//プレイヤーとダンジョンに入るUIを表示させる座標が一致しているか判定
	if (CheckDungeonInUi(SceneTitle::game_manager->GetObjectManager()->factory->GetPlayer()->GetCharaPos())) {
		
		//ダンジョン潜入時SE
		SceneTitle::game_manager->GetSoundManager()->ChosePlaySystemSound(SceneTitle::game_manager->GetSoundManager()->sound_csv[22]);

		map_in_ui_open = true;
		//ダンジョンに入る
		PlayerInDungeon();

	}
	else {
		map_in_ui_open = false;
	}

	//マウスのポジションがダンジョンの上に来たら
	if (CheckDungeonClearTimeOpen(tnl::Vector3(mouce_x_buff, mouce_y_buff,0))) {
		dungeon_clear_time = true;
	}
	else {
		dungeon_clear_time = false;
	}

}

//------------------------------------------------------------------------------------------------------------
//描画
void SceneStartMap::Draw()
{
	//startmapの描画(basemap)(layer1)
	for (auto chip : SceneTitle::game_manager->GetObjectManager()->GetStartMapChipList()) {
		chip->StartMapDraw(camera);

	}
	//startmapの描画(decoration_map)(layer2)
	for (auto second_chip : SceneTitle::game_manager->GetObjectManager()->GetStartMapSecondChipList()) {
		second_chip->StartMapDraw(camera);
	}
	
	//プレイヤーの描画
	SceneTitle::game_manager->GetObjectManager()->factory->GetPlayer()->Draw(SceneTitle::game_manager->GetObjectManager()->factory->GetPlayer()->GetObjectType(), camera);

	//ダンジョンに入る時のUI
	if (map_in_ui_open) {
	}
	else {

	}

	if (dungeon_clear_time) {

		map_in_ui->MenuDraw();
		DrawStringEx(map_in_ui->menu_x + 10, map_in_ui->menu_y + 10, GetColor(255,255,255), "前回の潜入時間 : %d分%d秒", GetMinutes()[0], GetSeconds()[0]);
		DrawStringEx(map_in_ui->menu_x + 10, map_in_ui->menu_y + 30, GetColor(255,255,255), "前回の到達階層 : %d階", GetDungeonLevel()[0]);
		DrawStringEx(map_in_ui->menu_x + 10, map_in_ui->menu_y + 50, GetColor(255,255,255), "ダイアモンドの最大取得数 : %d個", GetMaxDiamondNum());

	}
	else {

	}

	
}


