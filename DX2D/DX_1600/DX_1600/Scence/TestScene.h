#pragma once
class Player;

class TestScene : public Scene
{
public:
	TestScene();
	virtual ~TestScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	shared_ptr<Player> _player;
	//to do : 발판 추가
	shared_ptr<Collider> _ground;
};