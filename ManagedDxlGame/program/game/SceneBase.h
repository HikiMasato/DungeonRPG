#pragma once


class SceneBase {
public:
	
	SceneBase();

	virtual ~SceneBase() {}

	virtual void Update(float delta_time) = 0;
	virtual void Draw() = 0;

	// �Q�[���J�n�������L�^����ϐ�
	std::chrono::high_resolution_clock::time_point start_time;
	
	

	int mouce_x_buff = 0;
	int mouce_y_buff = 0;




	std::vector<int> GetMinutes() const {
		return minutes;
	}
	std::vector<int> GetSeconds() const {
		return seconds;
	}
	std::vector<int> GetDungeonLevel() const {
		return dungeon_level;
	}
	int GetMaxDiamondNum() const {
		return max_diamond;
	}


	void SetMinutes(int num, int now) {
		minutes[num] += now;
	}
	void SetSeconds(int num, int now) {
		seconds[num] += now;
	}
	void SetDungeonLevel(int num, int add) {
		dungeon_level[num] += add;
	}
	void SetMaxDiamondNum(int num) {
		max_diamond += num;
	}


private:

	//��,�b
	static std::vector<int> minutes, seconds;

	//�_���W�������x��
	static std::vector<int> dungeon_level;

	//�W�߂��_�C�A�����h��
	static int max_diamond;

};