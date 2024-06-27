//-------------------------------------------------------
//�����̂���
#include <time.h>
#include <string>
#include <numbers>
#include <functional>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
//-------------------------------------------------------
//�l�I�ɒǉ������@�\
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
//�R���X�g���N�^
ScenePlay::ScenePlay() {

	
	seq_dungeon = std::make_shared<DungeonScene>();
	//�_���W�����������Ԍv��
	seq_dungeon->ClearTimeCountStart(start_time);

}
ScenePlay::~ScenePlay() {
	
	//�_���W�����������Ԍv���I��
	//�����󂯎��
	SetMinutes(0,seq_dungeon->ClearTimeCountEnd(start_time).first);
	//�b���󂯎��
	SetSeconds(0,seq_dungeon->ClearTimeCountEnd(start_time).second);
	//�_���W�������x�����󂯎��
	SetDungeonLevel(0,seq_dungeon->GetDugeonLevel());
	//�v���C���[�̃_�C�A�����h�����擾
	SetMaxDiamondNum(SceneTitle::game_manager->GetObjectManager()->factory->GetPlayer()->GetCharaStetus(Character::Stetus::DIAMOND));
	
	tnl::DebugTrace("\n�O��̃N���A�^�C�� : %d���b%d\n", GetMinutes(), GetSeconds());
	tnl::DebugTrace("\n�O��̓��B�K�w : %d�K\n", GetDungeonLevel());
	
	seq_dungeon.reset();

}
//------------------------------------------------------------------------------------------------------------
// ���t���[�����s����܂�
void ScenePlay::Update(float delta_time) {

	
	seq_dungeon->Update(delta_time);
	
}

//------------------------------------------------------------------------------------------------------------
//�`��֐�
void ScenePlay::Draw() {
	//DrawStringEx(10, 10, -1, "ScenePlay");
	seq_dungeon->Draw();
}