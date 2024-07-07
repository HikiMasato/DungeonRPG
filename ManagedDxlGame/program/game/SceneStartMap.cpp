#include <functional>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
//-------------------------------------------------------
//�l�I�ɒǉ������@�\
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
//�R���X�g���N�^
SceneStartMap::SceneStartMap()
{
	//�X�^�[�g�}�b�v���C���X�^���X��
	SceneTitle::game_manager->GetObjectManager()->GenerateOrdersToStartMapChip();
	
	//�X�^�[�ƃV�[��������
	InitSceneStartMap();

}

//------------------------------------------------------------------------------------------------------------
//�f�X�g���N�^
SceneStartMap::~SceneStartMap()
{
	//BGM���I��
	StopSoundMem(SceneTitle::game_manager->GetSoundManager()->sound_csv[9]);
	//�v���C���[�̍ŏI���W��ۑ�
	player_pos_buff = SceneTitle::game_manager->GetObjectManager()->factory->GetPlayer()->GetStartPostion();
}

//------------------------------------------------------------------------------------------------------------
//SceneStartMap������
void SceneStartMap::InitSceneStartMap() 
{
	//�t�H���g�T�C�Y��߂�
	SetFontSize(16);
	//BGM���Đ�
	SceneTitle::game_manager->GetSoundManager()->ChosePlayBGMSound(SceneTitle::game_manager->GetSoundManager()->sound_csv[9]);
	
	//�X�^�[�}�b�v�p�ɃX�P�[����ύX
	if (SceneTitle::game_manager->GetNowScale() != GameManager::ScaleMode::NOMAL) {
		SceneTitle::game_manager->ScaleChange();
	}

	//�v���C���[�̃X�|�[���^�C�v��ύX����
	SceneTitle::game_manager->GetObjectManager()->SetPlayerSpawnType(Factory::PlayerSpawn::STARTMAP);
	//�X�^�[�g�}�b�v�Ƀv���C���[�𐶐�
	SceneTitle::game_manager->GetObjectManager()->GenerateOrders(SceneTitle::game_manager->GetObjectManager()->factory->GetPlayerSpawn());

	
	map_in_ui = std::make_shared<Menu>(300, 350, 300, 100, "using_graphics/window_ui.png");



}

//------------------------------------------------------------------------------------------------------------
//�_���W�����ɓ��邩�ǂ�����Ui���o��������`�F�b�N����֐�
bool SceneStartMap::CheckDungeonInUi(tnl::Vector3 pos)
{	
	//��ԉE�̎R	
	tnl::Vector3 open_ui_pos_01 = { 240,550,0 };
	tnl::Vector3 open_ui_pos_02 = { 280,600,0 };
		

	if (open_ui_pos_01.x <= pos.x && open_ui_pos_01.y <= pos.y 
		&& open_ui_pos_02.x >= pos.x && open_ui_pos_02.y >= pos.y) {
		return true;
	}

	return false;
}

//------------------------------------------------------------------------------------------------------------
//�_���W����������ƃ}�E�X�̃|�C���^���d�Ȃ������ɁA�O��̃_���W�����̃N���A�^�C����\������
bool SceneStartMap::CheckDungeonClearTimeOpen(tnl::Vector3 pos)
{
	//��ԉE�̎R
	tnl::Vector3 open_ui_pos_01 = { 230,350,0 };
	tnl::Vector3 open_ui_pos_02 = { 280,400,0 };


	if (open_ui_pos_01.x <= pos.x && open_ui_pos_01.y <= pos.y
		&& open_ui_pos_02.x >= pos.x && open_ui_pos_02.y >= pos.y) {
		return true;
	}

	return false;
}

//------------------------------------------------------------------------------------------------------------
//�v���C���[���_���W�����ɓ���֐�
void SceneStartMap::PlayerInDungeon()
{
	auto mgr = SceneManager::GetInstance();
	mgr->ChangeScene(new ScenePlay);
}

//------------------------------------------------------------------------------------------------------------
//���t���[������
void SceneStartMap::Update(float delta_time)
{
	//���ׂĂ�Object��Update���Ă�(�C���X�^���X�����m�ۂ������̂̂�)
	SceneTitle::game_manager->GetObjectManager()->Update(delta_time);

	//�v���C���[�̃|�W�V�������擾(���ꔻ��Ɏg�p)
	tnl::Vector3 pos = SceneTitle::game_manager->GetObjectManager()->factory->GetPlayer()->GetCharaPos();
	player_pos_buff = pos;

	//�}�E�X�̃|�W�V�������擾
	GetMousePoint(&mouce_x_buff, &mouce_y_buff);

	//�����̃`�F�b�N���m�F���悤
	//�v���C���[�ƃ_���W�����ɓ���UI��\����������W����v���Ă��邩����
	if (CheckDungeonInUi(SceneTitle::game_manager->GetObjectManager()->factory->GetPlayer()->GetCharaPos())) {
		
		//�_���W����������SE
		SceneTitle::game_manager->GetSoundManager()->ChosePlaySystemSound(SceneTitle::game_manager->GetSoundManager()->sound_csv[22]);

		map_in_ui_open = true;
		//�_���W�����ɓ���
		PlayerInDungeon();

	}
	else {
		map_in_ui_open = false;
	}

	//�}�E�X�̃|�W�V�������_���W�����̏�ɗ�����
	if (CheckDungeonClearTimeOpen(tnl::Vector3(mouce_x_buff, mouce_y_buff,0))) {
		dungeon_clear_time = true;
	}
	else {
		dungeon_clear_time = false;
	}

}

//------------------------------------------------------------------------------------------------------------
//�`��
void SceneStartMap::Draw()
{
	//startmap�̕`��(basemap)(layer1)
	for (auto chip : SceneTitle::game_manager->GetObjectManager()->GetStartMapChipList()) {
		chip->StartMapDraw(camera);

	}
	//startmap�̕`��(decoration_map)(layer2)
	for (auto second_chip : SceneTitle::game_manager->GetObjectManager()->GetStartMapSecondChipList()) {
		second_chip->StartMapDraw(camera);
	}
	
	//�v���C���[�̕`��
	SceneTitle::game_manager->GetObjectManager()->factory->GetPlayer()->Draw(SceneTitle::game_manager->GetObjectManager()->factory->GetPlayer()->GetObjectType(), camera);

	//�_���W�����ɓ��鎞��UI
	if (map_in_ui_open) {
	}
	else {

	}

	if (dungeon_clear_time) {

		map_in_ui->MenuDraw();
		DrawStringEx(map_in_ui->menu_x + 10, map_in_ui->menu_y + 10, GetColor(255,255,255), "�O��̐������� : %d��%d�b", GetMinutes()[0], GetSeconds()[0]);
		DrawStringEx(map_in_ui->menu_x + 10, map_in_ui->menu_y + 30, GetColor(255,255,255), "�O��̓��B�K�w : %d�K", GetDungeonLevel()[0]);
		DrawStringEx(map_in_ui->menu_x + 10, map_in_ui->menu_y + 50, GetColor(255,255,255), "�_�C�A�����h�̍ő�擾�� : %d��", GetMaxDiamondNum());

	}
	else {

	}

	
}


