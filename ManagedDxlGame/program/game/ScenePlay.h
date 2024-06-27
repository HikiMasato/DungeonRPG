#pragma once

class SceneBase;
class DungeonScene;
class ObjectManager;

class ScenePlay : public SceneBase {
public:
	ScenePlay();
	~ScenePlay();
	

	void Update(float delta_time) override;
	void Draw() override;
	
	std::shared_ptr<DungeonScene> seq_dungeon = nullptr;
};

