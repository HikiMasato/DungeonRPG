#pragma once


class SceneBase {
public:
	
	virtual ~SceneBase() {}

	virtual void Update(float delta_time) = 0;
	virtual void Draw() = 0;

	// �Q�[���J�n�������L�^����ϐ�
	std::chrono::high_resolution_clock::time_point start_time;
	
	//��
	int minutes, seconds = 0;

	//�}�E�X�̃|�W�V����
	tnl::Vector3 mouce_pos;
	POINT mouce_pos_p;

	int mouce_x_buff;
	int mouce_y_buff;
};