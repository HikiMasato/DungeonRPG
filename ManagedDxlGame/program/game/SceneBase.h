#pragma once


class SceneBase {
public:
	
	virtual ~SceneBase() {}

	virtual void Update(float delta_time) = 0;
	virtual void Draw() = 0;

	// ゲーム開始時刻を記録する変数
	std::chrono::high_resolution_clock::time_point start_time;
	
	//分
	int minutes, seconds = 0;

	//マウスのポジション
	tnl::Vector3 mouce_pos;
	POINT mouce_pos_p;

	int mouce_x_buff;
	int mouce_y_buff;
};